#include<bits/stdc++.h>
using namespace std;

typedef long long llg;
const llg INF = 2147483647;

//#define yyj(a) freopen("0_in/"a".in","r",stdin),freopen("0_out/"a".out","w",stdout);
#define yyj(a) freopen(("0_in/" + string(a) + ".in").c_str(),"r",stdin),freopen(("0_out/" + string(a) + ".out").c_str(),"w",stdout)
inline llg getint()
{
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); 
    while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ? -w : w;
}

vector<int> LPS(const string& str) {
    int n = str.size();
    vector<int> lps(n, 0);
    int len = 0;
    int i = 1;

    while (i < n) {
        if (str[i] == str[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

string solve(const string& s) {
    vector<int> lps = LPS(s);
    int n = s.size();
    int len = lps[n-1];

    bool found = false;
    for (int i = 0; i < n - 1; i++) {
        if (lps[i] == len) {
            found = true;
            break;
        }
    }
    while (len > 0 && !found) {
        len = lps[len - 1];
        for (int i = 0; i < n - 1; i++) {
            if (lps[i] == len) {
                found = true;
                break;
            }
        }
    }

    if (len > 0 && found) {
        return s.substr(0, len);
    } else {
        return "Just a legend";//ABCDABD [0, 0, 0, 0, 1, 2, 0]
        //AABAAAB [0, 1, 0, 1, 2, 2, 3]
        /*
        i--当前元素 len--当前最长匹配长度 lps[i]--当前元素的最长匹配长度
        for i
        if w_i==w_len : len++ lps_i=len i++
        else if len!=0: len=lps_{len-1}
        else : lps_i=0 i++
        */
    }
}

int main() {
    string s;cin >> s;
    cout << solve(s) << endl;
    return 0;
}
