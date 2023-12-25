// Implements a Circular Queue in C Language (Done)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 20
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
		printf("Operation: [1/2/3/4/5]\n");
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
	return (front == -1);
}

bool isFull()
{
	return (((front == 0) && (rear == (MAX - 1))) || (front == rear + 1));
}

void insert()
{
	printf("Element to Insert: ");
	int key = 0; scanf("%d", &key);

	if (!isFull())
	{
		if (isEmpty())
		{
			front = 0;
			rear = 0;
		}
		else
			rear = (rear + 1) % MAX;
		queue[rear] = key;
		printf("%d Successfully Inserted\n", key);
	}
	else
		printf("Queue Overflow\n");
}

void delete()
{
	if (!isEmpty())
	{
		int key = queue[front];
		printf("Element Deleted: %d\n", key);
		if (front == rear)
        {
            front = -1;
            rear = -1;
        }
		else
			front = (front + 1) % MAX;
	}
	else
	{
		printf("Queue Underflow\n");
		exit(1);
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
        int i = front;
        do
        {
            printf("%d ", queue[i]);
            i = (i + 1) % MAX;
        }
        while(i != (rear + 1) % MAX);
        printf("\n");
    }
    else
        printf("Queue Underflow\n");
}
