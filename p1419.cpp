#include<bits/stdc++.h>
using namespace std;

typedef long long llg;
const llg INF = 2147483647;

#define yyj(a) freopen("0_in/"a".in","r",stdin),freopen("0_out/"a".out","w",stdout);

inline llg getint()
{
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ? -w : w;
}

