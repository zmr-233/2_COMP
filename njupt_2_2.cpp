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
bool check(int num){
    int tmp = num;
    int i3 = num %10; num/=10;
    int i2 = num %10; num/=10;
    int i1 = num %10; num/=10;
    if(tmp==i3*i3*i3 + i2*i2*i2 + i1*i1*i1)
        return true;
    return false;
}
int main(){
    for(int i=100;i<=999;i++){
        if(check(i))
            cout << i << endl;
    }
    return 0;
}