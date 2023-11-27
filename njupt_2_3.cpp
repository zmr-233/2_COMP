#include<bits/stdc++.h>
using namespace std;
typedef long long llg;
const llg INF = 2147483647;

//用于从重定向0_in/a.in和0_out/a.out读取文件
#define yyj(a) freopen("0_in/"a".in","r",stdin),freopen("0_out/"a".out","w",stdout);

//读取一个整数
inline llg getint()
{
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ? -w : w;
}
bool fun(int num){
    string s;
    while(num){
        if(num%2==1) s+='1';
        else s+='0';
        num/=2;
    }
    int a{},b{};
    for(auto i:s){
        if(i=='1') a++;
        else b++;
    }
    if(a>b) return true;
    else return false;

}
int main(){
    int a{},b{};
    for(int i=1;i<=1000;i++){
        if(fun(i))a++;
        else b++;
    }
    cout << a << " " << b <<endl;
    return 0;
}