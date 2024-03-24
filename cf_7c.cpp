/*
https://codeforces.com/problemset/problem/7/C

扩展欧几里得

题意很明了，就是让你给出一组x，y的值符合这个等式成立，
他会给你A，B，C的值。这是一个拓展的欧几里得，
Ax + By = gcd(A,B)这种形式的，
但是我们这个式子得变形两边都除以A和B的最大公约数得到
A（x/gcd(A,B)） + B（y/gcd(A,B)） = 1，
然后两边乘以-C变成
A（x*（-C）/gcd(A,B)） + B（y*(-C)/gcd(A,B)） = -C，
为了让答案成为整数，
我们使得（-C）%gcd(A,B) == 0;这样就能求出最后答案了。
*/
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
