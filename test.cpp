#include<iostream>
#include<queue>
#include<string>
using namespace std;
struct node{
    int i;
    bool a[6][6];
};
node rev(node t,int x,int y){
    t.a[x][y] = t.a[x][y] ? 0:1;
    t.a[x+1][y] = t.a[x+1][y]  ? 0:1;
    t.a[x][y+1] = t.a[x][y+1] ? 0:1;
    t.a[x-1][y] = t.a[x-1][y] ? 0:1;
    t.a[x][y-1] = t.a[x][y-1] ? 0:1;
    t.i+=1;
    return t;
}
bool check(node t){
    bool is_0 = true,is_1 = true;
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++){
            if(t.a[i][j]==1){
                is_0 = false;
            }else{
                is_1 = false;
            }
            if(!is_1 && !is_0){
                return 0;
            }
        }
    return 1;
}
int main(){
    node t;
    for(int i=1;i<=4;i++){
        string s; cin >> s;
        for(int j=1;j<=4;j++){
            if(s[j-1]=='w') t.a[i][j]=1;
            else t.a[i][j]=0;
        }
    }
    queue<node> q; q.push(t);
    while(!q.empty()){
        node tmp = q.front(); q.pop();
        if(check(tmp)){
            cout << tmp.i;
            return 0;
        }
        for(int i=1;i<=4;i++)
            for(int j=1;j<=4;j++)
                    q.push(rev(tmp,i,j));
    }
    return 0; 
}