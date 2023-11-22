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

//A-不知所然的尺取法
const int MAXN = 2*10e5+10;
llg a[MAXN];
llg n,m;
int main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> a[i];
    int l=1,r1=1,r2=1;
    sort(a+1,a+n+1);
    llg ans = 0;
    for(;l<=n;l++){
        while(r1<=n && a[r1]-a[l]<=m) r1++;
        while(r2<=n && a[r2]-a[l]<m) r2++;
        if(a[r2]-a[l] == m && a[r1-1]-a[l] == m && r1-1 >= 1) 
            ans+=r1-r2;
    }
    cout << ans;
    return 0;
}
//B-STL map大法
/**
 * 对每一个s[i]建立一个映射，然后查询s[i]-c的个数即可
*/
    #include <iostream>
    #include <map>
    using namespace std;
    map<llg,llg> map_;//建立一个数字到出现次数的映射 map<num,times>
    //A-B=C --> A-C=B
    int main() {
        int n;
        llg ans=0;
        cin >> n >> m;
        for(int i=1;i<=n;i++) {
            cin >> a[i];
            map_[a[i]]++;
            a[i]-=m;    
        } 
        for(int i=1;i<=n;i++) ans+=map_[a[i]];
        cout << ans << endl;
        return 0;
}
