// Implements a Circular Double-Ended(DE) Queue
// Finished

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 5
int queue[MAX];
int front = -1, rear = -1;

bool isEmpty();
bool isFull();
void insertFront();
void insertRear();
void deleteRear();
void deleteFront();
void peek();
void display();

int main(void)
{
    printf("Queue Operations:\n");
    printf("1. Insert at Rear\n2. Insert at Front\n");
    printf("3. Delete at Front \n4. Delete at Rear\n");
    printf("5. Status\n");
    printf("6. Display\n7. Exit\n");
    int choice = 0;
    while (true)
    {
        printf("Operation [1/2/3/4/5/6/7]: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                insertRear();
                break;
            case 2:
                insertFront();
                break;
            case 3:
                deleteFront();
                break;
            case 4:
                deleteRear();
                break;
            case 5:
                peek();
                break;
            case 6:
                display();
                break;
            case 7:
                exit(0);
                break;
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
    return ((front == 0 && rear == MAX - 1) || front == rear + 1);
}

void insertRear() // Base Insert
{
    if (isFull())
    {
        printf("Queue Overflow\n");
        return;
    }

    int key = 0;
    printf("Element to Insert: ");
    scanf("%d", &key);

    if (isEmpty())
    {
        front = 0;
        rear = 0;
    }
    else
        rear = (rear + 1) % MAX;
    queue[rear] = key;
    printf("%d Successfully Inserted\n", queue[rear]);
}

void insertFront()
{
    if (isFull())
    {
        printf("Queue Overflow\n");
        return;
    }

    int key = 0;
    printf("Element to Insert: ");
    scanf("%d", &key);

    if (isEmpty())
    {
        front = 0;
        rear = 0;
    }
    else if (front == 0)
        front = MAX - 1;
    else
        front = (front - 1) % MAX;
    queue[front] = key;
    printf("%d Successfully Inserted\n", queue[front]);
}

void deleteFront() // Base Delete
{
    if (isEmpty())
    {
        printf("Queue Underflow\n");
        return;
    }
    printf("Element Deleted: %d\n", queue[front]);
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
        front = (front + 1) % MAX;
}

void deleteRear()
{
    if (isEmpty())
    {
        printf("Queue Underflow\n");
        return;
    }
    int key = queue[rear];
    printf("Element Deleted: %d\n", key);
    if (rear == front)
        front = rear - 1;
    else if (rear == 0)
        rear = MAX - 1;
    else
        rear = (rear - 1) % MAX;
}

void peek()
{
    if (!isEmpty())
    {
        printf("First Element in Queue: %d\n", queue[front]);
        printf("Last Element in Queue: %d\n", queue[rear]);
    }
    else
        printf("Queue Underflow\n");
}

void display()
{
    if (isEmpty())
    {
        printf("Queue Underflow\n");
        return;
    }

    printf("Queue Elements: ");
    int i = front;
    do
    {
        printf("%d ", queue[i]);
        i = (i + 1) % MAX;
    }
    while (i != (rear + 1) % MAX);
    printf("\n");
}
