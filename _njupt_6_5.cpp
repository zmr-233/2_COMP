//DP线段树离散化
#ifdef USEERROR1
#include <bits/stdc++.h>
using namespace std;

typedef long long llg;
const llg INF = 2147483647;

// #define yyj(a) freopen("0_in/"a".in","r",stdin),freopen("0_out/"a".out","w",stdout);
#define yyj(a) freopen(("0_in/" + string(a) + ".in").c_str(), "r", stdin), freopen(("0_out/" + string(a) + ".out").c_str(), "w", stdout)
inline llg getint()
{
    llg w = 0, q = 0;
    char c = getchar();
    while ((c < '0' || c > '9') && c != '-')
        c = getchar();
    if (c == '-')
        q = 1, c = getchar();
    while (c >= '0' && c <= '9')
        w = w * 10 + c - '0', c = getchar();
    return q ? -w : w;
}

const int MAXN = 100010;
llg nums[MAXN];
int n;
llg dp[MAXN];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> nums[i];
    llg max_m = 1;
    for (int i = 1; i <= n; i++)
    {
        llg max_n = 0;
        for (int j = 1; j < i; j++)
        {
            if (nums[i] & nums[j] != 0)
                max_n = max(max_n, dp[j]);
        }
        dp[i] = max_n + 1;
        max_m = max(max_m, dp[i]);
    }
    cout << max_m;
    return 0;
}
#endif
#include <bits/stdc++.h>
#define maxn 100005
#define maxp 31
using namespace std;
int n, a[maxn], dp[maxp], pw[maxp];
int main()
{
    pw[0] = 1;
    for (int i = 1; i < maxp; ++i)
        pw[i] = pw[i - 1] << 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; ++i)
    {
        int mx = 0;
        for (int j = 0; j < maxp; ++j)
        {
            if (a[i] & pw[j])
            {
                mx = max(mx, dp[j]);
            }
        }
        ++mx;
        for (int j = 0; j < maxp; ++j)
        {
            if (a[i] & pw[j])
            {
                dp[j] = max(dp[j], mx);
            }
        }
    }
    int mx = 0;
    for (int j = 0; j < maxp; ++j)
        mx = max(mx, dp[j]);
    printf("%d\n", mx);
    return 0;
}