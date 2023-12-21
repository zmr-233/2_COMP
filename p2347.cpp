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
const int MAXN = 1000010;
llg c[]={0,1,2,3,5,10,20},m[10];
int n=6,C=1000;
int new_n;
llg new_c[MAXN],new_m[MAXN];
llg dp[MAXN];
set<llg> s;
int main(){
    for(int i=1;i<=6;i++)cin>>m[i];
    for(int i=1;i<=6;i++ ){
        for(int j=1;j<=m[i];j<<=1){
            m[i]-=j;
            new_c[++new_n]=j*c[i];
        }
        if(m[i]){
            new_c[++new_n]=m[i]*c[i];
        }
    }
    for(int i=1;i<=new_n;i++)
        for(int j=C;j>=new_c[i];j--){/*j>=new_c[i]*/
            dp[j]=max(dp[j],dp[j-new_c[i]]+new_c[i]);
            if(dp[j]!=0) s.insert(dp[j]);
        }
    cout <<"Total="<< s.size();
    return 0;
}