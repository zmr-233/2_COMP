#include<bits/stdc++.h>
using namespace std;
typedef long long llg;
const int mod=1e9+7;
const int N=1e5+5;
vector <int>a[N];
llg ans=0;
int dp[N][2];
int vis[N];
void dfs(int t)
{
    vis[t]=1;
    for(auto x:a[t])
    {
        if(!vis[x])
        {
            dfs(x);
            dp[t][0]=(dp[t][0]*(dp[x][0]+dp[x][1]))%mod;
            dp[t][1]=(dp[t][1]*dp[x][0])%mod;
        }
    }
}
int main()
{
    int n;cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
    {
        dp[i][0]=1;
        dp[i][1]=1;
    }
    dfs(1);
    ans=(dp[1][1]+dp[1][0])%mod;
    cout<<ans<<endl;
}
