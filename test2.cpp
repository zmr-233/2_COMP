如下是GNU C库的动态链接器ld-linux.so的部分源码，如下的代码作为Bootstrap代码(不能调用任何函数)写得十分精妙，请你仔细分析和梳理架构逻辑
/* Run time dynamic linker.
   Copyright (C) 1995-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <ldsodefs.h>
#include <_itoa.h>
#include <entry.h>
#include <fpu_control.h>
#include <hp-timing.h>
#include <libc-lock.h>
#include "dynamic-link.h"
#include <dl-librecon.h>
#include <unsecvars.h>
#include <dl-cache.h>
#include <dl-osinfo.h>
#include <dl-procinfo.h>
#include <dl-prop.h>
#include <tls.h>
#include <stap-probe.h>
#include <stackinfo.h>
#include <not-cancel.h>

#include <assert.h>

/* Avoid PLT use for our local calls at startup.  */
extern __typeof (__mempcpy) __mempcpy attribute_hidden;

/* GCC has mental blocks about _exit.  */
extern __typeof (_exit) exit_internal asm ("_exit") attribute_hidden;
#define _exit exit_internal

/* Helper function to handle errors while resolving symbols.  */
static void print_unresolved (int errcode, const char *objname,
			      const char *errsting);

/* Helper function to handle errors when a version is missing.  */
static void print_missing_version (int errcode, const char *objname,
				   const char *errsting);

/* Print the various times we collected.  */
static void print_statistics (hp_timing_t *total_timep);

/* Add audit objects.  */
static void process_dl_audit (char *str);

/* This is a list of all the modes the dynamic loader can be in.  */
enum mode { normal, list, verify, trace };

/* Process all environments variables the dynamic linker must recognize.
   Since all of them start with `LD_' we are a bit smarter while finding
   all the entries.  */
static void process_envvars (enum mode *modep);

#ifdef DL_ARGV_NOT_RELRO
int _dl_argc attribute_hidden;
char **_dl_argv = NULL;
/* Nonzero if we were run directly.  */
unsigned int _dl_skip_args attribute_hidden;
#else
int _dl_argc attribute_relro attribute_hidden;
char **_dl_argv attribute_relro = NULL;
unsigned int _dl_skip_args attribute_relro attribute_hidden;
#endif
rtld_hidden_data_def (_dl_argv)

#ifndef THREAD_SET_STACK_GUARD
/* Only exported for architectures that don't store the stack guard canary
   in thread local area.  */
uintptr_t __stack_chk_guard attribute_relro;
#endif

/* Only exported for architectures that don't store the pointer guard
   value in thread local area.  */
uintptr_t __pointer_chk_guard_local
     attribute_relro attribute_hidden __attribute__ ((nocommon));
#ifndef THREAD_SET_POINTER_GUARD
strong_alias (__pointer_chk_guard_local, __pointer_chk_guard)
#endif

/* Length limits for names and paths, to protect the dynamic linker,
   particularly when __libc_enable_secure is active.  */
#ifdef NAME_MAX
# define SECURE_NAME_LIMIT NAME_MAX
#else
# define SECURE_NAME_LIMIT 255
#endif
#ifdef PATH_MAX
# define SECURE_PATH_LIMIT PATH_MAX
#else
# define SECURE_PATH_LIMIT 1024
#endif

/* Check that AT_SECURE=0, or that the passed name does not contain
   directories and is not overly long.  Reject empty names
   unconditionally.  */
static bool
dso_name_valid_for_suid (const char *p)
{
  if (__glibc_unlikely (__libc_enable_secure))
    {
      /* Ignore pathnames with directories for AT_SECURE=1
	 programs, and also skip overlong names.  */
      size_t len = strlen (p);
      if (len >= SECURE_NAME_LIMIT || memchr (p, '/', len) != NULL)
	return false;
    }
  return *p != '\0';
}

/* LD_AUDIT variable contents.  Must be processed before the
   audit_list below.  */
const char *audit_list_string;

/* Cyclic list of auditing DSOs.  audit_list->next is the first
   element.  */
static struct audit_list
{
  const char *name;
  struct audit_list *next;
} *audit_list;

/* Iterator for audit_list_string followed by audit_list.  */
struct audit_list_iter
{
  /* Tail of audit_list_string still needing processing, or NULL.  */
  const char *audit_list_tail;

  /* The list element returned in the previous iteration.  NULL before
     the first element.  */
  struct audit_list *previous;

  /* Scratch buffer for returning a name which is part of
     audit_list_string.  */
  char fname[SECURE_NAME_LIMIT];
};

