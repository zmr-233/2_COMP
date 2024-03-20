#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll ha1[2000005], ha2[2000005], p[2000005];
const ll mod = 1e9 + 7;
const ll P = 1331;

ll mo(ll x) {
    return (x % mod + mod) % mod;
}

void ha(string s) {
    int n = s.size();
    for (int i = 1; i <= n; i++) {
        ha1[i] = mo(ha1[i - 1] * P + s[i - 1]);
    }

    for (int i = n; i >= 1; i--) {
        ha2[i] = mo(ha2[i + 1] * P + s[i - 1]);
    }
}

ll get1(int l, int r) {
    if (l > r) return 0;
    return mo(ha1[r] - ha1[l - 1] * p[r - 1 + 1]);
}

ll get2(int l, int r) {
    if (l > r) return 0;
    return mo(ha2[1] - ha2[r + 1] * p[r - 1 + 1]);
}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    ha(s);
    p[0] = 1;
    for (int i = 1; i <= n * 2; i++) {
        p[i] = mo(p[i - 1] * P);
    }


    for (int i = 0; i <= n; i++) {
        if (get1(1, i) == get2(1 + n, i + n) && get2(i + 1, n) == get1(i + n + 1, n * 2)) {
            string a = s.substr(0, i) + s.substr(n + i);
            string b = s.substr(i, n);
            reverse(b.begin(), b.end());
            if (a == b) {
                cout << a << endl;
                cout << i << endl;
                return 0;
            }
        }
    }

    cout << -1 << endl;
}
//#include<bits/stdc++.h>
#include<iostream>
#include<string.h>
#include<cstdlib>
using namespace std;
typedef long long llg;
const int MAXN = 100010;
bool is_prime[MAXN];
llg prime[MAXN];
int init(int n){
    int p=0;
    memset(is_prime,true,sizeof(is_prime));
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<=n;i++){
        if(is_prime[i]){
            prime[p++]=i;
            if((llg)i*i<=n)
                for(int j=i*i;j<=n;j+=i)
                    is_prime[j]=false;
        }
    }
    return p;
}
llg binpow(llg a,llg b,llg m){
    a%=m;
    llg ans=1;
    while(b){
        if(b&1) ans = ans*a%m;
        a=a*a%m;
        b>>=1;
    }
    return ans;
}
int testtimes = 8;
bool fun0(llg a){
    return (a+1)%6==0 || (a-1)%6==0;
}
bool fun1(llg a){
    if(a<3) return a==2;
    for(int i=0;i<testtimes;i++){
        int b = rand()%(a-2)+2;
        if(binpow(b,a-1,a)!=1) return 0;
    }
    return 1;
     
}
int main(){
    int T; cin >> T;
    int p_maxn=100000;
    int p=init(p_maxn);
    for(int i=0;i<T;i++){
        llg num; cin >> num;
        if(fun0(num)
            && fun1(num)
         ){
            cout << "Prime"<<endl;
        }else{
            //cout << "No"<<endl;
            for(int j=0;j<p;j++)
                if(num%prime[j]==0){
                    cout << prime[j]<<endl;
                    break;
                }
        }
    }
}