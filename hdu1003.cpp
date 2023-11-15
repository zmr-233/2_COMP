#include<bits/stdc++.h>
using namespace std;
//输入：T次数 -> N个数
//输出两行:Case #: max_sum start end
const int INF = 0x7fffffff;
int main(){
    int T; cin >> T;
    for(int ii = 1;ii<=T;ii++){
       int N; cin >> N;
       int sum = 0;
       int max_sum = -INF;
       int start = 1,end = 1,p = 1;
       for(int i=1;i<=N;i++){
            int num; cin >> num;
            sum += num;
            if(sum>max_sum){
                max_sum = sum;start = p; end = i;
            }
            if(sum < 0){sum=0;p = i+1;}
       } 
       
    }
}