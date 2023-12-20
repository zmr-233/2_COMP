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

const int MAXN = 110;
int dp[MAXN];
int c[MAXN][MAXN];
int w[MAXN][MAXN];
int N,M;
int main(){
    while(scanf("%d %d",&N,&M) && N && M){
        for(int i=1;i<=N;i++)
            for(int k=1;k<=M;k++){ 
                cin >> w[i][k];
                c[i][k]=k; //有时候会遇到物品'体积'就是日期之类，哪怕`c[i][k]==k`也不要偷懒不写c[][]，否则会把自己绕昏
            } 
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=N;i++)
            for(int j=M;j>=1;j--)
                for(int k=1;k<=M;k++)
                    if(j-c[i][k]>=0)
                        dp[j]=max(dp[j],dp[j-c[i][k]]+w[i][k]);

        cout << dp[M] << endl;
    }
    return 0;
}

