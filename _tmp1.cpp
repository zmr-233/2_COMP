#include <bits/stdc++.h>
using namespace std;

#define SIZE 100005
#define ll long long int

int zs[SIZE];
int ps[SIZE];

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (r < i + z[i] - 1)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

vector<int> prefix_function(string s) {
    int n = (int) s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    vector<int> z = z_function(s);
    vector<int> p = prefix_function(s);

    ll cnt[SIZE] = {0}, prefix_suffix_count[SIZE] = {0};
    int m = s.size();

    for(int i=0; i<m; i++) {
        zs[z[i]]++;
        ps[p[i]]++;
    }

    for(int i=m; i>=1; i--)
        zs[i-1] += zs[i];
    for(int i=1; i<=m; i++)
        ps[i] += ps[i-1];

    vector<pair<int, int>> answer;
    for(int i=m-1; i>=0; i--) {
        cnt[p[i]]++;
        if(i == m - p[i]) {
            int l = p[i];
            prefix_suffix_count[l] = cnt[l];
        }
    }

    for(int len=m; len>0; len=p[len-1])
        answer.push_back(make_pair(len, zs[len]));
    
    reverse(answer.begin(), answer.end());

    cout << answer.size() << '\n';
    for(auto it: answer)
        cout << it.first << " " << it.second+1<< '\n';

    return 0;
}
