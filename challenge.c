#include <stdio.h>
#include <stdlib.h>

/**
 * Basic structure for a singly linked list node.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * Merges two sorted linked lists into one sorted list.
 *
 * The idea is simple — go through both lists at the same time
 * and always pick the smaller value to attach next. I used a 
 * dummy head so I don’t have to deal with special cases for 
 * the first node. When one list runs out, I just attach the 
 * rest of the other list.
 *
 * @param list1 pointer to the first sorted list
 * @param list2 pointer to the second sorted list
 * @return pointer to the head of the merged sorted list
 */
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    // if one list is empty, return the other
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    // dummy node to make building the list easier
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    // compare nodes and link the smaller one first
    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    // attach whatever is left over
    tail->next = (list1 != NULL) ? list1 : list2;

    // return merged list (skip dummy)
    return dummy.next;
}

/**
 * Creates a new list node with a given value.
 */
struct ListNode* createNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;



/**
 * Reflection:
 *
 * I learned how merging linked lists actually works by controlling
 * the node pointers directly instead of copying values. I used a 
 * dummy head to keep the code clean and avoid messy conditions for
 * the first node. I also learned why the iterative version is faster
 * and safer than recursion, especially with long lists. It’s all about
 * pointer control and thinking step-by-step through the list.
 */
