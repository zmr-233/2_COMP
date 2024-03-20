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

2*N=14 N=7
abcdgfedcbaefg
gfe|abcdefgdcba
000|40000000001

4mod7 = 4
7-4=3

CMP:
i(a)+4->e
2*N-3->e
for(j=3 j<7)
a[2*N-3]

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
    z[0] = n;
    return z;
}
template <class T> std::vector<int> z_algorithm(const std::vector<T>& s) {
    int n = int(s.size());
    if (n == 0) return {};
    std::vector<int> z(n);
    z[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        int& k = z[i];
        k = (j + z[j] <= i) ? 0 : std::min(j + z[j] - i, z[i - j]);
        while (i + k < n && s[k] == s[i + k]) k++;
        if (j + z[j] < i + z[i]) j = i;
    }
    z[0] = n;
    return z;
}
std::vector<int> z_algorithm(const std::string& s) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return z_algorithm(s2);
}

vector<int> extend(string a,string b){
    string s = a+b;
    //cout << s<<endl;
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
    return vector<int>(z.begin()+n/2,z.end());
}
/*
aabaaab:
aa|baaabaa|baaab
baaab|aabaaab|aa
02510|9102510|21

aabaaabaabaaab
*/
/*
int main(){
    int n; cin >> n;
    string T; cin >> T;
    for(auto i:z_fun(T)) cout << i;
    cout <<endl;
    for(auto i:z_algorithm(vector<char>(T.begin(),T.end()))) cout << i;
    cout << endl;
    return 0;
    string b(T); reverse(b.begin(),b.end());
    vector<int> e = extend(T,b);
    //cout << b << endl;
    //for(auto i:e) cout << i;
    //cout << endl;
    for(int i=0;i<b.size();i++){
        if(e[i]!=0 ){
            int t = e[i] % n;
            bool success = true;
            for(int j=t;j<n;j++)
                if(i+t-j-1 >= 0 &&b[i+j]!=b[i+t-j-1]){
                    success = false;
                    break;
                }
            if(success){
                for(int j=0;j<n;j++)
                    cout << b[j+i];
                cout << endl << n-i;
                return 0;
            }
        }
    }
    puts("-1");
    return 0;
}
*/
int main() {
    int n;
    cin >> n;
    string t;
    cin >> t;
    
    string a = t.substr(0, n);
    string b = t.substr(n);
    reverse(b.begin(), b.end());
    
    string x = a + b;
    vector<int> za_x = z_algorithm(x);
    za_x.push_back(0);
/*
n = 7
aabaaab:
aa|baaabaa|baaab
baaab|aabaaab|aa

A:
aa|baaabaa|baaab
$1|0231002|51021|0
B:
baaab|aabaaab|aa
$0004|0000500|01|0

*/
    string y = b + a;
    vector<int> za_y = z_algorithm(y);
    za_y.push_back(0);
    
    for(auto i:za_x) cout << i;
    cout << endl;
    for(auto i:za_y) cout << i;
    cout << endl;
    for (int i = 0; i <= n; i++) {
        if(za_x[2 * n - i] < i) continue;
        if(za_y[n + i] < n - i) continue;
        cout << t.substr(0, i) + t.substr(n + i) << endl;
        cout << i << endl;
        return 0;
    }
    
    cout << -1 << endl;
}

