#include<bits/stdc++.h>
using namespace std;
typedef long long llg;
const int MAXN = 10050;
int prime[MAXN];
int is_prime[MAXN];
int Eratosthenes(int n){
    memset(is_prime,true,sizeof(is_prime));
    int p=0;
    is_prime[0]=is_prime[1]=0;
    for(int i=2;i<=n;i++){
        if(is_prime[i]){
            prime[p++]=i;
            if((llg)i*i<=n)
                for(int j=i*i; j<=n;j+=i)
                    is_prime[j]=0;
        }
    }
    return p;
}