// Implements a Double-Linked List
// Finished

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} node;

node *insert(node *start);
node *delete (node *start);
void search(node *start);
void traverse(node *start);
void delete_all(node *start);

int main(int argc, char *argv[])
{
    node *list = NULL;
    char choice;
    while (true)
    {
        printf("List Operations: \n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Traverse\n");
        printf("Choose: [1/2/3/4] ");
        scanf(" %c", &choice);
        switch (choice)
        {
            case '1':
                list = insert(list);
                break;
            case '2':
                list = delete (list);
                break;
            case '3':
                search(list);
                break;
            case '4':
                traverse(list);
                break;
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

node *insert(node *start)
{
    node *new = (node *) malloc(sizeof(node));
    if (new == NULL)
    {
        printf("List Overflow. Failed To Allocate Memory\n");
        delete_all(start);
        exit(1);
    }

    printf("Element to Insert: ");
    int key;
    scanf("%d", &key);
    new->data = key;
    new->next = NULL;
    new->prev = NULL;
    int index = 0;
    node *cursor = NULL;

    if (start == NULL)
    {
        start = new;
        printf("Successfully Inserted %d\n", key);
        return start;
    }

    printf("1. Insert At Beginning \n2. Insert After\n3. Insert Before\n4. Insert At End\n5. Insert At [Position]\n[1/2/3/4/5] ");
    scanf("%d", &key);

    switch (key)
    {
        case 1:
        label:
            new->next = start;
            start->prev = new;
            start = new;
            break;
        case 2:
            printf("After: ");
            scanf("%d", &key);
            for (cursor = start; cursor != NULL; cursor = cursor->next)
            {
                if (cursor->data == key || cursor->next == NULL)
                {
                    new->prev = cursor;
                    new->next = cursor->next;
                    if (cursor->next != NULL)
                        cursor->next->prev = new;
                    cursor->next = new;
                    break;
                }
            }
            if (cursor == NULL)
                printf("%d Not Found. Inserted At End\n", key);
            break;
        case 3:
            printf("Before: ");
            scanf("%d", &key);
            for (cursor = start; cursor != NULL; cursor = cursor->next)
            {
                if (cursor->data == key)
                {
                    if (cursor == start)
                        goto label; // Insert at Beginning
                    new->prev = cursor->prev;
                    new->next = cursor;
                    cursor->prev->next = new;
                    cursor->prev = new;
                    break;
                }
            }
            break;
        case 4:
            for (cursor = start; cursor->next != NULL; cursor = cursor->next)
                ;
            new->prev = cursor;
            cursor->next = new;
            break;
        case 5:
            printf("Position: ");
            scanf("%d", &key);
            for (cursor = start; cursor != NULL; cursor = cursor->next)
            {
                index++;
                if (index == key)
                {
                    if (cursor == start)
                        goto label;
                    new->prev = cursor->prev;
                    new->next = cursor;
                    cursor->prev->next = new;
                    cursor->prev = new;
                    break;
                }
                if (key > index && cursor->next == NULL)
                {
                    new->prev = cursor;
                    cursor->next = new;
                    printf("Index Out of Bounds. Inserted At End\n");
                    break;
                }
            }
            break;
    }

    key = new->data;
    printf("Successfully Inserted %d\n", key);
    return start;
}

node *delete (node *start)
{
    printf("1. Delete At Beginning \n2. Delete Element\n3. Delete At End\n4. Delete At [Position]\n[1/2/3/4] ");
    int choice;
    scanf("%d", &choice);
    node *to_del = NULL;
    node *cursor = NULL;
    int key, index = 0;

    if (start == NULL)
    {
        printf("List Empty\n");
        return start;
    }
    else
        to_del = start;

    switch (choice)
    {
        case 1:
        label:
            start = start->next;
            if (start != NULL)
                start->prev = NULL;
            break;
        case 2:
            printf("Element: ");
            scanf("%d", &key);
            if (start->data == key)
                goto label;
            for (cursor = start; cursor != NULL; cursor = cursor->next)
            {
                if (cursor->data == key)
                {
                    to_del = cursor;
                    cursor->prev->next = cursor->next;
                    cursor->next->prev = cursor->prev;
                    break;
                }
            }
            break;
        case 3:
            for (cursor = start; cursor->next != NULL; cursor = cursor->next)
                ;
            to_del = cursor;
            cursor->prev->next = NULL;
            break;
        case 4:
            printf("Position: ");
            scanf("%d", &key);
            if (key == 1)
                goto label;
            for (cursor = start; cursor != NULL; cursor = cursor->next)
            {
                index++;
                if ((index + 1) == key)
                {
                    to_del = cursor->next;
                    cursor->next = to_del->next;
                }
            }
    }

    free(to_del);
    return start;
}

void search(node *start)
{
    printf("Search For: ");
    int key;
    scanf("%d", &key);
    int count = 0;
    for (node *cursor = start; cursor != NULL; cursor = cursor->next)
    {
        count++;
        if (cursor->data == key)
        {
            printf("%d Found at %d\n", cursor->data, count);
            return;
        }
    }
    printf("%d Not Found in List\n", key);
}

void traverse(node *start)
{
    if (start == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    node *cursor = start;
    node *end;
    for (; cursor != NULL; cursor = cursor->next)
    {
        printf("%d ", cursor->data);
        if (cursor->next == NULL)
            end = cursor;
    }
    printf("\n");

    for (cursor = end; cursor != NULL; cursor = cursor->prev)
        printf("%d ", cursor->data);
    printf("\n");
}

void delete_all(node *start)
{
    if (start == NULL)
        return;
    for (node *cursor = start; cursor != NULL;)
    {
        node *to_del = cursor;
        cursor = cursor->next;
        free(to_del);
    }
}
