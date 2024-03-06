#### 基本操作

- 查看文件头(是元信息,指明了段表的位置)
`readelf -h <fn>`包含魔数&基本大小

- 查看Section段表(由文件头e_shoff成员决定)
`readelf -S <fn>`更加详细的段表-->包含每段的标记
`objdump -h <fn>`主要是段表-->**每个段的大小\索引\地址\偏移**

- 查看Segment段表(被称作程序头表，只有ELF可执行文件才有)
`readelf -l <fn>`查看装载与内存


- .text代码段
`readelf -x .text <fn>`注意readelf不支持反汇编
`objdump -s -d <fn>`-->**着重推荐:自动反汇编**(-d足够 -s显示16进制)

- .data & .rodata段
`readelf -x .data <fn>`自行将.data替换为.rodata即可
`objdump -s --section=.data <fn>`实际使用下来两者差不多

- .bss段“未初始化全局变量&静态变量"
`readelf -d <fn>`
`objdump -s --section=.bss <fn>`

- .strtab字符串表

#### 重定位
`ld <fn>`会简单显示未定义的符号信息
`objdump -r <fn>`重定位表**推荐使用**

- .symtab符号表
`readelf -s <fn>`符号表**推荐:更加详细**->地址\大小等等
`objdump -t <fn>`和nm基本上差不多

#### 符号信息
**可以单独使用nm获取符号信息**
`nm <fn>`显示所有符号表信息(较为简洁)-->注意nm是带有元数据

#### |查看Section&Segment
`readelf -S <fn>`查看Section信息
`readelf -l <fn>`查看Segment信息

#### |查看模块间数据访问
1. 使用`objdump -h`找到`.got`段
2. `objdump -R <fn.so>`找到**动态链接**的重定位项(必需是共享文件)

#### 推荐命令
`objdump -x -d -t <fn>`显示大部分信息


#### 动态链接相关结构
- .interp段:
`objdump -s <fn>`或者`readelf -l <fn> | grep interpreter`

- .dynamic段
`readelf -d <fn.so>`这个算动态链接的"文件头"
`ldd <fn>`用于查看依赖的共享库

- .dynsym动态符号表
`readelf -sD <fn.so>`只保存与动态链接相关的符号(相当于.symtab)

- .rel.dyn & .rel.plt 动态链接重定位表
`readelf -r <fn.so>`能够读出动态/静态的重定位表
