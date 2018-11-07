/**
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(0);
        ListNode* cur = head;
        int carry = 0;
        while(l1 || l2) {
            // cal sum
            auto sum = carry;

            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;
            sum = sum % 10;

            // add node
            cur->next = new ListNode(sum);
            cur = cur->next;
        };

        if (carry) cur->next = new ListNode(carry);

        if (head->next) {
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }
        return head;
    }
};

/**

// test
#include <iostream>

ListNode* getList(long num) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    do {
        ListNode* node = new ListNode(num % 10);
        if (head == nullptr) {
            tail = head = node;
        } else {
            tail->next = node;
            tail = node;
        }
        num /= 10;
    } while(num);
    return head;
}

void freeList(ListNode* p) {
    while (p) {
        ListNode* tmp = p;
        p = p->next;
        delete tmp;
    }
}

void printList(ListNode* p) {
    while(p) {
        std::cout << p->val << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    ListNode* l1 = getList(9);
    ListNode* l2 = getList(9999999991);

    Solution solution;
    ListNode* ret = solution.addTwoNumbers(l1, l2);

    printList(l1);
    printList(l2);
    printList(ret);

    freeList(l1);
    freeList(l2);
    freeList(ret);

    return 0;
}
*/