/* Initialize an audit list iterator.  */
static void
audit_list_iter_init (struct audit_list_iter *iter)
{
  iter->audit_list_tail = audit_list_string;
  iter->previous = NULL;
}

/* Iterate through both audit_list_string and audit_list.  */
static const char *
audit_list_iter_next (struct audit_list_iter *iter)
{
  if (iter->audit_list_tail != NULL)
    {
      /* First iterate over audit_list_string.  */
      while (*iter->audit_list_tail != '\0')
	{
	  /* Split audit list at colon.  */
	  size_t len = strcspn (iter->audit_list_tail, ":");
	  if (len > 0 && len < sizeof (iter->fname))
	    {
	      memcpy (iter->fname, iter->audit_list_tail, len);
	      iter->fname[len] = '\0';
	    }
	  else
	    /* Do not return this name to the caller.  */
	    iter->fname[0] = '\0';

	  /* Skip over the substring and the following delimiter.  */
	  iter->audit_list_tail += len;
	  if (*iter->audit_list_tail == ':')
	    ++iter->audit_list_tail;

	  /* If the name is valid, return it.  */
	  if (dso_name_valid_for_suid (iter->fname))
	    return iter->fname;
	  /* Otherwise, wrap around and try the next name.  */
	}
      /* Fall through to the procesing of audit_list.  */
    }

  if (iter->previous == NULL)
    {
      if (audit_list == NULL)
	/* No pre-parsed audit list.  */
	return NULL;
      /* Start of audit list.  The first list element is at
	 audit_list->next (cyclic list).  */
      iter->previous = audit_list->next;
      return iter->previous->name;
    }
  if (iter->previous == audit_list)
    /* Cyclic list wrap-around.  */
    return NULL;
  iter->previous = iter->previous->next;
  return iter->previous->name;
}

#ifndef HAVE_INLINED_SYSCALLS
/* Set nonzero during loading and initialization of executable and
   libraries, cleared before the executable's entry point runs.  This
   must not be initialized to nonzero, because the unused dynamic
   linker loaded in for libc.so's "ld.so.1" dep will provide the
   definition seen by libc.so's initializer; that value must be zero,
   and will be since that dynamic linker's _dl_start and dl_main will
   never be called.  */
int _dl_starting_up = 0;
rtld_hidden_def (_dl_starting_up)
#endif

/* This is the structure which defines all variables global to ld.so
   (except those which cannot be added for some reason).  */
struct rtld_global _rtld_global =
  {
    /* Generally the default presumption without further information is an
     * executable stack but this is not true for all platforms.  */
    ._dl_stack_flags = DEFAULT_STACK_PERMS,
#ifdef _LIBC_REENTRANT
    ._dl_load_lock = _RTLD_LOCK_RECURSIVE_INITIALIZER,
    ._dl_load_write_lock = _RTLD_LOCK_RECURSIVE_INITIALIZER,
#endif
    ._dl_nns = 1,
    ._dl_ns =
    {
#ifdef _LIBC_REENTRANT
      [LM_ID_BASE] = { ._ns_unique_sym_table
		       = { .lock = _RTLD_LOCK_RECURSIVE_INITIALIZER } }
#endif
    }
  };
/* If we would use strong_alias here the compiler would see a
   non-hidden definition.  This would undo the effect of the previous
   declaration.  So spell out was strong_alias does plus add the
   visibility attribute.  */
extern struct rtld_global _rtld_local
    __attribute__ ((alias ("_rtld_global"), visibility ("hidden")));

/* This variable is similar to _rtld_local, but all values are
   read-only after relocation.  */
struct rtld_global_ro _rtld_global_ro attribute_relro =
  {
    /* Get architecture specific initializer.  */
#include <dl-procinfo.c>
#ifdef NEED_DL_SYSINFO
    ._dl_sysinfo = DL_SYSINFO_DEFAULT,
#endif
    ._dl_debug_fd = STDERR_FILENO,
    ._dl_use_load_bias = -2,
    ._dl_correct_cache_id = _DL_CACHE_DEFAULT_ID,
#if !HAVE_TUNABLES
    ._dl_hwcap_mask = HWCAP_IMPORTANT,
#endif
    ._dl_lazy = 1,
    ._dl_fpu_control = _FPU_DEFAULT,
    ._dl_pagesize = EXEC_PAGESIZE,
    ._dl_inhibit_cache = 0,

    /* Function pointers.  */
    ._dl_debug_printf = _dl_debug_printf,
    ._dl_mcount = _dl_mcount,
    ._dl_lookup_symbol_x = _dl_lookup_symbol_x,
    ._dl_open = _dl_open,
    ._dl_close = _dl_close,
    ._dl_tls_get_addr_soft = _dl_tls_get_addr_soft,
#ifdef HAVE_DL_DISCOVER_OSVERSION
    ._dl_discover_osversion = _dl_discover_osversion
#endif
  };
