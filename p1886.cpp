#include<bits/stdc++.h>
using namespace std;
const int N = 1000005;
int a[N];
deque<int> q;
//输入一共有两行，第一行有两个正整数 n,k。 第二行 n 个整数，表示序列 a
//输出共两行，第一行为每次窗口滑动的最小值
//第二行为每次窗口滑动的最大值
int main(){
    int n,k; cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++){
        while(!q.empty() && a[i] < a[q.back()]) q.pop_back();
        q.push_back(i);
        if(i>=k){
            while(!q.empty() && q.front() <= i-k) q.pop_front();
            cout << a[q.front()] << " ";
        }
    }
    q.clear();
    cout << endl;
    for(int i=1;i<=n;i++){
        while(!q.empty() && a[i] > a[q.back()]) q.pop_back();
        q.push_back(i);
        if(i>=k){
        while(!q.empty() && q.front() <= i-k) q.pop_front();
        cout << a[q.front()] << " ";
        }
    }
    cout << endl;
    return 0; 
}