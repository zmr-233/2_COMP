#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 5 * 1e5 + 5;
vector<int> children[MAX_N];  // 存储树的结构
int happiness[MAX_N];         // 存储每个节点的快乐指数
pair<int, int> topTwo[MAX_N]; // 存储每个节点的两个最大快乐指数

void dfs(int node) {
    topTwo[node] = {happiness[node], 0}; // 初始化当前节点的快乐指数

    for (int child : children[node]) {
        dfs(child);
        int childHappiness = topTwo[child].first;
        if (childHappiness > topTwo[node].first) {
            topTwo[node].second = topTwo[node].first;
            topTwo[node].first = childHappiness;
        } else if (childHappiness > topTwo[node].second) {
            topTwo[node].second = childHappiness;
        }
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> happiness[i];
    }

    for (int i = 1; i < n; ++i) {
        int l, k;
        cin >> l >> k;
        children[k].push_back(l);
    }

    dfs(1); // 假设1号是校长，也是树的根节点

    cout << topTwo[1].first << " " << topTwo[1].second << endl;

    return 0;
}
