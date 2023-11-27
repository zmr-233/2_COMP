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


int main(){
    string s = "123456789";
    do{
        string s1 = s.substr(0, 3);
        string s2 = s.substr(3, 3);
        string s3 = s.substr(6, 3);

        int i1 = std::stoi(s1);
        int i2 = std::stoi(s2);
        int i3 = std::stoi(s3);
        if(i3 == 3*i1 && i2 == 2*i1)
            cout <<i1<<" " << i2<<" " << i3<<endl;
    }while(next_permutation(s.begin(),s.end()));
    return 0;
}
