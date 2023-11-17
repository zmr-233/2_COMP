//p1725  https://www.luogu.com.cn/problem/P1725
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 2147483647;
const int N = 400010;
ll n,l,r,a[N],f[N];
int main(){
    int tmp_n;cin >> n >> l >> r;
    deque<ll> dq;
    memset(f,-1,sizeof(f));
    memset(a,0,sizeof(a));
    f[0] = 0;
    for(int i=0;i<=n;i++) cin >> a[i];
    int j = 0;
    ll max_f = -INF;
    for(int i=0;i<=n;i++){
        if(j <= n && i-j >= l && j < i ){
            while(!dq.empty()  && f[j] > f[dq.back()]) dq.pop_back();
            dq.push_back(j);
            j++;
        }
        while(!dq.empty() && i - dq.front() > r) dq.pop_front();
        if(!dq.empty() && dq.front() <=n && f[dq.front()] != -1/*检查能否被跳到*/) f[i] = a[i] + f[dq.front()];
        if(i + r > n && f[i] > max_f) max_f = f[i];
    }
    cout << max_f;
    return 0;
}
//WA:最后两组数据会WA:
//主要是因为没有判断DP状态的转移是否合法，如果该点是不能到达的，那么就不能用它更新后面的状态
//应该使用数组use[i]进行标记

/**
 * 总结:
 * 这里要检查能否被跳到，若根本跳不到为-1，直接不计算
*/
