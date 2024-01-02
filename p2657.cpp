
/**
 * 典型的数位统计DP+记忆化存储
 * 建议看书P338
 * 
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

const int N = 15;
int dp[N][N],num[N];
int dfs(int pos,int last,bool lead,bool limit){
    if(pos==0) return 1; //因为0-9是单独作为Windy数的
    if(!lead && !limit && dp[pos][last]!=-1) return dp[pos][last];
    int ans = 0;
    int up=(limit?num[pos]:9);
    for(int i=0;i<=up;i++){
        if(abs(i-last)<2) continue;
        if(i==0 && lead) ans+=dfs(pos-1,-2,true,limit && i==up);
        else ans += dfs(pos-1,i,false,limit && i==up);
    }
    if(!lead && !limit) dp[pos][last]=ans;
    return ans;
}
int solve(int x){
    int len=0;
    while(x){
        num[++len]=x%10;
        x/=10;
    }
    memset(dp,-1,sizeof(dp));
    return dfs(len,-2,true,true); //这里使用-2，是为了确保第一位数字，都可以被dfs
}
int main(){
    int a,b; cin >> a >> b;
    cout << solve(b)-solve(a-1);
    return 0;
}

