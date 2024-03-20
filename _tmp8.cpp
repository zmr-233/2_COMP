#include<bits/stdc++.h>
using namespace std;
typedef long long llg;
llg  g,x,y;
void gcd(llg  a,llg  b){
    if(b==0)
        g=a,x=1,y=0;
    else{
        gcd(b,a%b);
        swap(y,x);
        y=y-x*(a/b);
    }
}
int main()
{
    llg a,b,c;
    while(~scanf("%lld%lld%lld",&a,&b,&c))
    {
        c=-c;
        gcd(a,b);
        if(c%g)
            printf("-1\n");
        else
        {
            printf("%lld %lld\n",x*c/g,y*c/g);
        }
    }
    return 0;
    /*x=gcd y*/
}
