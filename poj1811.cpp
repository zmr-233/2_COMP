/*http://poj.org/problem?id=1811

题意：给出 t 组数据，每组数据给出一个整数 n，如果 n 是素数就输出 Prime，不是素数就输出其最小因数

思路：组合使用 Pollard Rho 算法与 Miller Rabin 算法，可求出大整数的所有因子

*/
#include <iostream>
#include <ctime>
#include <algorithm>
#define LL long long
const int S=20;
LL factor[100];
int tot;
LL n;
using namespace std;
 
LL quickmult(LL a,LL b,LL mod) {
    a%=mod,b%=mod;
    LL ans=0;
    while(b>0){
        if(b&1) ans=(ans+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return ans;
}
LL quickpow(LL a,LL b,LL mod) {
    LL ans = 1;
    a%=mod;
    while(b>0){ 
        if(b&1) ans=quickmult(ans,a,mod)%mod;
        a=quickmult(a,a,mod)%mod;
        b>>=1;
    }
    return ans;
}

int test_time = 8;
bool Miller_Rabin(LL n) {
    if(n<3 || n%2==0) return n==2;
    LL u=n-1,t=0;
    while(u%2==0) u>>=1,t++;
    for(int i=1;i<test_time;i++){
        LL a=rand()%(n-2)+2, v=quickpow(a,u,n);
        if(v==1) continue;
        int s;
        for( s=0;s<t;s++){
            if(v==n-1) break;
            v=quickmult(v,v,n) %n;
        }
        if(s==t) return 0;
    }
    return 1;
}
LL gcd(LL a,LL b)
{
   /* if(b==0)
        return a;
    return gcd(b,a%b);*/
    if(a==0)
        return 1;
    if(a<0)
        return gcd(-a,b);
    while(b)
    {
        LL temp=a%b;
        a=b;
        b=temp;
    }
    return a;
}
LL Pollard_rho(LL x,LL c)
{
    LL i=1,k=2;
    LL x0=rand()%x;
    LL y=x0;
    while(true)
    {
        
        i++;
        x0=(quickmult(x0,x0,x)+c)%x;
        LL d=gcd(y-x0,x);
        if(d!=1&&d!=x)
           return d;
        if(y==x0)
            return x;
        if(i==k)
        {
            y=x0;
            k+=k;
        }
    }
}
void findfac(LL n)
{
    if(Miller_Rabin(n))
    {
        factor[tot++]=n;
        return ;
    }
    LL p=n;
    while(p>=n)
    {
        p=Pollard_rho(p,rand()%(n-1)+1);
    }
    findfac(p);
    findfac(n/p);
}
int main()
{
    int T;
    while(cin>>T)
    {
        while(T--)
        {
            cin>>n;
            tot=0;
            findfac(n);
            if(tot==1)
                cout<<"Prime"<<endl;
            else
            {
                sort(factor,factor+tot);
                cout<<factor[0]<<endl;
            }
        }
    }
    return 0;
}