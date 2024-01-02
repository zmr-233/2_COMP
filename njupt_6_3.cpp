#ifdef USEERROR
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
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ? -w : w;
}

const int MAXN = 100010;

int n,m;
llg nums[MAXN];
llg dp[MAXN];
int main(){
    cin >> n >> m;
}
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 100100;
int fireworks[MAXN];
int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> fireworks[i];
    }

    while (m--) {
        int l, r;
        cin >> l >> r;
        int max_beauty = 0;
        for (int i = l - 1; i < r; ++i) {
            max_beauty = max(max_beauty, fireworks[i]);
        }
        cout << max_beauty << endl;
    }

    return 0;
}
#endif
/**
 * 使用线段树
*/
#include<bits/stdc++.h>
using namespace std;

struct SegmentTreeNode {
    int start, end, max;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int s, int e) : start(s), end(e), max(0), left(nullptr), right(nullptr) {}
};

SegmentTreeNode* buildTree(const vector<int>& nums, int start, int end) {
    if (start > end) return nullptr;
    SegmentTreeNode* root = new SegmentTreeNode(start, end);
    if (start == end) {
        root->max = nums[start];
    } else {
        int mid = start + (end - start) / 2;
        root->left = buildTree(nums, start, mid);
        root->right = buildTree(nums, mid + 1, end);
        root->max = max(root->left->max, root->right->max);
    }
    return root;
}

int query(SegmentTreeNode* root, int start, int end) {
    if (!root || start > end) return INT_MIN;
    if (root->start == start && root->end == end) return root->max;
    int mid = root->start + (root->end - root->start) / 2;
    if (end <= mid) {
        return query(root->left, start, end);
    } else if (start > mid) {
        return query(root->right, start, end);
    } else {
        return max(query(root->left, start, mid), query(root->right, mid + 1, end));
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> fireworks(n);
    for (int i = 0; i < n; i++) {
        cin >> fireworks[i];
    }

    SegmentTreeNode* root = buildTree(fireworks, 0, n - 1);

    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        cout << query(root, l - 1, r - 1) << endl;
    }

    return 0;
}