/* If we would use strong_alias here the compiler would see a
   non-hidden definition.  This would undo the effect of the previous
   declaration.  So spell out was strong_alias does plus add the
   visibility attribute.  */
extern struct rtld_global_ro _rtld_local_ro
    __attribute__ ((alias ("_rtld_global_ro"), visibility ("hidden")));

static void dl_main (const ElfW(Phdr) *phdr, ElfW(Word) phnum,
		     ElfW(Addr) *user_entry, ElfW(auxv_t) *auxv);

/* These two variables cannot be moved into .data.rel.ro.  */
static struct libname_list _dl_rtld_libname;
static struct libname_list _dl_rtld_libname2;

/* Variable for statistics.  */
#ifndef HP_TIMING_NONAVAIL
static hp_timing_t relocate_time;
static hp_timing_t load_time attribute_relro;
static hp_timing_t start_time attribute_relro;
#endif

/* Additional definitions needed by TLS initialization.  */
#ifdef TLS_INIT_HELPER
TLS_INIT_HELPER
#endif

/* Helper function for syscall implementation.  */
#ifdef DL_SYSINFO_IMPLEMENTATION
DL_SYSINFO_IMPLEMENTATION
#endif

/* Before ld.so is relocated we must not access variables which need
   relocations.  This means variables which are exported.  Variables
   declared as static are fine.  If we can mark a variable hidden this
   is fine, too.  The latter is important here.  We can avoid setting
   up a temporary link map for ld.so if we can mark _rtld_global as
   hidden.  */
#ifdef PI_STATIC_AND_HIDDEN
# define DONT_USE_BOOTSTRAP_MAP	1
#endif

#ifdef DONT_USE_BOOTSTRAP_MAP
static ElfW(Addr) _dl_start_final (void *arg);
#else
struct dl_start_final_info
{
  struct link_map l;
#if !defined HP_TIMING_NONAVAIL && HP_TIMING_INLINE
  hp_timing_t start_time;
#endif
};
static ElfW(Addr) _dl_start_final (void *arg,
				   struct dl_start_final_info *info);
#endif

/* These defined magically in the linker script.  */
extern char _begin[] attribute_hidden;
extern char _etext[] attribute_hidden;
extern char _end[] attribute_hidden;

#ifdef RTLD_START
RTLD_START
#else
# error "sysdeps/MACHINE/dl-machine.h fails to define RTLD_START"
#endif

/* This is the second half of _dl_start (below).  It can be inlined safely
   under DONT_USE_BOOTSTRAP_MAP, where it is careful not to make any GOT
   references.  When the tools don't permit us to avoid using a GOT entry
   for _dl_rtld_global (no attribute_hidden support), we must make sure
   this function is not inlined (see below).  */

#ifdef DONT_USE_BOOTSTRAP_MAP
static inline ElfW(Addr) __attribute__ ((always_inline))
_dl_start_final (void *arg)
#else
static ElfW(Addr) __attribute__ ((noinline))
_dl_start_final (void *arg, struct dl_start_final_info *info)
#endif
{
  ElfW(Addr) start_addr;

  if (HP_SMALL_TIMING_AVAIL)
    {
      /* If it hasn't happen yet record the startup time.  */
      if (! HP_TIMING_INLINE)
	HP_TIMING_NOW (start_time);
#if !defined DONT_USE_BOOTSTRAP_MAP && !defined HP_TIMING_NONAVAIL
      else
	start_time = info->start_time;
#endif
    }

  /* Transfer data about ourselves to the permanent link_map structure.  */
#ifndef DONT_USE_BOOTSTRAP_MAP
  GL(dl_rtld_map).l_addr = info->l.l_addr;
  GL(dl_rtld_map).l_ld = info->l.l_ld;
  memcpy (GL(dl_rtld_map).l_info, info->l.l_info,
	  sizeof GL(dl_rtld_map).l_info);
  GL(dl_rtld_map).l_mach = info->l.l_mach;
  GL(dl_rtld_map).l_relocated = 1;
#endif
  _dl_setup_hash (&GL(dl_rtld_map));
  GL(dl_rtld_map).l_real = &GL(dl_rtld_map);
  GL(dl_rtld_map).l_map_start = (ElfW(Addr)) _begin;
  GL(dl_rtld_map).l_map_end = (ElfW(Addr)) _end;
  GL(dl_rtld_map).l_text_end = (ElfW(Addr)) _etext;
  /* Copy the TLS related data if necessary.  */
#ifndef DONT_USE_BOOTSTRAP_MAP
# if NO_TLS_OFFSET != 0
  GL(dl_rtld_map).l_tls_offset = NO_TLS_OFFSET;
# endif
#endif

  HP_TIMING_NOW (GL(dl_cpuclock_offset));

  /* Initialize the stack end variable.  */
  __libc_stack_end = __builtin_frame_address (0);

  /* Call the OS-dependent function to set up life so we can do things like
     file access.  It will call `dl_main' (below) to do all the real work
     of the dynamic linker, and then unwind our frame and run the user
     entry point on the same stack we entered on.  */
  start_addr = _dl_sysdep_start (arg, &dl_main);

#ifndef HP_TIMING_NONAVAIL
  hp_timing_t rtld_total_time;
  if (HP_SMALL_TIMING_AVAIL)
    {
      hp_timing_t end_time;

      /* Get the current time.  */
      HP_TIMING_NOW (end_time);

      /* Compute the difference.  */
      HP_TIMING_DIFF (rtld_total_time, start_time, end_time);
    }
#endif

  if (__glibc_unlikely (GLRO(dl_debug_mask) & DL_DEBUG_STATISTICS))
    {
#ifndef HP_TIMING_NONAVAIL
      print_statistics (&rtld_total_time);
#else
      print_statistics (NULL);
#endif
    }

  return start_addr;
}

