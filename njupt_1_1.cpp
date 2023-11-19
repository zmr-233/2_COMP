#include<bits/stdc++.h>
using namespace std;
typedef long long llg;
const llg INF = 2147483647;

#define yyj(a) freopen("0_in/"a".in","r",stdin),freopen("0_out/"a".out","w",stdout);

inline llg getint(){
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ? -w : w;
}
const int MAXN = 1000010;
llg a[MAXN],n;
set<int> factors;
bool check(llg num){
    for(int i=2;i*i <= num; i++)
        if(num%i == 0) return true;
    return false;
}
void findFactor(llg num){
    llg tmp = num;
    while (num % 2 == 0) {
        factors.insert(2);
        num /= 2;
    }
    for (int i = 3; i <= sqrt(num); i += 2)
        while (num % i == 0) {
            factors.insert(i);
            num /= i;
        }
    if (num > 2)
        factors.insert(num);
}
int main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        llg num = getint();
        if(check(num))
            findFactor(num);
    }
    for(auto i:factors)
        cout << i << " ";
    return 0;
}

