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

const int MAXN = 100010;
llg nums[MAXN],n;
llg a[MAXN],c=0;
int main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        nums[i]=getint();
        a[i]=a[i-1]+nums[i];
    }
    sort(a+1,a+n+1);
    int ans=0;
    for(int i=1,j=1;i<=n;i=j){
        while(j<=n && a[i]==a[j]) j++;
        ans += j-1-i; 
    }
    cout << ans;
    return 0;
}