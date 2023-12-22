/**
 * 给定序列的子序列是原序列删除一些（可能没有）元素后形成的序列。
 * 给定一个序列 X = <x1, x2, ..., xm>，另一个序列 Z = <z1, z2, ..., zk> 是 X 的子序列，
 * 如果存在一个 X 的索引的严格递增序列 <i1, i2, ..., ik> 使得对于所有 j = 1,2,...,k, 
 * 都有 xij = zj。例如，Z = <a, b, f, c> 是 X = <a, b, c, f, b, c> 的子序列，
 * 其索引序列为 <1, 2, 4, 6>。给定两个序列 X 和 Y，
 * 问题是找出 X 和 Y 的最长公共子序列的长度。
 
程序的输入来自一个文本文件。文件中的每个数据集包含两个字符串，
代表给定的序列。序列之间由任意数量的空白字符分隔。输入数据是正确的。
对于每组数据，程序在标准输出的新行开始处打印最长公共子序列的长度。

样例输入
abcfbc abfcab
programming contest 
abcd mnp

样例输出
4
2
0
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long llg;
const llg INF = 2147483647;

//#define yyj(a) freopen("0_in/"a".in","r",stdin),freopen("0_out/"a".out","w",stdout);
#define yyj(a) freopen(("0_in/" + string(a) + ".in").c_str(),"r",stdin),freopen(("0_out/" + string(a) + ".out").c_str(),"w",stdout)
inline llg getint()
{
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ?  -w : w;
}

int main(){
    
}
