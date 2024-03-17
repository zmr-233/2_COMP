/*

abab:

a|baba|bab
0|7050|301
bab|abab|a
070|5030|1

7mod4=3

n=4
a|baba|bab
bab|abab|a
070|5030|1

7mod4=3 
if(i-3<0)continue;

5mod4=3
i-3>0
4-3=1
for(j=1->4)
b[i+j] == a[2*n-j]

cga:
*|agc|cga
*|600|001
agc|cga|*
600|001|*

abc:
ab|cba|c
00|100|1
c|abc|ba
0|300|01

abcde:
abc|edcba|de
000|20000|01
ed|abcde|cba
00|30000|001

ab|edcba|cde
edc|abcde|ba
000|20000|01

*|edcba|abcde
edcba|abcde|*

abcde|edcba|*
*|abcde|edcba

aabaaab:
aa|baaabaa|baaab
00|@000300|50001
baaab|aabaaab|aa
02510|9102510|21

N=7
aabaaab|baaabaa|*
*|aabaaab|baaabaa
*|$102310|0251021


atcodeer
00000001
reedocta
10000000

2*N=14 N=7
aa|baaabaa|baaab
00|@000300|50001
baaab|aabaaab|aa
02510|9102510|21

9mod7=2
7-2=5

abcedcbade
0002000001
edabcdecba
0030000001

abababab
07050301
babababa
07050301

*/
/*
n=4
a|baba|bab
bab|abab|a
070|5030|1

7mod4=3 
if(i-3<0)continue;

5mod4=3
i-3>0
4-3=1
for(j=1->4)
b[i+j] == a[2*n-j]
*/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000050;
char t[2*MAXN];
int Next[2*MAXN];
vector<int> z_fun(string s){
    int n=s.size();
    vector<int> z(n);
    for(int i=0,l=0,r=0;i<n;++i){
        if(i<=r && z[i-l]<r-i+1){
            z[i]=z[i-l];
        }else{
            z[i]=max(0,r-i+1);
            while(i+z[i]<n && s[z[i]]==s[z[i]+i]) ++z[i];
        }
        if(i+z[i]-1>r) l=i, r=i+z[i]-1;
    }
    return z;
}
vector<int> extend(string a,string b){
    int n=a.size();
    vector<int> e(n);
    for(int i=0,l=0,r=0;i<n;++i){
        if(i<=r && e[i-l]<r-i+1){
            e[i]=e[i-l];
        }else{
            e[i]= max(0,r-i+1);
            while(i+e[i]<n && a[e[i]]==b[e[i]+i]) ++e[i];
        }
        if(i+e[i]-1>r) l=i, r=i+e[i]-1;
    }
    return e;
}
/*
aabaaab:
aa|baaabaa|baaab
00|@000300|50001
baaab|aabaaab|aa
02510|9102510|21
02523|9252342|21

*/
int main(){
    string a; cin >> a;
    string b(a);
    reverse(b.begin(),b.end());
    vector<int> e = extend(a,b);
    cout << b << endl;
    for(auto i:e)
        cout << i;
}
