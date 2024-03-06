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

bool solve(const vector<int>& window, const vector<int>& pattern, const map<int, int>& rankMap) {
    vector<int> windowPattern(window.size());
    for (size_t i = 0; i < window.size(); ++i) {
        windowPattern[i] = rankMap.at(window[i]);
    }
    return windowPattern == pattern;
}

int main() {
    int N, K, S;
    cin >> N >> K >> S;

    vector<int> cows(N);
    for (int i = 0; i < N; ++i) {
        cin >> cows[i];
    }

    vector<int> pattern(K);
    for (int i = 0; i < K; ++i) {
        cin >> pattern[i];
    }

    vector<int> indices;
    for (int i = 0; i <= N - K; ++i) {
        vector<int> window(cows.begin() + i, cows.begin() + i + K);
        map<int, int> rankMap;
        set<int> uniqueSpots(window.begin(), window.end());

        int rank = 1;
        for (int spot : uniqueSpots) {
            rankMap[spot] = rank++;
        }

        if (solve(window, pattern, rankMap)) {
            indices.push_back(i + 1); // +1
        }
    }

    cout << indices.size() << endl;

    return 0;
}