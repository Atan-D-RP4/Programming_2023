// Implements a Singly-Linked List
// Finished

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>


typedef struct node
{
    int data;
    struct node* link;
}node;

node* insert(node* start);
node* delete(node* start);
void search(node* start);
void traverse(node* start);
node* list_rev(node* start);
void delete_all(node* start);
void fun1(struct node* head);


int main(int argc, char* argv[])
{
    node* list = NULL;
    char choice;
    while(true)
    {
        printf("List Operations: \n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Traverse\n5. Reverse\n");
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
                fun1(list);
                break;
            case '5':
                list = list_rev(list);
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

node* insert(node* start)
{
    node* before = NULL; node* crsr = NULL;
    node* new = (node*)malloc(sizeof(node));
    if (new == NULL)
    {
        printf("List Overflow. Failed To Allocate Memory\n");
        delete_all(start);
    }

    printf("Element to Insert: ");
    int key; scanf("%d", &key);
    new->data = key;
    new->link = NULL;
    int index = 0;


    if (start == NULL)
    {
        new->link = start;
        start = new;
        printf("Successfully Inserted %d\n", key);
        return start;
    }

    printf("1. Insert At Beginning \n2. Insert After\n3. Insert Before\n4. Insert At End\n5. Insert At [Position]\n[1/2/3/4/5] ");
    scanf("%d", &key);
    switch(key)
    {
        case 1:
            label:
            new->link = start;
            start = new;
            break;
        case 2:
            printf("After: "); scanf("%d", &key);
            for (crsr = start; crsr != NULL; crsr = crsr->link)
            {
                if (crsr->data == key || crsr->link == NULL)
                {
                    new->link = crsr->link;
                    crsr->link = new;
                    break;
                }
            }
            if (crsr->link == NULL)
                printf("%d Not Found. Inserted At End\n", key);
            break;
        case 3:
            printf("Before: "); scanf("%d", &key);
            for (crsr = start; crsr != NULL; crsr = crsr->link)
            {
                if (crsr->data == key)
                {
                    if (crsr == start)
                        goto label;
                    new->link = before->link;
                    before->link = new;
                    break;
                }
                else if (crsr->link == NULL)
                {
                    printf("%d Not Found. Inserted At Beginning\n", key);
                    goto label;
                }
                before = crsr;
            }
            break;
        case 4:
            for (crsr = start; crsr->link != NULL; crsr = crsr->link);
            new->link = crsr->link;
            crsr->link = new;
            break;
        case 5:
            printf("Position: "); scanf("%d", &key);
            for (crsr = start; crsr != NULL; crsr = crsr->link)
            {
                index++;
                if (index == key)
                {
                    if (crsr == start)
                        goto label;
                    new->link = before->link;
                    before->link = new;
                    break;
                }
                else if (crsr->link == NULL)
                {
                    new->link = crsr->link;
                    crsr->link = new;
                    printf("Index Out of Bounds. Inserted At End\n");
                    break;
                }
                before = crsr;
            }
            break;
        default:
            printf("Enter Valid Choice!");
            break;
    }

    printf("Successfully Inserted %d\n", new->data);
    return start;
}

node* delete(node* start)
{
    printf("1. Delete At Beginning \n2. Delete Element\n3. Delete At End\n4. Delete At [Position]\n[1/2/3/4] ");
    int choice; scanf("%d", &choice);
    node* to_del = NULL; node* crsr = NULL;
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
            start = start->link;
            break;
        case 2:
            printf("Element: "); scanf("%d", &key);
            if (start->data == key)
            {
                start = start->link;
            }
            for (crsr = start; crsr != NULL; crsr = crsr->link)
            {
                if (crsr->link->data == key)
                {
                    to_del = crsr->link;
                    crsr->link = to_del->link;
                    break;
                }
            }
            break;
        case 3:
            for (crsr = start; crsr->link->link != NULL; crsr = crsr->link);
            to_del = crsr->link;
            crsr->link = NULL;
            break;
        case 4:
            printf("Position: "); scanf("%d", &key);
            if (key == 1)
            {
                start = start->link;
            }
            for (crsr = start; crsr != NULL; crsr = crsr->link)
            {
                index++;
                if ((index + 1) == key)
                {
                    to_del = crsr->link;
                    crsr->link = to_del->link;
                }
            }

    }

    free(to_del);
    return start;
}

void search(node* start)
{
    printf("Search For: ");
    int key; scanf("%d", &key);
    int count = 0;
    for (node* crsr = start; crsr != NULL; crsr = crsr->link)
    {
        count++;
        if (crsr->data == key)
        {
            printf("%d Found at %d\n", crsr->data, count);
            return;
        }
    }
    printf("%d Not Found in List\n", key);
}

void traverse(node* start)
{
    if (start == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    for (node* crsr = start; crsr != NULL; crsr = crsr->link)
        printf("%d ", crsr->data);
    printf("\n");
}

node* list_rev(node* start)
{
    if (start == NULL)
    {
        printf("List is Empty\n");
        return start;
    }

    node* prv = NULL;
    node* nxt = NULL;
    for (node* crsr = start; crsr != NULL;)
    {
        nxt = crsr->link;
        crsr->link = prv;
        prv = crsr;
        crsr = nxt;
    }
    start = prv;

    return start;
}

void delete_all(node* start)
{
    if (start == NULL)
		exit(0);
    for (node* crsr = start; crsr != NULL; )
    {
        node* to_del = crsr;
        crsr = crsr->link;
        free(to_del);
    }
    exit(0);
}

void fun1(struct node* head)

{

  if(head == NULL)

    return;

  fun1(head->link);

  printf("%d  ", head->data);

}
