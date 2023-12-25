#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

int stack1[MAX]; // Stack for insertion operation
int stack2[MAX]; // Stack for deletion operation

int top1 = -1; // Top of stack1
int top2 = -1; // Top of stack2

bool stack1isFull();
bool stack2isFull();
bool stack1isEmpty();
bool stack2isEmpty();

void insert(int element);
void delete();
void display();

int main() {
    printf("Queue Using Two Stacks Operations:\n");
    printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");

    int choice;
    while (true) {
        printf("Operation: [1/2/3/4]\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Integer Element to Enqueue: ");
                int element;
                scanf("%d", &element);
                insert(element);
                break;

            case 2:
                delete();
                break;

            case 3:
                display();
                break;

            case 4:
                exit(0);

            default:
                printf("Enter Valid Choice:\n");
        }
    }

    return 0;
}

bool stack1isFull() {
    return (top1 == MAX - 1);
}

bool stack2isFull() {
    return (top2 == MAX - 1);
}

bool stack1isEmpty() {
    return (top1 == -1);
}

bool stack2isEmpty() {
    return (top2 == -1);
}

void insert(int element) {
    if (stack1isFull()) {
        printf("Queue Overflow\n");
        return;
    }

    stack1[++top1] = element;
    printf("Element Enqueued!\n");
}

void delete() {
    if (stack1isEmpty() && stack2isEmpty()) {
        printf("Queue Underflow\n");
        return;
    }

    if (stack2isEmpty()) {
        // Transfer elements from stack1 to stack2
        while (!stack1isEmpty()) {
            stack2[++top2] = stack1[top1--];
        }
    }

    printf("Element Dequeued: %d\n", stack2[top2--]);
}

void display() {
    printf("Queue Elements:\n");

    if (stack1isEmpty() && stack2isEmpty()) {
        printf("Queue Empty\n");
        return;
    }

    // Display elements in stack2 (front of the queue)
    for (int i = top2; i >= 0; i--) {
        printf("%d ", stack2[i]);
    }

    // Display elements in stack1 (rear of the queue)
    for (int i = 0; i <= top1; i++) {
        printf("%d ", stack1[i]);
    }

    printf("\n");
}
