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

const int MAXN = 35010;
int nums_n[12];
int nums[12][210];
int dp[5010];
int oo;
set<int> ans;
int main(){
    ios::sync_with_stdio(false);
    cin >> oo;
    for(int o=0;o<oo;o++){
        int n;
        int t_t,t_w;
        int l,r;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            cin >> t_t >> t_w;
            nums[t_t][++nums_n[t_t]]=t_w;
        }
        scanf("%d %d",&l,&r);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=10;i++)
            if(nums_n[i]!=0){
                for(int j=r;j>=0;j--)
                    for(int k=1;k<=nums_n[i];k++)
                        if(j>=nums[i][k]){
                            dp[j]=max(dp[j],dp[j-nums[i][k]]+nums[i][k]);
                        }
            }
        ans.clear();
        for(int i=l;i<=r;i++) if(dp[i]>=l && dp[i] <=r) ans.insert(dp[i]);
        printf("%d\n",ans.size());
        if(ans.size() == 0) continue;
            for(auto i:ans)
                printf("%d ",i);
        printf("\n");
        return 0;
    }
}