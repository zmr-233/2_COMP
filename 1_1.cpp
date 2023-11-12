//1.1单向链表
#include<bits/stdc++.h>
using namespace std;

//A-数组实现
const int N = 105;
struct node{
    int id;
    int next_id;
    int data; 
}nodes[N];
int main_1(){
    int m,n;
    cin >> m >> n;
    nodes[0].next_id = 1;
    for(int i=1;i <=n; i++){nodes[i].id = 1;nodes[i].next_id = i+1;}
    nodes[n].next_id = 1;//处理循环链表
    int prev = 1, now = 1;
    while((n--)>1){
        for(int i=1; i < m; i++){prev = now;now = nodes[now].next_id;}  
        cout << nodes[now].id << " ";
        nodes[prev].next_id = nodes[now].next_id;
        now = nodes[now].next_id; 
    }
    cout << nodes[now].next_id << endl;
    return 0;
}

//B-STL实现
int main_2(){
    int m,n;
    cin >> m >> n;
    list<int> l;
    for(int i=1;i<=n;i++) l.push_back(i);
    auto it = l.begin();
    while(l.size() > 1){
        for(int i=1;i<m;i++){
            it++;
            if(it == l.end()) it = l.begin();//STL的循环依赖于if实现
        }
        cout << *it << " ";
        /*STL链表单独处理循环的部分*/
        auto next = ++it;
        l.erase(--it);
        if(next == l.end()) next = l.begin();//注意end()实际上是下一个元素
        it = next;

    }
    cout << *it << endl;
    return 0;
}


