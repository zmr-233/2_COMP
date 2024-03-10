#include<bits/stdc++.h>
using namespace std;

#define MAXN 100005
int LPS[MAXN];
char s[MAXN];
int main(){
    string s; cin >> s;
    int len=0,i=1;
    while(i<s.size()){
        if(s[len]==s[i]){
            len++;
            LPS[i]=len;
            i++;
        }else{
            if(len!=0){
                len = LPS[len-1];
            }else{
                LPS[i]=0;
                i++;
            }
        }
    }
    for(int i=0;i<s.size();i++){
        cout << LPS[i]<<" ";
    }
    return 0;

}