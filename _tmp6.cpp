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
/*
题意很明了，就是让你给出一组x，y的值符合这个等式成立，
他会给你A，B，C的值。这是一个拓展的欧几里得，
Ax + By = gcd(A,B)这种形式的，
但是我们这个式子得变形两边都除以A和B的最大公约数得到
A（x/gcd(A,B)） + B（y/gcd(A,B)） = 1，
然后两边乘以-C变成
A（x*（-C）/gcd(A,B)） + B（y*(-C)/gcd(A,B)） = -C，
为了让答案成为整数，
我们使得（-C）%gcd(A,B) == 0;这样就能求出最后答案了。

*/