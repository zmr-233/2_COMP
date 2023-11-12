#include <bits/stdc++.h>
using namespace std;
#define fl(i, a, b) for (int i = a, i##_ = b; i <= i##_; ++i)
#define fr(i, a, b) for (int i = a, i##_ = b; i >= i##_; --i)
using ll = long long;
using ull = unsigned long long;
const int inf = 0x3f3f3f3f; 
const ll INF=0x3f3f3f3f3f3f3f3f;
#define int long long
const int N=2e5+5;
int a[N];
void solve()
{
    int n;cin>>n;
    int s,t;s=inf;t=0;
    ll sum=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];
        if(a[i]<s)s=a[i];
        if(a[i]>t)t=a[i];
    }
    ll ans=0;
    int judge=0;int cnt=0;
    for(int i=1;i<=n;i++)
    {
        //if(a[i]>s&&a[i]<t)judge=true;
        if(a[i]==s)cnt++;
        if(cnt>=2){judge=true;}
        if(judge)break;
    }
    if(!judge)ans=(sum-s-t);
    else ans=(sum+1-s-t);
    cout<<ans<<endl;

}
signed main()
{
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr);std::cout.tie(nullptr);
    int t;
    t=1;
    std::cin>>t;
    while(t--)solve();
}