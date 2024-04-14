#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int val;
    struct ListNode *next;
} ListNode;

uint64_t atoi64(char *numStr)
{
    uint64_t num = 0;
    int c = *numStr++;

    if (isdigit(c))
        num = c - 48;

    while ((c = *numStr++))
    {
        if (isdigit(c))
            num = (10 * num) + (c - 48);
    }

    return num;
}

struct ListNode *reverseList(struct ListNode *head)
{
    struct ListNode *prev = NULL;
    struct ListNode *current = head;
    struct ListNode *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    // After the loop, 'prev' will be the new head of the reversed list
    return prev;
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode *sumL = NULL, *crsr = NULL;
    struct ListNode *p = reverseList(l1), *q = reverseList(l2);

    char num1[100] = {0}, num2[100] = {0};
    int i = 0;

    for (i = 0; p != NULL; p = p->next)
        num1[i++] = p->val + '0';
    num1[i] = '\0';

    for (i = 0; q != NULL; q = q->next)
        num2[i++] = q->val + '0';
    num2[i] = '\0';

    uint64_t sumN = atoi64(num1) + atoi64(num2);

    if (sumN == 0)
    {
        struct ListNode *neW = (struct ListNode *) calloc(1, sizeof(struct ListNode));
        neW->val = 0;
        neW->next = sumL;
        sumL = neW;
        return sumL;
    }

    for (; sumN != 0; sumN /= 10)
    {
        struct ListNode *neW = (struct ListNode *) calloc(1, sizeof(struct ListNode));
        neW->val = sumN % 10;
        neW->next = sumL;
        sumL = neW;
    }

    return reverseList(sumL);
}

void traverse(ListNode *start)
{
    if (start == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    for (ListNode *crsr = start; crsr != NULL; crsr = crsr->next)
        printf("%d ", crsr->val);
    printf("\n");
}

int main(void)
{
    ListNode *num1 = NULL, *num2 = NULL;
    ListNode *a = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *b = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *c = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *d = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *e = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *g = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *f = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *h = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *i = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *j = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *k = (ListNode *) calloc(1, sizeof(ListNode));
    ListNode *l = (ListNode *) calloc(1, sizeof(ListNode));
    /*
        a->val = 0, a->next = NULL;
        b->val = 0, b->next = NULL;
    */
    a->val = 9;
    a->next = NULL;
    num1 = a;
    b->val = 1;
    b->next = c;
    num2 = b;
    c->val = 9;
    c->next = d;
    d->val = 9;
    d->next = e;
    e->val = 9;
    e->next = f;
    f->val = 9;
    f->next = g;
    g->val = 9;
    g->next = h;
    h->val = 9;
    h->next = i;
    i->val = 9;
    i->next = j;
    j->val = 9;
    j->next = l;
    l->val = 9;
    l->next = NULL;

    traverse(addTwoNumbers(num1, num2));
}
