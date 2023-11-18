//P5018--检验是否是对称二叉树
/**
 * 最终用这种方法，得了56分，其中：
 * 1.保证'完全二叉树'的情况下，AC2，WA2
 * 2.在保证'点权均为1'的情况下，WA4
 * 3.在'n<10e6'的情况下，全TLE
*/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000010;

int n,w[MAXN],l[MAXN],r[MAXN];
int max_node = 1;
void judge(list<int>& m,list<int>& n){
    if(m.size() != n.size() ) return;
    n.reverse();
    int n_node = 0;
    auto m_it = m.begin(); auto n_it = n.begin();
    while (m_it != m.end() && n_it != n.end()) {
        if (w[*m_it] != w[*n_it]) return;
        if (w[*m_it] != -1 && w[*n_it] != -1) n_node++;
        ++m_it;++n_it;
    }
    if(2*n_node + 1 > max_node) max_node = 2*n_node +1;
}
list<int> inorder(int root){
    if(root == -1) return list<int>(1,0);
    list<int> m = inorder(l[root]);
    list<int> n = inorder(r[root]);
    judge(m,n);
    m.push_back(root);
    m.insert(m.end(),n.begin(),n.end());
    return m;
}
int main(){
    cin >> n;
    for(int i=1;i<=n;i++)cin >> w[i];
    for(int i=1;i<=n;i++)cin >> l[i] >> r[i];
    w[0] = -1;
    inorder(1);
    cout << max_node;
    return 0; 
}
