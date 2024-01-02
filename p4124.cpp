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

int num[N];
llg dp[N][11][11][2][2][2];
//dp[pos][u][v][state][n8][n4];

#ifdef USE_ERROR
int dfs(int pos,int u,int v,bool state,bool is8,bool is4,bool lead,bool limit){
    //E1:
    if(is8 && is4) return 0;
    if(pos==0){
        if(state && !(is8 && is4) ) return 1;
        else return 0;
    }
    if(!lead && !limit && dp[pos][u][v][state][is8][is4] != -1) return dp[pos][u][v][state][is8][is4];
    int up = (limit?num[pos]:9);
    int ans=0;
    for(int i=0;i<=up;i++){
        bool h8=false,h4=false,islead=false;
        if(i==8) h8=true;
        else if(i==4) h4=true;
        else if(lead && i==0) islead = true;

        if(u==v && i==u) ans+=dfs(pos-1,i,u,true,is8 | h8,is4 | h4,islead,limit && i==up);
        else ans+=dfs(pos-1,i,u,state,is8 | h8,is4 | h4,islead,limit && i==up);
    } 
    if(!limit && !lead) dp[pos][u][v][state][is8][is4] = ans;
    return ans;
}
int solve(llg x){
    int len=0;
    while(x){
        num[++len]=x%10;
        x/=10;
    }
    memset(dp,-1,sizeof(dp));
    return dfs(len,10,10,false,false,false,true,true);
}
#endif

llg dfs(int pos,int u,int v,bool state,bool is8,bool is4,
/*E1:bool lead, 避开前导0——因为手机号可以直接让开头从1-9开始*/bool limit){
    if(is8 && is4) return 0; //E2:因为8和4不能直接出现，所以同时出现直接返回0；
    if(!pos) return state; //E3:当0位时，直接把state的值进行返回
    if(!limit && dp[pos][u][v][state][is8][is4] != -1) return dp[pos][u][v][state][is8][is4];
    int up = (limit ? num[pos] : 9);
    llg ans = 0;
    for(int i=0;i<=up;i++){ //E4：直接把几个项目合并
        ans += dfs(pos-1,i,u,state || (i==u && i==v),is8 || (i==8),is4 || (i==4),limit && (i==up));
    }
    if(!limit) dp[pos][u][v][state][is8][is4] = ans;
    return ans;
}
llg solve(llg x){
    int len=0;
    while(x){
        num[++len]=x%10;
        x/=10;
    }
    //---------------------------------------------------
    if(len!=11) return 0; //！！！！Error:注意这里必须要满足11位才有价值
    //---------------------------------------------------
    memset(dp,-1,sizeof(dp));
    llg ans = 0;
    for(int i=1;i<=num[len];i++){ //最高位1-9，需要避开前导0问题
        ans += dfs(len-1,i,0,false,i==8,i==4,i==num[len]);
    }
    return ans;
}
int main(){
    llg a,b; cin >>a >> b;
    cout << solve(b)-solve(a-1);
    return 0;
}
  