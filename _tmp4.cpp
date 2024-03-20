#include<bits/stdc++.h>
using namespace std;
typedef long long llg;
llg binpow(llg a,llg b){
    llg res = 1;
    while(b>0){
        if(b & 1) res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}
llg binpow(llg a,llg b,llg m){
    a%=m;
    llg res=1;
    while(b>0){
        if( b & 1) res=res*a%m;
        a=a*a%m;
        b>>=1;
    }
    return res;
}
bool isprime(llg num){
    if(llg <2) return 0;
    for(llg i=2;i*i<=a;++i)
        if(a%i==0) return 0;
    return 1;
}
int test_time =8;
bool millerRabin(int n){
    if(n<3) return n==2;
    for*
}