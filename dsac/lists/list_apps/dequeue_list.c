// Implements a Double_Ended(DE) Queue Using a Singly-Linked List
// Finished

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node
{
    int data;
    struct node* link;
}node;

void insertFront();
void insertRear();
void deleteRear();
void deleteFront();
void peekFront();
void peekRear();
void display();
void delete_all(node* start);

node* front = NULL;
node* rear = NULL;
int key;

int main(void)
{
	printf("Queue Operations:\n");
	printf("1. Insert at Front\n2. Delete at Rear\n");
	printf("3. Insert at Rear\n4. Delete at Front\n");
	printf("5. Peek First\n6. Peek Last\n");
	printf("7. Display\n8. Exit\n");
	char choice = 0;
	while(true)
	{
		printf("Operation: [1/2/3/4/5/6/7]\t\t\t\t Press X to Exit\n");
		scanf(" %c", &choice);
		switch (choice)
		{
			case '1':
				insertFront();
				break;
			case '2':
				deleteRear();
				break;
            case '3':
                insertRear();
                break;
			case '4':
                deleteFront();
                break;
            case '5':
				peekFront();
				break;
            case '6':
                peekRear();
                break;
			case '7':
				display();
				break;
			case ('X' | 'x'):
				delete_all(front);
				exit(0);
			default:
				printf("Enter Valid Choice:\n");
		}
	}
}


void insertFront()
{
	node* new = (node*)malloc(sizeof(node));
	if (new == NULL)
	{
		printf("List Overflow. Failed To Allocate Memory\n");
		delete_all(front);
		exit(1);
	}
	new->link = NULL;

	printf("Element to Insert:"); scanf("%d", &key);
	new->data = key;

	if (front != NULL)
	{
		new->link = front;
	}
		front = new;
	return;
}

void insertRear() // Base Insert
{
	node* new = (node*)malloc(sizeof(node));
	if (new == NULL)
	{
		printf("List Overflow. Failed To Allocate Memory\n");
		delete_all(front);
		exit(1);
	}
	new->link = NULL;

	printf("Element to Insert:"); scanf("%d", &key);
	new->data = key;

	if (front == NULL)
	{
		front = new;
	}
	else
	{
		rear->link = new;
	}
	rear = new;
	return;
}

void deleteRear()
{
	node* cursor;
	node* tmp = rear;
	for (cursor = front; cursor->link != rear; cursor = cursor->link);
	cursor->link = rear->link;
	rear = cursor;
	printf("Deleted %d Successfully\n", tmp->data);
	free(tmp);
	tmp = NULL;
	return;
}

void deleteFront() // Base Delete
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

void peekFront()
{
	printf("Last In Queue: %d", front->data);
	return;
}

void peekRear()
{
	printf("First In Queue: %d", rear->data);
	return;
}

void display()
{
	if (front == NULL)
	{
		printf("Queue Underflow\n");
		return;
	}
	
	for (node* cursor = front; cursor != NULL; cursor = cursor->link)
    {
        printf("%d ", cursor->data);
    }
    printf("\n");
	return;
}

void delete_all(node* start)
{
	if (front == NULL)
		return;
    for (node* cursor = start; cursor != NULL; )
    {
        node* to_del = cursor;
        cursor = cursor->link;
        free(to_del);
    }
}
