#include<bits/stdc++.h>
using namespace std;

typedef long long llg;
const llg INF = 2147483647;

#define yyj(a) freopen("0_in/"a".in","r",stdin),freopen("0_out/"a".out","w",stdout);

inline llg getint()
{
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ? -w : w;
}
const int MAXN = 10e5+10;
llg a[MAXN],sa[MAXN];
llg n,s;
int main(){
    int t; cin >> t;
    for(int tt=1;tt<=t;tt++){
        cin >> n >> s;
        for(int i=1;i<=n;i++){
            cin >> a[i];
            sa[i]=sa[i-1] + a[i];
        }
        int i=1,j=1, min_l = n;
        for(;i<=n;i++){
            while(j<n && sa[j]-sa[i] < s) j++;
            if(sa[j]-sa[i] >= s)
                min_l = min(min_l,j-i);
        }
        cout << min_l << endl;
    }
    return 0;
}