static ElfW(Addr) __attribute_used__
_dl_start (void *arg)
{
#ifdef DONT_USE_BOOTSTRAP_MAP
# define bootstrap_map GL(dl_rtld_map)
#else
  struct dl_start_final_info info;
# define bootstrap_map info.l
#endif

  /* This #define produces dynamic linking inline functions for
     bootstrap relocation instead of general-purpose relocation.
     Since ld.so must not have any undefined symbols the result
     is trivial: always the map of ld.so itself.  */
#define RTLD_BOOTSTRAP
#define BOOTSTRAP_MAP (&bootstrap_map)
#define RESOLVE_MAP(sym, version, flags) BOOTSTRAP_MAP
#include "dynamic-link.h"

  if (HP_TIMING_INLINE && HP_SMALL_TIMING_AVAIL)
#ifdef DONT_USE_BOOTSTRAP_MAP
    HP_TIMING_NOW (start_time);
#else
    HP_TIMING_NOW (info.start_time);
#endif

  /* Partly clean the `bootstrap_map' structure up.  Don't use
     `memset' since it might not be built in or inlined and we cannot
     make function calls at this point.  Use '__builtin_memset' if we
     know it is available.  We do not have to clear the memory if we
     do not have to use the temporary bootstrap_map.  Global variables
     are initialized to zero by default.  */
#ifndef DONT_USE_BOOTSTRAP_MAP
# ifdef HAVE_BUILTIN_MEMSET
  __builtin_memset (bootstrap_map.l_info, '\0', sizeof (bootstrap_map.l_info));
# else
  for (size_t cnt = 0;
       cnt < sizeof (bootstrap_map.l_info) / sizeof (bootstrap_map.l_info[0]);
       ++cnt)
    bootstrap_map.l_info[cnt] = 0;
# endif
#endif

  /* Figure out the run-time load address of the dynamic linker itself.  */
  bootstrap_map.l_addr = elf_machine_load_address ();

  /* Read our own dynamic section and fill in the info array.  */
  bootstrap_map.l_ld = (void *) bootstrap_map.l_addr + elf_machine_dynamic ();
  elf_get_dynamic_info (&bootstrap_map, NULL);

#if NO_TLS_OFFSET != 0
  bootstrap_map.l_tls_offset = NO_TLS_OFFSET;
#endif

#ifdef ELF_MACHINE_BEFORE_RTLD_RELOC
  ELF_MACHINE_BEFORE_RTLD_RELOC (bootstrap_map.l_info);
#endif

  if (bootstrap_map.l_addr || ! bootstrap_map.l_info[VALIDX(DT_GNU_PRELINKED)])
    {
      /* Relocate ourselves so we can do normal function calls and
	 data access using the global offset table.  */

      ELF_DYNAMIC_RELOCATE (&bootstrap_map, 0, 0, 0);
    }
  bootstrap_map.l_relocated = 1;

  /* Please note that we don't allow profiling of this object and
     therefore need not test whether we have to allocate the array
     for the relocation results (as done in dl-reloc.c).  */

  /* Now life is sane; we can call functions and access global data.
     Set up to use the operating system facilities, and find out from
     the operating system's program loader where to find the program
     header table in core.  Put the rest of _dl_start into a separate
     function, that way the compiler cannot put accesses to the GOT
     before ELF_DYNAMIC_RELOCATE.  */
