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


#ifdef USE_DP
/**
 * A-数位统计DP  递推实现
*/
const int N = 18;
llg ten[N],dp[N];
llg cnta[N],cntb[N];
llg num[N];
void init(){
    ten[0]=1;
    for(int i=1;i<N;i++){
        dp[i]=i*ten[i-1];
        ten[i]=10*ten[i-1];
    }
}
void solve(llg x,llg* cnt){
    int len=0;
    while(x){
        num[++len]=x%10;
        x/=10;
    }
    for(int i=len;i>=1;i--){
        //A-常规：小一位
        for(int j=0;j<=9;j++) cnt[j] += dp[i-1]*num[i];
        //B-最高位：小于num[i]
        for(int j=0/*包含0*/;j<num[i];j++) cnt[j] += ten[i-1];
        //C-最高位：刚好是num[i]
        llg tmp=0;
        for(int j=i-1;j>=1;j--) tmp = 10*tmp + num[j];
        cnt[num[i]] += tmp +1 ;
        /*ERROR:
        cnt[num[i]] += tmp; 这里缺少了300这种情况
        应当+1l
        */
        //最后处理--去除前缀0
        cnt[0]-=ten[i-1]; //这里已经相当于1*ten[i-1]
    }
}
int main(){
    init(); //ERROR:忘记加初始化
    llg a,b;
    cin >> a >> b;
    solve(a-1,cnta),solve(b,cntb);
    /**
     * 注意！
     * 区间[a,b]等于[1,a-1]与[1,b]的差分
     * 不要写成solve(a,cnta)！！！！！
    */
    for(int i=0;i<=9;i++)
        cout << cntb[i]-cnta[i] << " ";
    return 0;
}
#endif
#define USE_DP2
#ifdef USE_DP2
/**
 * B-数位统计DP  记忆化搜索实现
*/
const int N=15;
llg dp[N][N];
int num[N],now; //now:统计的是当前0-9的哪一个数字

llg dfs(int pos,int sum,bool lead,bool limit){ //pos:当前处理到第pos位
    if(pos==0) return sum; //递归到0位，结束
    if(!lead && !limit && dp[pos][sum]!=-1) return dp[pos][sum]; //记忆化搜索
    
    int up = (limit?num[pos]:9); //这一位的最大值，如324第3位就是Up=3
    llg ans=0; //下面以324 now=2(pos=3)为例
    for(int i=0;i<=up;i++){
        //A-计算000-099
        if(i==0 && lead) ans += dfs(pos-1,sum,true,limit && i==up);
        //B-计算200-299
        else if(i==now) ans += dfs(pos-1,sum+1,false,limit && i==up);
        //C-计算100-199
        else if(i!=now) ans += dfs(pos-1,sum,false,limit && i==up);
    }
    if(!lead && !limit) dp[pos][sum]=ans; //注意：有且只有无前导且无数位限制，才能放入dp
    return ans;
}
llg solve(llg x){
    int len=0;
    while(x){
        num[++len]=x%10;
        x/=10;
    }
    memset(dp,-1,sizeof(dp));
    return dfs(len,0,true,true);
}
int main(){
    llg a,b; cin >> a>>b;
    for(int i=0;i<=9;i++) now=i,cout << solve(b)-solve(a-1) << " ";
    return 0;
}
#endif