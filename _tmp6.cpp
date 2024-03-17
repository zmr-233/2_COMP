#include<bits/stdc++.h>
using namespace std;

vector<int> primefac(int n) {
    vector<int> fac;
    while (n % 2 == 0) {
        fac.push_back(2);
        n = n / 2;
    }
    for (int i = 3; i * i <= n; i = i + 2) {
        while (n % i == 0) {
            fac.push_back(i);
            n = n / i;
        }
    }
    if (n > 2) fac.push_back(n);
    return fac;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> fac = primefac(n);
    if (fac.size() < k) {
        cout << -1 << endl;
        return 0;
    }

    while (fac.size() > k) {
        int last = fac.back();
        fac.pop_back();
        fac.back() *= last;
    }

    for (int factor : fac) {
        cout << factor << " ";
    }
    cout << endl;

    return 0;
}
