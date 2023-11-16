//P3957--单调队列优化DP
//标准题解:https://www.luogu.com.cn/blog/SalomeJLQ/solution-p3957
#include<bits/stdc++.h>
using namespace std;
const int N = 500010;
typedef long long ll;
const ll INF = 2147483647;
ll a[N][2],f[N];ll n,d,k;
//A-不带DP优化的
bool dp_check(ll g){
    memset(f,-127,sizeof(f));
    ll x= max(d-g,(ll)1),s=d+g;
    f[0] = 0;
    for(int i=1;i<=n;i++){
        for(int j=i-1;j>=0;j--){
            if(a[i][0]-a[j][0]<x) continue;
            if(a[i][0]-a[j][0]>s)break;
            f[i] = max(f[i],f[j]+a[i][1]);
            if(f[i]>=k) return true;
        }
    }
    return false;
}
//B-带DP优化的
bool dp_optimizer_check(ll g){
    memset(f,-127,sizeof(f));
    f[0] = 0; ll x = max(d-g,(ll)1),s = d+g;
    deque<ll> dq;
    int j = 0;
    for(int i=1;i <= n;i++){
        while(a[i][0]-a[j][0] >= x && j <i){
            //检查队尾单调性
            while(!dq.empty() && f[j] > f[dq.back()] ) dq.pop_back();
            dq.push_back(j);
            j++;//符合单调性后，插入决策j
        }
        while(!dq.empty() && a[i][0]-a[dq.front()][0] >s) dq.pop_front();
        //实行决策
        if(!dq.empty()) f[i] = a[i][1]+f[dq.front()];
        if(f[i]>=k) return true;
    }
    return false;
}
int main(){
    cin >> n >> d >> k;
    ll top_k = 0;
    for(int i=1;i<=n;i++){cin >>a[i][0] >> a[i][1]; if(a[i][1]>0) top_k += a[i][1]; }
    if(top_k<k){cout << -1; return 0;}
    ll l = 0, r = a[n][0];
    //见到鬼畜的g，首要想法不是挨个枚举，肯定是二分法
    while(l<r){
        ll mid = (l+r)>>1;
        if(dp_optimizer_check(mid)) r = mid;
        else l = mid +1;
    }
    cout << l;
    return 0;
}