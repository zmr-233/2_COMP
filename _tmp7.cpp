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