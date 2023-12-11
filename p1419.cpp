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

const int MAXN = 100010;
const double eps = 1e-7;
llg a[MAXN];
int n,s,t;
double max_ave = -INF;
bool check(double mid){
    double max_tmp = -INF;
    int p=1; double cur = 0;
    for(int i=1;i<=n;i++){
        if(i-p>=t){p=i; cur=0;}
        cur += a[i];
        if(i-p+1>=s && cur - max_tmp > eps){
            max_tmp = cur;
        }
        if(cur<0){p=i+1;cur =0;}
    }

}

int main(){
    cin >> n >> s >> t;
    double maxx = -INF,minx = INF;
    for(int i=1;i<=n;i++){cin>>a[i];maxx=max(maxx,(double)a[i]),minx=min(minx,(double)a[i]);}
    double l=-10000,r=10000,ans = -1;
    while(r-l>eps){
        double mid = (l + r)/2;
        if(check(mid)) {l = mid; ans = mid;}
        else l = mid;
    }
}