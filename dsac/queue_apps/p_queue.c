// Implements a Circular Priority Queue in C Language
// Finished

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 5
int queue[MAX];
bool mode = false;
int front = -1;
int rear = -1;

bool isEmpty();
bool isFull();
void p_insert(int key);
void insert();
void delete ();
void peek();
void display();

int main(int argc, char *argv[])
{
    printf("Select Queue Mode:\n 1. Circular\t2. Priority\n[1/2]");
    char c;
    scanf("%c", &c);
    if (c == '2')
        mode = true;
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
    return (front == -1 || rear == -1);
}

bool isFull()
{
    return ((front == 0 && rear == MAX - 1) || front == rear + 1);
}

void p_insert(int key)
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i <= rear; i++)
    {
        if (key < queue[i])
        {
            k = 1;
            for (j = rear + 1; j > i; j--)
            {
                queue[j] = queue[j - 1];
            }
            queue[i] = key;
            rear = (rear + 1) % MAX;
            break;
        }
    }

    if (k == 0)
    {
        queue[rear + 1] = key;
        rear = (rear + 1) % MAX;
    }
}

void insert()
{
    printf("Element to Insert: ");
    int key = 0;
    scanf("%d", &key);
    if (!isFull())
    {
        if (isEmpty())
        {
            front = 0;
            rear = 0;
            queue[rear] = key;
        }
        else
        {
            if (mode)
                p_insert(key);
            else
            {
                rear = (rear + 1) % MAX;
                queue[rear] = key;
            }
            printf("%d Successfully Inserted\n", key);
        }
    }
    else
        printf("Queue Overflow\n");
}

void delete ()
{
    if (!isEmpty())
    {
        int key = queue[front];
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
            front = (front + 1) % MAX;
        printf("%d Successfully Deleted\n", key);
    }
    else
        printf("Queue Underflow\n");
}

void peek()
{
    if (!isEmpty())
    {
        printf("First Element in Queue: %d\n", queue[front]);
        printf("Last Element in Queue: %d\n", queue[rear]);
    }
    else
    {
        printf("Queue Underflow\n");
        return;
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
        while (i != (rear + 1) % MAX);
        printf("\n");
    }
    else
        printf("Queue Underflow\n");
}
