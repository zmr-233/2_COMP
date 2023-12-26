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
const int MAXN = 2010;
int dp[2][MAXN];
int main(){
    string a,b;
    cin >> a; cin >>  b;
    int cur=1,old=0;
    for(int j=1;j<=b.size();j++)
        dp[old][j]=j;
    /**
     * 易错: 
     * 需要进行初始化：
     * dp[old][j]=j 
     * dp[cur][0]=i
    */
    for(int i=1;i<=a.size();i++){
        dp[cur][0]=i;
        for(int j=1;j<=b.size();j++){
            if(a[i-1]==b[j-1])
                dp[cur][j]=dp[old][j-1];
            else
                dp[cur][j]=
                    min({dp[cur][j-1],dp[old][j],dp[old][j-1]})+1;
        }
        swap(old,cur);
    }
    cout << dp[old][b.size()];
    return 0;
}