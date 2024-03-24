#include<bits/stdc++.h>
using namespace std;
typedef long long llg;
const int MAXN = 100000001;
bool check[MAXN+10];
int phi[MAXN+10];
int prime[MAXN+10];
int tot;

void phifun(int N){
    memset(check,false,sizeof(check));
    phi[1] = 1;
    tot = 0;
    for(int i = 2; i <= N; i++){
        if( !check[i] ){
            prime[tot++] = i;
            phi[i] = i-1;
        }
        for(int j = 0; j < tot; j++){
            if(i * prime[j] > N) break;
            check[i * prime[j]] = true;
            if( i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else{
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}

int main() {
    phifun(MAXN);
    int a;
    while((~scanf("%d",&a)) && a!=0)
        printf("%d\n",a-1-phi[a]); 
}