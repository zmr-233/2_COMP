//true
/**
 * ## Randias的作业

## 题目描述

$Randias$ 正在面对他的小学作业：
找到一个长度为 $2n$ 的非零整数序列 $a$，满足以下条件：
$(a_1 × a_2) + (a_3 × a_4) + · · · + (a_{2n−1}~ × a_{2n}) = a_1 × (a_2 + a_3) × (a_4 + a_5) × · · · × (a_{2n−2} + a_{2n−1}) × a_{2n} != 0$
即 $\sum_{i=1}^{n} a_{2i-1}a_{2i} = a_{1}a_{2n}\prod_{i=2}^{n} (a_{2i-2} + a_{2i-1}) \neq 0$。
当然，$Randias$ 知道如何解决这个问题。但他想给你一个测试。你能解决上面的问题吗？

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$ $(1 ≤ t ≤ 10^5) $，表示测试用例的数量。
对于每个测试用例，只有一行包含一个整数 $n$ $(2 ≤ n ≤ 10^5)$。
保证所有测试用例中 $n$ 的总和不超过 $2·10^5$ 。

## 输出格式

对于每个测试用例，输出一行包含 $2n$ 个整数，表示 $a_1，a_2，...，a_{2n}$ $ (1 ≤ |ai| ≤ 10^{10}) $。
可以证明答案总是存在。

## 输入#1

```
3
2
3
4
```

## 输出#1

```
1 -3 -3 1
1 -10 6 6 -10 1
1 -15 10 -1 -1 10 -15 1
```
*/

/**
 * 解题思路:只需要构造一个序列满足表达式即可
这道题典型就是被样例所误解了，想办法去构造类似对称的序列，实际上是完全没有必要的
首要考虑到乘法不能乘得太大，想到用1去构造，当(a_i-a_{i-1}==1)的时候，那么可以构造类似
x, -1,−1,2,−1,··· ,2,−1,y 的序列, 令 y = 1 解出 x 即可.
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
    return q ? -w : w;
}
int main(){
    int x; cin >> x;
    for(int j=0;j<x;j++){
        int n;cin>>n;
        cout << 3-n << " ";
        for(int i=1;i<=n-1;i++) cout << -1 << " " << 2 << " ";
        cout << 1<<" ";
    }
    return 0;
}