// A class-like implementation of a Stack in C
// Made it for LeetCode
// The StackDisplay function crashes the program for large values
// Also, the input loop runs infinitely for undefined inputs

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int *min_vals;
    int top;
    int capacity;
} Stack;

Stack* StackCreate() {
    Stack *new = malloc(sizeof(Stack));
    new->data = NULL;
    new->min_vals = NULL;
    new->top = -1;
    new->capacity = 0;
    return new;
}

void StackPush(Stack* obj, int val) {
    if (obj->top == obj->capacity - 1) {
        // Double the capacity if the stack is full
        obj->capacity = (obj->capacity == 0) ? 1 : obj->capacity * 2;
        obj->data = realloc(obj->data, obj->capacity * sizeof(int));
        obj->min_vals = realloc(obj->min_vals, obj->capacity * sizeof(int));
    }
    obj->data[++(obj->top)] = val;
    obj->min_vals[obj->top] = (obj->top == 0 || val < obj->min_vals[obj->top - 1]) ? val : obj->min_vals[obj->top - 1];
}

void StackPop(Stack* obj) {
    if (obj->top >= 0) {
        (obj->top)--;
    }
}

int StackTop(Stack* obj) {
    return (obj->top >= 0) ? obj->data[obj->top] : -1;
}

int StackGetMin(Stack* obj) {
    return (obj->top >= 0) ? obj->min_vals[obj->top] : -1;
}

void StackFree(Stack* obj) {
    free(obj->data);
    free(obj->min_vals);
    free(obj);
}

void StackDisplay(Stack* obj) {
    int top = StackTop(obj);
        printf("Stack: \n");
    for (int i = top; i >= 0; --i) {
        printf("%d\n", obj->data[i]);
    }
}

int main(void) {
    Stack* stack = StackCreate();

    printf("Stack Operations:\n");
	printf("1. Push\n2. Pop\n3. Peek\n4. Minimum\n5.Display\n6. Exit\n");

	int choice = 0;
	while(true)
	{
		printf("Operation: [1/2/3/4/5/6]: ");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
                printf("Enter Element to Push: ");
                scanf("%d", &choice);
                StackPush(stack, choice);
				break;
			case 2:
				printf("Popped Element: %d\n", StackTop(stack));
                StackPop(stack);
				break;
			case 3:
				printf("Top of Stack: %d\n", StackTop(stack));
				break;
            case 4:
                printf("Minimum of Stack: %d\n", StackGetMin(stack));
			case 5:
				StackDisplay(stack);
				break;
			case 6:
                StackFree(stack);
				exit(0);
			default:
				printf("Enter Valid Choice:\n");
		}
	}
}
