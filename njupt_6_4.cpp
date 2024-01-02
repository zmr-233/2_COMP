#ifdef USEERROR
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
int nums[MAXN];
llg ans;
int n,a,b;
int main(){
    cin >> n >> a >> b;
    for(int ii=1;ii<=n;ii++) scanf("%1d",&nums[ii]);
    int i=1,j=n;
    for(;i!=j;i++,j--){
        if(nums[i]!=nums[j] && nums[i]!=2 && nums[j] !=2){
            cout << -1;
            return 0;
        }else if(nums[i]!=nums[j] && nums[i]==2){
            switch(nums[j]){
            case 0:
                ans +=a;
                break;
            case 1:
                ans +=b;
                break;
            }
        }else if(nums[i]!=nums[j] && nums[j]==2){
            switch(nums[i]){
            case 0:
                ans +=a;
                break;
            case 1:
                ans +=b;
                break;
            }
        }else if(nums[i]==nums[j] && nums[i]==2 && nums[j]==2){
            ans += 2*min(a,b);
        }
    }
    if(i ==j && nums[i]==2) ans+=min(a,b);
    cout << ans;
    return 0;
}
#endif
#ifdef USEERROR2
#include<bits/stdc++.h>
using namespace std;

typedef long long llg;
const llg INF = 2147483647;

const int MAXN = 100010;
int nums[MAXN];
llg ans;
int n, a, b;

int main() {
    cin >> n >> a >> b;
    for (int ii = 1; ii <= n; ii++) scanf("%1d", &nums[ii]);
    int i = 1, j = n;
    while (i <= j) {
        if (nums[i] != nums[j]) {
            if (nums[i] == 2 && nums[j] == 2) {
                ans += min(a, b);
            } else if (nums[i] == 2) {
                ans += (nums[j] == 0) ? a : b;
            } else if (nums[j] == 2) {
                ans += (nums[i] == 0) ? a : b;
            } else {
                cout << -1;
                return 0;
            }
        }
        if (i == j && nums[i] == 2) ans += min(a, b);
        i++, j--;
    }
    //if(i ==j && nums[i]==2) ans+=min(a,b);
    cout << ans;
    return 0;
}
#endif
#include<bits/stdc++.h>
using namespace std;

typedef long long llg;
const llg INF = 2147483647;

const int MAXN = 100010;
llg nums[MAXN];
int ans;
int n, a, b;

int main() {
    cin >> n >> a >> b;
    for (int ii = 1; ii <= n; ii++) scanf("%d", &nums[ii]);
    int i = 1, j = n;
    while (i <= j) {
        if (nums[i] != nums[j]) {
            if (nums[i] == 2) {
                ans += (nums[j] == 0) ? a : b;
            } else if (nums[j] == 2) {
                ans += (nums[i] == 0) ? a : b;
            } else {
                cout << -1;
                return 0;
            }
        }else if(i!=j && nums[i] == 2 && nums[i]==nums[j]) ans += 2*min(a, b);
        else if (i == j && nums[i] == 2) ans += min(a, b);
        i++, j--;
    }
    cout << ans;
    return 0;
}

