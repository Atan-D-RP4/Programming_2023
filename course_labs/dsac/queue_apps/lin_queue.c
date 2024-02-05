// Implements a Linear Queue in C Language

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 5
int queue[MAX];
int front = -1;
int rear = -1;

bool isEmpty();
bool isFull();
void insert();
void delete();
void peek();
void display();

int main(void)
{
	printf("Queue Operations:\n");
	printf("1. Insert\n2. Delete\n3. Peek\n4. Display\n5. Exit\n");
	int choice = 0;
	while(true)
	{
		printf("Operation [1/2/3/4/5]: ");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
				insert();
				break;
			case 2:
				delete();
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
	return (front == -1 || front > rear);
}
bool isFull()
{
	return (rear == MAX - 1);
}

void insert()
{
	int key = 0;
	printf("Element to Insert: "); scanf("%d", &key);
	if (!isFull())
	{
		if (isEmpty())
			front = 0;
		queue[++rear] = key;
	}
	else
	{
		printf("Queue Overflow\n");
		exit(1);
	}
}

void delete()
{
		if (!isEmpty())
		{
			printf("Successfully Deleted %d\n", queue[front++]);
			if (isEmpty())
			{
				front = -1;
				rear = -1;
			}
		}
		else
		{
			printf("Queue Underflow\n");
		}
}

void peek()
{
	if (!isEmpty())
		printf("First Element in Queue: %d", queue[front]);
	else
	{
		printf("Queue Underflow\n");
		exit(1);
	}
}
void display()
{
	if (!isEmpty())
	{
		printf("Queue Elements: ");
		for (int i = front; i <= rear; i++)
			printf("%d ", queue[i]);
		printf("\n");
	}
	else
		printf("Queue Underflow\n");
}
