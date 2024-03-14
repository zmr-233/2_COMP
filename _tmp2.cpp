#include <bits/stdc++.h>
using namespace std;

#ifdef local
#include</Users/zhanyi/Desktop/template/debug>
#else
#define dbg(...)
#endif


using i64 = long long;


void solve() {
    string s;
    cin >> s;
    
    int n = s.size();
    s = " " + s;

    vector<int> z(n + 1);
    int L = 1, R = 0;
    for (int i = 2; i <= n; i++) {
        if (i > R) {
            z[i] = 0;
        } else {
            int k = i - L + 1;
            z[i] = min(z[k], R - i + 1);
        }
        while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) {
            z[i]++;
        }
        if (i + z[i] - 1 > R) {
            L = i, R = i + z[i] - 1;
        }
    }

    vector<i64> d(n + 2);
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (i + z[i] - 1 == n) {
            ans.push_back(z[i]);
        }
            d[z[i] + 1]--;
            d[1]++;
    }
    d[1]++;
    d[n + 1]--;
    for (int i = 1; i <= n; i++) {
        d[i] += d[i - 1];
    }
 
    cout << ans.size() + 1 << "\n";
    sort(ans.begin(), ans.end());
    for (auto x : ans) {
        cout << x << " " << d[x] << "\n";
    }

    cout << n << " " <<  "1\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}