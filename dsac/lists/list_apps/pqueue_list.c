// Implements a Priority Queue Using Linked Lists


#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>


typedef struct node
{
    short pr;
    int data;
    struct node* link;
}node;

node *front = NULL, *rear = NULL;


bool isEmpty();
void insert();
void delete ();
void peek();
void display();
void delete_all();

int main()
{
    printf("Queue Operations:\n");
    printf("1. Insert\n2. Delete\n3. Peek\n4. Display\n5. Exit\n");
    int choice = 0;
    while (true)
    {
        printf("Operation [1/2/3/4/5]: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                insert();
                break;
            case 2:
                delete ();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                printf("Enter Valid Choice:\n");
        }
    }
}

bool isEmpty()
{
    return (front == NULL);
}

void insert()
{
    if (isEmpty())
    {
        printf("Queue Underflow\n");
        return front;
    }

    node* new = (node*)malloc(sizeof(node));
    if (new == NULL)
    {
        printf("Memory Overflow\n");
        exit(1);
    }
    printf("Insert: ");
    scanf("%d", &new->data);
    printf("Priority: ");
    scanf("%d", &new->pr);
    new->link = NULL;

    // If the queue is empty or new node has higher priority than the front node
    if (front == NULL || new_node->priority > front->priority) {
        new_node->link = front;
        front = new_node;
    }
    else
    {
        // Traverse the list to find the correct position
        node* crsr = front;
        while (crsr->link != NULL && crsr->link->priority >= new_node->priority)
            crsr = crsr->link;
        new_node->link = crsr->link;
        crsr->link = new_node;
    }

    return
}

void delete ()
{
    if (front == NULL)
	{
		printf("Queue Underflow\n");
		return;
	}

	node* tmp = front;
	printf("Deleted %d Successfully\n", tmp->data);
	if (front == rear)
	{
		front = NULL;
		rear = NULL;
	}
	else
		front = front->link;

	free(tmp);
	tmp = NULL;
	return;
}

void peek()
{

}

void display()
{
    for (node* cursor = start; cursor != NULL; cursor = cursor->link)
    {
        printf("%d ", cursor->data);
    }
    printf("\n");
	return;
}

void delete_all()
{
    if (front == NULL)
		return;
    for (node* cursor = front; cursor != NULL; )
    {
        node* to_del = cursor;
        cursor = cursor->link;
        free(to_del);
    }
}

