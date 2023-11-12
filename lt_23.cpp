//leetcode 92 合并k个有序列表
#include<bits/stdc++.h>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
};

//通过:但是过于笨重
//本质上是遍历所有列表，每次找出一个最小值
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;
        bool done = false;
        while(done == false){
            done = true;
            int minVal = INT_MAX;
            queue<int> minIndex;
            queue<ListNode*> minNode;
            for(int i = 0; i < lists.size();i++){
                if (lists[i]!=NULL) done = false; else continue;
                if (lists[i]->val < minVal){
                    minVal = lists[i]->val;
                    while(!minNode.empty()) {minNode.pop(); minIndex.pop();}
                    minNode.push(lists[i]);
                    minIndex.push(i);
                }else if (lists[i]->val == minVal){
                    minNode.push(lists[i]);
                    minIndex.push(i);
                }
            }
            while(!minNode.empty()){
                cur->next = minNode.front();
                cur = cur->next;
                minNode.pop();
                int index = minIndex.front();
                minIndex.pop();
                lists[index] = lists[index]->next;
            }
        }
        return dummy->next;
    }
};

//A-利用优先队列
class Solution {
public:

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b){return a->val > b->val;};
        priority_queue<ListNode*,vector<ListNode*>,decltype(cmp)> pq(cmp);
        /**
         * 使用C++17推导指引
        lists.erase(remove_if(lists.begin(), lists.end(), [](auto p) { return !p; }), lists.end());
        priority_queue q{ [](auto& a, auto& b) { return a->val > b->val; }, lists };
        */
        for(auto node:lists) if (node!=NULL) pq.push(node);
        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;
        while(!pq.empty()){
            ListNode *node = pq.top();
            pq.pop();
            cur->next = node;
            cur = cur->next;
            if (node->next!=NULL) pq.push(node->next);
        }
        return dummy->next;
    }
};

//B-利用分治法
class Solution{
public:
    ListNode* mergeTwoList(ListNode* a,ListNode* b){
        if ( !a || !b) return a? a:b;
        ListNode dummy ,* cur = &dummy,* pta = a,* ptb = b;
        while(pta && ptb){
            if(pta->val < ptb->val){cur->next = pta;pta = pta->next;}
            else {cur->next = ptb; ptb = ptb->next;}
            cur = cur->next;
        }
        cur->next = pta ? pta:ptb;
        return dummy.next;
    }
    ListNode* mergeLRList(vector<ListNode*>& lists,int left,int right){
        if (left == right) return lists[left];
        if (left > right) return nullptr; 
        int mid = (left + right)>>1;
        return mergeTwoList(mergeLRList(lists,left,mid),mergeLRList(lists,mid+1,right));
    }
    ListNode* mergeKLists(vector<ListNode*>& lists){
        return mergeLRList(lists,0,lists.size()-1);
    }
};
