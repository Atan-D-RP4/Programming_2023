#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 20
int stack[MAX];
int top = -1;

bool overflow();
bool underflow();
void push();
void pop();
void peek();
void display();

int main(void)
{
	printf("Stack Operations:\n");
	printf("1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit\n");

	int choice = 0;
	while(true)
	{
		printf("Operation: [1/2/3/4/5]\n");
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
				exit(0);
			default:
				printf("Enter Valid Choice:\n");
		}
	}
}




bool overflow()
{
	return (top == MAX - 1);
}

bool underflow()
{
	return (top == -1);
}

void push()
{
	printf("Enter Integer Element: ");
	int elmnt; scanf("%d", &elmnt);
	if (overflow())
	{
		printf("Stack Overflown\n");
		return;
	}
	stack[++top] = elmnt;
	printf("Element Inserted!\n");
}

void pop()
{
	if(underflow())
	{
		printf("Stack Underflown\n");
		return;
	}
	printf("Element to be removed:%d \n", stack[top--]);
	printf("Element Removed!\n");
}

void peek()
{
	if(overflow())
	{
		printf("Stack Full\n");
		return;
	}

	printf("Top Element: %d\n", stack[top]);
}

void display()
{
	printf("Stack Elements:\n");
	if (underflow())
	{
		printf("Stack Empty\n");
		return;
	}
	for (int i = top; i != -1; i--)
		printf("%d ", stack[i]);
	printf("\n");
}
