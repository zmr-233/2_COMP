//中缀转后缀表达式
//C++实现
#include<bits/stdc++.h>
#define USE_STRING
using namespace std;
typedef long long ll;
const ll INF = 2147483647;
struct node{
    bool t = 0;
    ll d = 0;
    node(bool t_,ll d_):t(t_),d(d_){}
};
int getCH(char ch){ //获得符号ch的优先级
    if(ch == '+' || ch == '-' ) return 1;  
    else if(ch == '*' || ch == '/' ) return 2;
    else if(ch == '^' ) return 3;
    //cout << "#" << ch << "#" << endl; exit(-3);
}
int checkCH(char ch1,char ch2){ //根据ch1和ch2的优先级返回不同的代码
    int p1 = getCH(ch1), p2 = getCH(ch2);
    if(p1 > p2 || p1==3 && p2==3) return 1;
    else if(p1 < p2 || p1 == p2) return 2;
}
void show(deque<node>& output,deque<node>& tmp){ //打印输出队列
    for(auto i : output)
        if(i.t == 0) cout << i.d << " ";
        else cout << (char) i.d << " ";
    for(auto i : tmp)
        if(i.t == 0) cout << i.d << " ";
        else cout << (char) i.d << " ";
    cout << endl;
}
node cal(node& n1,node& n2,node& op){
    switch((char)op.d){
    case '+': return node(0,n1.d + n2.d);
    case '-': return node(0,n1.d - n2.d);
    case '*': return node(0,n1.d * n2.d);
    case '/': return node(0,n1.d / n2.d);
    case '^': return node(0,pow(n1.d,n2.d));
    }
}
int main(){
    stack<node> input;
    deque<node> tmp;
    char ch;
    #ifdef USE_GETCHAR
    while( (ch = getchar())!='\n'){
        if (ch == ' ') continue;
        else if(ch == '(') input.push(node(1,(ll)'('));
        else if(ch == ')'){
            while(!input.empty() && input.top().d != (ll)'(') 
                {tmp.push_back(input.top()); input.pop();}
            input.pop();
        }
        else if (isdigit(ch)) tmp.push_back(node(0,(ll)ch-'0'));
        else{
            int k;
            while(!input.empty() && input.top().d != (ll)'(' && (k = checkCH(ch,(char)input.top().d)) == 2 ){
                tmp.push_back(input.top()); input.pop();
            }
            input.push(node(1,(ll)ch));
        }
    }
    while(!input.empty()) {tmp.push_back(input.top()); input.pop();}
    #endif
    #ifdef USE_STRING
    string s;
    cin >> s; // 读取整个字符串

    for (char ch : s) { // 遍历字符串中的每个字符
        if (ch == ' ') continue;
        else if(ch == '(') input.push(node(1,(ll)'('));
        else if(ch == ')'){
            while(!input.empty() && input.top().d != (ll)'(') 
                {tmp.push_back(input.top()); input.pop();}
            input.pop();
        }
        else if (isdigit(ch)) tmp.push_back(node(0,(ll)ch-'0'));
        else{
            int k;
            while(!input.empty() && input.top().d != (ll)'(' && (k = checkCH(ch,(char)input.top().d)) == 2 ){
                tmp.push_back(input.top()); input.pop();
            }
            input.push(node(1,(ll)ch));
        }
    }
    while(!input.empty()) {tmp.push_back(input.top()); input.pop();}
    #endif

    deque<node> output;
    show(output,tmp);
    while(!tmp.empty()){
        while(!tmp.empty() && tmp.front().t != 1) {output.push_back(tmp.front());tmp.pop_front();}
        node op = tmp.front(); tmp.pop_front();
        node n2 = output.back(); output.pop_back(); node n1 = output.back(); output.pop_back();
        output.push_back(cal(n1,n2,op));
        show(output,tmp);
    }

    return 0;
}