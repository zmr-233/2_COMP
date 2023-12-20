/**
 * ```markdown
## V-图
该比赛已结束，您无法在比赛模式下递交该题目。您可以点击“在题库中打开”以普通模式查看和递交本题。

长度为 $n$ 的整数序列 $a$ 是一个 $V$ 形图，如果满足 $n \geq 3$，并且存在一个索引 $i$（$1 < i < n$），满足以下条件：

- 对于 $1 \leq j < i$，有 $a_j > a_{j+1}$；
- 对于 $i < j \leq n$，有 $a_j > a_{j-1}$。

给定一个 $V$ 形图 $a$，请找到一个具有最大平均值的 $V$ 形图 $b$，满足 $b$ 是 $a$ 的一个连续子序列。

**注意**，序列的连续子序列可以通过从序列的开始和结束处移除一些（可以为零）元素来获得。

## 输入格式
每个测试包含多个测试用例。第一行包含一个整数 $t$（$1 \leq t \leq 10^5$），表示测试用例的数量。

对于每个测试用例，第一行包含一个整数 $n$（$3 \leq n \leq 3 \times 10^5$），表示整数序列 $a$ 的长度。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq 10^9$），表示序列 $a$。

保证 $a$ 是一个 $V$ 形图，所有测试用例中 $n$ 的总和不超过 $3 \times 10^5$。

## 输出格式
对于每个测试用例，输出一个实数，表示平均值的最大值。请精确到小数点后15位。

## 输入
```plaintext
2
4
8 2 7 10
6
9 6 5 3 4 8
```

## 输出
```plaintext
6.75000000000000000000
5.83333333333333303727
```
由于不会设置spj，精度方面用printf("%.15lf ")即可
```
*/

/**
 * 题意：
整个V形图就只有三种可能子序列:整个序列 `[1, n]`、从开始到最小值点之后的一个元素 `[1, m+1]`、从最小值点之前的一个元素到序列末尾 `[m-1, n]`
从其中挑一个即可
关键:
   - 使用前缀和数组 `sum[]`，其中 `sum[i]` 存储从序列开始到第 `i` 个元素的总和。
   - 考虑三种可能的子序列：。
   - 计算这三个子序列的平均值，并选择最大的平均值作为结果
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define int long long
const int N=3e5+5;
ll a[N];
ll sum[N];
void solve()
{
    int n;cin>>n;
    for(int i=1;i<=n;i++)sum[i]=0;
    for(int i=1;i<=n;i++)cin>>a[i],sum[i]=a[i]+sum[i-1];
    int l=1,r=n;int m=0;
    while(l<=r){ /*二分法找到中点*/
        int mid=(l+r)>>1;
        if(a[mid]<a[mid-1]&&a[mid]<a[mid+1]){
            m=mid;break;
        }
        if(a[mid]>a[mid+1])l=mid+1;
        else if(a[mid]>a[mid-1])r=mid-1;
    }
    double ans=1.0*sum[n]/n;
    ans=max(ans,max(1.0*sum[m+1]/(m+1),1.0*(sum[n]-sum[m-2])/(n-m+2)));
    cout<<fixed<<setprecision(15)<<ans<<endl;
}
signed main()
{
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr);std::cout.tie(nullptr);
    int t;t=1;
    std::cin>>t;
    while(t--)solve();
}


