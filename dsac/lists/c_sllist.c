// Implements a Circular Singly-Linked List
// Unfinished
// Pending Test for :
// Delete Operations
// List Reversal

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct node
{
    int data;
    struct node *link;
} node;

node *insert(node *last);
node *delete (node *last);
void search(node *last);
void traverse(node *last);
node *list_rev(node *last);
void delete_all(node *last);
bool c_checkLoop(node *start);

int main(int argc, char *argv[])
{
    node *list = NULL;
    char choice;
    while (true)
    {
        printf("List Operations: \n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Traverse\n5. Reverse List\n");
        printf("Choose: [1/2/3/4/5] ");
        scanf(" %c", &choice);
        switch (choice)
        {
            case '1':
                list = insert(list);
                break;
            case '2':
                list = delete(list);
                break;
            case '3':
                search(list);
                break;
            case '4':
                traverse(list);
                c_checkLoop(list);
                break;
            case '5':
                list = list_rev(list);
            case ('X' | 'x'):
                delete_all(list);
                return 0;
            default:
                printf("Enter Valid Choice\n");
        }
        printf("Press 'X' to exit\n");
    }
    return 0;
}

node *insert(node *last) // Fully Completed and Tested
{
    node *new = (node *) malloc(sizeof(node));
    if (new == NULL)
    {
        printf("List Overflow. Failed To Allocate Memory\n");
        delete_all(last);
    }

    printf("Element to Insert: ");
    int key;
    scanf("%d", &key);
    new->data = key;
    new->link = NULL;
    int index = 0;

    if (last == NULL)
    {
        new->link = new;
        last = new;
        printf("Successfully Inserted %d\n", key);
        return last;
    }

    node *start = last->link;
    node *cursor = start;
    node *before = last;

    printf("1. Insert At Beginning \n2. Insert After\n3. Insert Before\n4. Insert At End\n5. Insert At [Position]\n[1/2/3/4/5] ");
    scanf("%d", &key);
    switch (key)
    {
        case 1:
            new->link = start;
            start = new;
            last->link = start;
            break;
        case 2:
            printf("After: ");
            scanf("%d", &key);
            do
            {
                if (cursor->data == key || cursor == last)
                {
                    new->link = cursor->link;
                    cursor->link = new;
                    if (cursor == last)
                        last = new;
                    break;
                }
                cursor = cursor->link;
            }
            while (cursor != start);

            if (cursor == last)
                printf("%d Not Found. Inserted At End\n", key);

            break;
        case 3:
            printf("Before: ");
            scanf("%d", &key);
            do
            {
                if (key == cursor->data)
                {
                    new->link = before->link;
                    before->link = new;
                    if (cursor == start)
                        start = new;
                    break;
                }
                before = cursor;
                cursor = cursor->link;
            }
            while (cursor != start);

            if (cursor == start)
                printf("%d Not Found. Inserted At End\n", key);
        case 4:
            new->link = last->link;
            last->link = new;
            last = new;
            break;
        case 5:
            printf("Position: ");
            scanf("%d", &key);
            do
            {
                index++;
                if (index == key || cursor == last)
                {
                    new->link = before->link;
                    before->link = new;
                    if (cursor == start)
                        start = new;
                    break;
                }
                before = cursor;
                cursor = cursor->link;
            }
            while (cursor != start);

            if (index < key)
                printf("%d Index Out Of Bounds. Inserted At begin\n", key);

            break;
        default:
            printf("Enter Valid Choice!");
            break;
    }

    printf("Successfully Inserted %d\n", new->data);
    return last;
}

node *delete (node *last) // Logic Finished. Pending: Debugging
{
    printf("1. Delete At Beginning \n2. Delete Element\n3. Delete At End\n4. Delete At [Position]\n[1/2/3/4] ");
    int choice;
    scanf("%d", &choice);
    int key, index = 0;

    node *to_del = NULL;
    node *cursor = NULL;
    if (last->link == NULL)
    {
        printf("List Empty\n");
        return last;
    }
    else
        to_del = last->link;
    node *start = last->link;

    switch (choice)
    {
        case 1:
            start = start->link;
            last = start;
            break;
        case 2:
            printf("Element: ");
            scanf("%d", &key);

            if (start->data == key)
            {
                start = start->link;
                last = start;
            }

            do
            {
                if (key == cursor->data)
                    to_del = cursor;
                cursor = cursor->link;
            }
            while (cursor != start);

            break;
        case 3:
            for (cursor = start; cursor->link->link != start; cursor = cursor->link)
                ;
            to_del = cursor->link;
            cursor->link = start;
            last = cursor;
            break;
        case 4:
            printf("Position: ");
            scanf("%d", &key);
            if (key == 1)
            {
                start = start->link;
                last = start;
            }
            for (cursor = start; cursor != NULL; cursor = cursor->link)
            {
                index++;
                if ((index + 1) == key)
                {
                    to_del = cursor->link;
                    cursor->link = to_del->link;
                }
            }
    }

    free(to_del);
    return start;
}

void search(node *last)
{
    printf("Search For: ");
    int key;
    scanf("%d", &key);
    int count = 0;

    node *start = last->link;
    node *cursor = start;
    do
    {
        count++;
        if (cursor->data == key)
        {
            printf("%d Found at %d\n", cursor->data, count);
            return;
        }
        else
            cursor = cursor->link;
    }
    while (cursor->link != start);
    printf("%d Not Found in List\n", key);
}

void traverse(node *last)
{
    node *start = last->link;
    if (start == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    node *cursor = start;
    do
    {
        printf("%d ", cursor->data);
        cursor = cursor->link;
    }
    while (cursor != start);
    printf("\n");
}

node *list_rev(node *last)
{
    if (last == NULL)
    {
        printf("List is Empty\n");
        return last;
    }
    else if (last->link == last)
        return last;

    node *start = last->link;
    node *prv = NULL;
    node *nxt = NULL;
    for (node *crsr = start; crsr != NULL;)
    {
        nxt = crsr->link;
        crsr->link = prv;
        prv = crsr;
        crsr = nxt;
    }
    start = prv;

    return start;
}

void delete_all(node *last)
{
    if (last == NULL)
        return;
    node *start = last->link;

    node *cursor = start;
    do
    {
        node *to_del = cursor;
        cursor = cursor->link;
        free(to_del);
    }
    while (cursor != start);
    exit(0);
}

bool c_checkLoop(node *last)
{
    // Awesome debug function for Circular Linked Lists
    node *slow, *fast;
    node* start = last->link;
    slow = fast = start;
    do
    {
        slow = slow->link;
        fast = fast->link->link;
        if (fast == slow)
        {
            slow = start;
            int index = 0;
            while (slow != fast)
            {
                index++;
                slow = slow->link;
                fast = fast->link;
            }
            printf("List has Looped at node with data %d at position %d\n", slow->data, index);
            return true;
        }
    }
    while (fast != last && fast->link != last);

    return false;
}
