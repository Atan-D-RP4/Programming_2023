// To merge K sorted Linked Lists
// From LeetCode (Hard)

#include <stdio.h>
#include <stdlib.h>

//Definition for singly-linked list.
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

ListNode* mergeList(ListNode *l1, ListNode *l2)
{
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    ListNode *merged = NULL;

    if (l1->val < l2->val) {
        merged = l1;
        merged->next = mergeList(l1->next, l2);
    } else {
        merged = l2;
        merged->next = mergeList(l1, l2->next);
    }

    return merged;
}

ListNode* mergeKLists(ListNode** lists, int listsSize)
{
    if (listsSize == 0)
        return NULL;

    int interval = 1;

    while (interval < listsSize) {
        for (int i = 0; i + interval < listsSize; i += interval * 2)
            lists[i] = mergeList(lists[i], lists[i + interval]);
        interval *= 2;
    }
    return lists[0];
}

int main() {
    // Define some sample linked lists for testing
    ListNode *list1 = (ListNode*)malloc(sizeof(ListNode));
    list1->val = 1;
    list1->next = (ListNode*)malloc(sizeof(ListNode));
    list1->next->val = 4;
    list1->next->next = (ListNode*)malloc(sizeof(ListNode));
    list1->next->next->val = 5;
    list1->next->next->next = NULL;

    ListNode *list2 = (ListNode*)malloc(sizeof(ListNode));
    list2->val = 1;
    list2->next = (ListNode*)malloc(sizeof(ListNode));
    list2->next->val = 3;
    list2->next->next = (ListNode*)malloc(sizeof(ListNode));
    list2->next->next->val = 4;
    list2->next->next->next = NULL;

    ListNode *list3 = (ListNode*)malloc(sizeof(ListNode));
    list3->val = 2;
    list3->next = (ListNode*)malloc(sizeof(ListNode));
    list3->next->val = 6;
    list3->next->next = NULL;

    // Array of pointers to linked lists
    ListNode *lists[] = {list1, list2, list3};
    int listsSize = 3;

    // Merge the linked lists
    ListNode* mergedList = mergeKLists(lists, listsSize);

    // Print the merged list
    printf("Merged List: ");
    ListNode* current = mergedList;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");

    // Free dynamically allocated memory
    current = mergedList;
    while (current != NULL) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }

    // Free memory of sample linked lists
    free(list1);
    free(list2);
    free(list3);

    return 0;
}
