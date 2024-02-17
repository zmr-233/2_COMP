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

int fun(int n, int k) {
    if (n == 1) return 0;
    if (k == 1) return n - 1;
    
    if (k > n) return (fun(n - 1, k) + k) % n;
    int res = fun(n - n / k, k);
    res -= n % k;
    if (res < 0)
        res += n;
    else
        res += res / (k - 1); 
    return res;
}
int main() {
    llg n, m;
    cin >> n >> m;
    cout << fun(n, m);
    return 0;
}