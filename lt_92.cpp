/**反转链表2
 * 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。
 * 请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
 * 
 * 输入：head = [1,2,3,4,5], left = 2, right = 4。
 * 输出：[1,4,3,2,5]
 * 
*/

#include<bits/stdc++.h>
using namespace std;
 struct ListNode
 {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

// 1 <= n <= 500
// -500 <= Node.val <= 500
// 1 <= left <= right <= n
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummy = new ListNode(-1,head); //注意：这里添加了额外的头结点
        int cnt = 1; ListNode* pre = dummy;
        while(cnt < left){pre = pre->next; cnt++;}
        ListNode * cur = pre->next,*next = cur->next,*prevLeft = pre;
        while(cnt < right){
            cur->next = pre;
            pre = cur;
            cur = next;
            next = next->next;
            cnt++;
        }
        cur->next = pre;
        prevLeft->next->next = next;
        prevLeft->next = cur;
        return dummy->next;
    }
};

/**
 * 题解:使用额外头结点
*/

//注意：如果是单纯的反转整个链表，一共有两种方式实现:
//A.迭代法:
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while(cur != nullptr){
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};

//B.递归法
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next)
            return head;
        ListNode* newhead = reverseList(head->next); //newhead是最后一个结点
        head->next->next = head;
        head->next = nullptr;
        return newhead; //这里如果返回了head就是毫无意义的
    }
};