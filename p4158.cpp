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
    return q ?  -w : w;
}
/**
 * # [SCOI2009] 粉刷匠
## 题目描述
windy 有 $N$ 条木板需要被粉刷。 每条木板被分为 $M$ 个格子。 
每个格子要被刷成红色或蓝色。windy 每次粉刷
只能选择一条木板上一段连续的格子，然后涂上一种颜色。 
每个格子最多只能被粉刷一次。
如果 windy 只能粉刷 $T$ 次，他最多能正确粉刷多少格子？
一个格子如果未被粉刷或者被粉刷错颜色，就算错误粉刷。

## 输入格式
第一行包含三个整数，$N,M,T$。
接下来有 $N$ 行，每行一个长度为 $M$ 的字符串，
``0`` 表示红色，`1` 表示蓝色。
## 输出格式
包含一个整数，最多能正确粉刷的格子数。

## 样例 #1
3 6 3
111111
000000
001100

### 样例输出 #1
16
*/
/**
 * 标准题解:
 * 易错点:状态过度压缩，明明每个方格都可以分为:
 * 涂了正确颜色 & 没有涂正确颜色
 * 
 * 这意味着必须要dp[i][j][color[i]]才行，
 * 否则下一个格子涂色要同时依赖于该格子是否正确/没有正确的dp数
 * 
 * 一道典型的两次DP：
 * A.在每一个木条上的DP
 * 1.直接从上一个格子刷过来：
 * dp[i][j][color[i]]=dp[i-1][j][color[i]]+1;
   dp[i][j][!color[i]]=dp[i-1][j][!color[i]];

   2.从此格开始涂新的一段，颜色与此格相同，则有转移方程
   dp[i][j][color[i]]=max(
    dp[i][j][color[i]],
    max(dp[i-1][j-1][0],dp[i-1][j-1][1])+1 
    );
    这里因为新涂什么样，都和上一格颜色无关，故取最大值

    3.从此格开始涂新的一段，颜色与此格不同，则有转移方程
    dp[i][j][!color[i]]=max({
        dp[i][j][!color[i]],
        dp[i-1][j-1][0],
        dp[i-1][j-1][1]
        });
*/
const int MAXN=2510;
int dp[MAXN][2];
int color[MAXN];
int ans[MAXN];
int n,m,C;
int main(){
    cin >> n >> m >> C;
    for(int o=0;o<n;o++){
        for(int i=1;i<=m;i++)
            scanf("%1d",&color[i]); //ERROR:每次只读取一个字符，却拿着cin>>color[i]读
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=m;i++){
            for(int j=C;j>=1;j--){
                //1.直接从上一个格子刷过来：
                dp[j][color[i]]=dp[j][color[i]]+1;
                dp[j][!color[i]]=dp[j][!color[i]];
                //2.从此格开始涂新的一段，颜色与此格相同
                int tmax=max(dp[j-1][1],dp[j-1][0]);
                dp[j][color[i]]=max(dp[j][color[i]],tmax+1);
                //3.从此格开始涂新的一段，颜色与此格不同
                dp[j][!color[i]]=max(dp[j][!color[i]],tmax);

            }
        }
        for(int j=C;j>=0;j--)
            for(int k=1;k<=m;k++)
                if(j-k>=0)
                    ans[j]=max(ans[j],ans[j-k]+max(dp[k][1],dp[k][0]));
    }
    cout << ans[C];
    return 0;
}
#ifdef USE_ERROR
//使用交替滚动ERROR
const int MAXN = 2510;
int dp[2][MAXN];
int out[2][MAXN];
int n,m,C;
int main(){
    cin >> n >> m >> C;
    int cur_=1,old_=0;
    for(int o=0;o<n;o++){
        int cur=1,old=0;
        string s; cin >> s;
        for(int j=1;j<=C;j++)
            dp[old][j]=1;
        for(int i=1;i<s.size();i++){
            for(int j=1;j<=C;j++){
                if(s[i]==s[i-1])
                    dp[cur][j]=dp[old][j]+1;
                else
                    dp[cur][j]=max(dp[old][j],dp[old][j-1]+1);

            }
            swap(cur,old);
        }
        /**
         * ERROR:重大错误
         * 对于分组背包问题，已经相当于两层DP
         * 否则对于for(k:m)的每一个k
         * 也必须进行一次swap(cur_,old_)
         * 
         * 
         * 除此之外，与书上不同，
         * else必须out[cur_][j]=max(out[cur_][j],out[old_][j]);
        */
        for(int k=1;k<=C;k++){
            for(int j=1;j<=C;j++){
                if(j-k>=0){
                    out[cur_][j]=max(
                        out[old_][j],
                        out[old_][j-k]+dp[old][k]
                    );
                }
                /*
                else
                    out[cur_][j]=max(out[cur_][j],out[old_][j]);
                */
            }
            swap(cur_,old_); //严重错误
        }
        swap(cur_,old_);
    }
    cout << out[old_][C];
    return 0;
}
#endif
#ifdef USE_AC30
//使用自我滚动且AC30分
const int MAXN = 2510;
int dp[2][MAXN];
int out[MAXN];
int n,m,C;
int main(){
    cin >> n >> m >> C;
    int cur_=1,old_=0;
    for(int o=0;o<n;o++){
        int cur=1,old=0;
        string s; cin >> s;
        for(int j=1;j<=C;j++)
            dp[old][j]=1;
        for(int i=1;i<s.size();i++){
            for(int j=1;j<=C;j++){
                if(s[i]==s[i-1])
                    dp[cur][j]=dp[old][j]+1;
                else
                    dp[cur][j]=max(dp[old][j],dp[old][j-1]+1);

            }
            swap(cur,old);
        }
        for(int j=C;j>=0;j--) 
            for(int k=1;k<=C;k++)
                if(j>=k)
                    out[j]=max(out[j],out[j-k]+dp[old][k]);
    }
    cout << out[C];
    return 0;
}
#endif