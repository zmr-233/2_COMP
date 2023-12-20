/*题解：一道特别典型的 贪心算法之区间调度问题
https://zhuanlan.zhihu.com/p/91254104
*/

/**
 * ## 原神，启动！

## 题目描述

小 $A$ 喜欢玩原神，他列了一串可以打原神的时间。我们知道原神不能重复启动，也就是一段时间内只能启动一个游戏。小 $A$ 当然希望启动的次数可以多一点，请你帮忙计算最多启动次数。
给定 $n$ 个开区间 $(a, b)$，你的任务是选择尽可能多的区间，使得这些区间之间没有交集。

## 输入格式

第一行包含一个整数 $T$ ，表示测试样例数量，下一行包含一个整数 $n$，表示区间的数量。接下来的 $n$ 行，每行包含两个整数 $a$ 和 $b$，表示一个开区间 $(a, b)$。

## 输出格式

每个样例输出一行一个整数，表示可以选择的最大区间数量。

## 数据范围

$1 ≤ n ≤ 100000$ 
$1 ≤ a < b ≤ 100000$

## 输入#1

```
2
3
1 5
2 4
3 5
5 
1 2 
2 3 
3 4 
4 5 
1 5
```

## 输出#1

```
1
4
```

解释： 选择区间 1-2，2-3，3-4 和 4-5，可以得到最大的区间数量。
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

const int MAXN = 1000010;
int n,ans,t;
pair<int, int>itv[MAXN];
int main(){
    int xxx;
    cin >> xxx;
    for(int ii=0;ii<xxx;ii++){
        cin >> n;
        for (int i = 1; i <= n; i++) 
            cin >> itv[i].second >> itv[i].first;
        sort(itv + 1, itv + n + 1);
        for (int i = 1; i <= n; i++) {
            if (t <= itv[i].second) {
                ans++;
                t = itv[i].first;
            }
        }
        cout << ans << endl;
        t=0,ans=0;
    }
	return 0;
}


