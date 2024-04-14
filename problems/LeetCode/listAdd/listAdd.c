#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int val;
    struct ListNode *next;
} ListNode;

unsigned int bit_sum(int a, int b)
{
    int result = a ^ b;
    int carry = (a & b) << 1;
    if (carry == 0)
        return result;
    else
        return bit_sum(carry, result);
}

int bit_divide(int dividend, int divisor)
{
    // Handle special cases
    if (divisor == 0)
    {
        printf("Error: Division by zero\n");
        return 0;
    }

    if (dividend == 0)
    {
        return 0;
    }

    if (dividend == INT_MIN && divisor == -1)
    {
        printf("Error: Integer overflow\n");
        return INT_MAX;
    }

    // Determine the sign of the result
    int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;

    // Make both dividend and divisor positive
    unsigned int u_dividend = (dividend < 0) ? -dividend : dividend;
    unsigned int u_divisor = (divisor < 0) ? -divisor : divisor;

    // Initialize the quotient
    int quotient = 0;

    // Bitwise division
    while (u_dividend >= u_divisor)
    {
        int shift = 0;

        // Keep left-shifting the divisor until it's greater than the dividend
        while (u_dividend >= (u_divisor << shift))
        {
            shift++;
        }

        // Update the dividend and quotient
        u_dividend -= u_divisor << (shift - 1);
        quotient += 1 << (shift - 1);
    }

    return sign * quotient;
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
    short carry = 0;
    while (l1 != NULL || l2 != NULL)
    {
        short x = (l1 != NULL ? l1->val : 0);
        short y = (l2 != NULL ? l2->val : 0);
        short sum = bit_sum(bit_sum(x, y), carry);
        carry = bit_divide(sum, 10);

        struct ListNode *neW = (struct ListNode *) calloc(1, sizeof(struct ListNode));
        neW->val = sum % 10;
        neW->next = sumL;
        sumL = neW;
        if (l1 != NULL)
            l1 = l1->next;
        if (l2 != NULL)
            l2 = l2->next;
    }
    if (carry > 0)
    {
        struct ListNode *neW = (struct ListNode *) calloc(1, sizeof(struct ListNode));
        neW->val = carry;
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
    ListNode *f = (ListNode *) calloc(1, sizeof(ListNode));

    /*
        ListNode *g = (ListNode*)calloc(1, sizeof(ListNode));
        ListNode *h = (ListNode*)calloc(1, sizeof(ListNode));
        ListNode *i = (ListNode*)calloc(1, sizeof(ListNode));
        ListNode *j = (ListNode*)calloc(1, sizeof(ListNode));
        ListNode *k = (ListNode*)calloc(1, sizeof(ListNode));
        ListNode *l = (ListNode*)calloc(1, sizeof(ListNode));
        a->val = 0, a->next = NULL;
        b->val = 0, b->next = NULL;
    */
    a->val = 2;
    a->next = b;
    num1 = a;
    b->val = 4;
    b->next = c;
    c->val = 3;
    c->next = NULL;

    d->val = 5;
    d->next = e;
    num2 = d;
    e->val = 6;
    e->next = f;
    f->val = 4;
    f->next = NULL;

    /*
        g->val = 9; g->next = h;
        h->val = 9; h->next = i;
        i->val = 9; i->next = j;
        j->val = 9; j->next = l;
        l->val = 9; l->next = NULL;
    */

    traverse(addTwoNumbers(num1, num2));
}
