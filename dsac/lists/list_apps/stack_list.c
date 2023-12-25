// Implements a Stack Using a Singly-Linked List
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

node* stk_top = NULL;

bool isEmpty();
void push();
void pop();
void peek();
void display();
void delete_all(node* start);

int main(void)
{
	printf("Stack Operations:\n");
	printf("1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit\n");

	int choice = 0;
	while(true)
	{
		printf("Operation[1/2/3/4/5]: ");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
				push();
				break;
			case 2:
				pop();

				break;
			case 3:
				peek();
				break;
			case 4:
				display();
				break;
			case 5:
                delete_all(stk_top);
				exit(0);
			default:
				printf("Enter Valid Choice:\n");
		}
	}
}



bool isEmpty()
{
    return (stk_top == NULL);
}
void push()
{
    node* start = stk_top;
    printf("Enter Integer Element: ");
    int elmnt; scanf("%d", &elmnt);
    node* new = (node*)malloc(sizeof(node));
    if (new == NULL)
    {
        printf("Stack Overflow. Failed To Allocate Memory\n");
        delete_all(stk_top);
        exit(-1);
    }
    new->data = elmnt;
    new->link = start;
    start = new;
    stk_top = start;
    return;
}

void pop()
{
    if (isEmpty())
    {
        printf("Stack Underflow\n");
        return;
    }
    node* tmp = stk_top;
    int popped = stk_top->data;
    stk_top = stk_top->link;
    free(tmp); tmp = NULL;
    printf("Successfully Deleted %d\n", popped);
    return;
}

void peek()
{
    printf("Top: %d\n", stk_top->data);
}

void display()
{
    if (isEmpty())
    {
        printf("Stack Underflow\n");
        return;
    }
    printf("Stack:\n");
    for (node* cursor = stk_top; cursor != NULL; cursor = cursor->link)
    {
        printf("%d ", cursor->data);
    }
    printf("\n");
}

void delete_all(node* start)
{
    for (node* cursor = start; cursor != NULL; )
    {
        node* to_del = cursor;
        cursor = cursor->link;
        free(to_del);
    }
}
