// Implements a Circular Doubly-Linked List
/* Unfinished -- Very Incorrect Insert
                 Incomplete Delete
                 Bugged Traversal/Search
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>


typedef struct node
{
    struct node* prev;
    int data;
    struct node* next;
}node;

node* insert(node* start);
node* delete(node* start);
void search(node* start);
void traverse(node* start);
void delete_all(node* start);

int main(int argc, char* argv[])
{
    printf("%lu", sizeof(node*));
    node* list = NULL;
    char choice;
    printf("List Operations: \n");
    printf("1. Insert\n2. Delete\n3. Search\n4. Traverse\n");
    while(true)
    {
        printf("Press 'X' to exit or\n");
        printf("Choose: [1/2/3/4] ");
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
                break;
            case ('X' | 'x'):
                delete_all(list);
                return 0;
            default:
                printf("Enter Valid Choice\n");
        }
    }
    return 0;
}

node* insert(node* start)
{
    node* new = (node*)calloc(1, sizeof(node));
    if (new == NULL)
    {
        printf("List Overflow. Failed To Allocate Memory\n");
        delete_all(start);
        exit(1);
    }

    printf("Element to Insert: ");
    int key; scanf("%d", &key);
    new->data = key;
    new->next = NULL;
    new->prev = NULL;
    int index = 0;
    node* cursor = start;

    if (start == NULL)
    {
        new->next = new;
        new->prev = new;
        start = new;
        printf("Successfully Inserted %d\n", key);
        return start;
    }

    printf("1. Insert At Beginning \n2. Insert After\n3. Insert Before\n4. Insert At End\n5. Insert At [Position]\n[1/2/3/4/5] ");
    scanf("%d", &key);

    switch(key)
    {
        case 1:
            new->prev = start->prev;
            new->next = start;
            start->prev->next = new;
            start->prev = new;
            start = new;
            break;
        case 2:
            printf("After: "); scanf("%d", &key);
            while (cursor->next != start && cursor->data != key)
                cursor = cursor->next;
            if (cursor->next == start && cursor->data != key)
                printf("%d Not Found. Inserted At End\n", key);
            new->prev = cursor;
            new->next = cursor->next;
            cursor->next->prev = new;
            cursor->next = new;
            break;
        case 3:
            printf("Before: "); scanf("%d", &key);
            while (cursor->data != key && cursor->next != start)
                cursor = cursor->next;
            new->prev = cursor->prev;
            new->next = cursor;
            cursor->prev->next = new;
            cursor->prev = new;
            if (cursor == start && cursor->data != start->data)
            {
                start = new;
                printf("%d Not Found. Inserted At Beginning\n", key);
            }
            break;
        case 4:
            new->prev = start->prev;
            new->next = start;
            start->prev->next = new;
            start->prev = new;
            break;
        case 5:
            printf("Position: "); scanf("%d", &key);
            if (key == 1)
            {
                new->prev = start->prev;
                new->next = start;
                start->prev->next = new;
                start->prev = new;
                start = new;
                break;
            }
            while (key - 1 > index && cursor != start)
            {
                index++;
                cursor = cursor->next;
            }
            if (cursor == start)
                printf("Index Out Of Bounds. Inserted At End\n");
            new->prev = cursor->prev;
            new->next = cursor;
            cursor->prev->next = new;
            cursor->prev = new;
            break;
    }

    key = new->data;
    printf("Successfully Inserted %d\n", key);
    return start;
}

node* delete(node* start)
{

    printf("1. Delete At Beginning \n2. Delete Element\n3. Delete At End\n4. Delete At [Position]\n[1/2/3/4] ");
    int choice; scanf("%d", &choice);
    node *to_del = NULL, *cursor = start;
    int key, index = 0;

    if (start == NULL)
    {
        printf("List Empty\n");
        return start;
    }
    else
        to_del = start;

   switch(choice)
    {
        case 1:
            start->prev->next = start->next;
            start->next->prev = start->prev;
            start = start->next;
            break;
        case 2:
            printf("Element: "); scanf("%d", &key);
            while (cursor->next != start && cursor->data != key)
                cursor = cursor->next;
            if (cursor->next == start && cursor->data != key)
                printf("%d Not Found\n", key);
            else
            {
                cursor = start->prev;
                cursor->prev->next = cursor->next;
                cursor->next->prev = cursor->prev;
            }
            to_del = cursor;
            cursor = cursor->next;
            break;
        case 3:
            cursor = start->prev;
            cursor->prev->next = cursor->next;
            cursor->next->prev = cursor->prev;
            to_del = cursor;
            cursor = cursor->next;
            break;
        case 4:
            printf("Position: "); scanf("%d", &key);
            if (key == 1)
            {
                start->prev->next = start->next;
                start->next->prev = start->prev;
                break;
            }
            while (key - 1 > index && cursor != start)
            {
                index++;
                cursor = cursor->next;
            }
            if (cursor == start)
                printf("Index Out Of Bounds. Inserted At End\n");
            cursor = start->prev;
            cursor->prev->next = cursor->next;
            cursor->next->prev = cursor->prev;
            to_del = cursor->next;
            break;
    }

    free(to_del); to_del = NULL;
    return start;
}


void search(node* start)
{
    printf("Search For: ");
    int key; scanf("%d", &key);
    int count = 0;
    node* cursor = start;
    do
    {
        count++;
        if (cursor->data == key)
        {
            printf("%d Found at %d\n", cursor->data, count);
            return;
        }
        cursor = cursor->next;
    }
    while (cursor->next != start);
    printf("%d Not Found in List\n", key);
}

void traverse(node* start)
{
    node* cursor = start;
    do
    {
        printf("%d ", cursor->data);
        cursor = cursor->next;
    }
    while (cursor != start);
    printf("\n");

    do
    {
        cursor = cursor->prev;
        printf("%d ", cursor->data);
    }
    while (cursor != start);
    printf("\n");
}

void delete_all(node* start)
{
    if (start == NULL)
		return;
    node* cursor = start;
    do
    {
        node* to_del = cursor;
        cursor = cursor->next;
        free(to_del);
    }
    while (cursor != start);
}
