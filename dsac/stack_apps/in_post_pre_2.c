// Infix Expresssion to [Pre/Post]-Fix Expression Converter
// I was a fool
// This is the Double-Digit version for handling it
// Along with Evaluation of Expression
// And it only required the Stack to be an
// INTEGER ARRAY!!!!!!!!!

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 50
int stack[MAX];
int top = -1;

int usage(int argc, char* argv[]);
char* in_to_prefix(char* infix_expr, int size);
char* strrev(char* string, int size);
int oprtr_e(int a, int b, char oprtr);

bool isFull();
bool isEmpty();
void push(int oprtr);
int pop();
int priority(char oprtr);
int eval_prefix(char *expr);
char* in_to_postfix(char* infix_expr, int size);
int eval_postfix(char *expr);


int main(int argc, char* argv[])
{
    int error = usage(argc, argv);
    if(error != 0)
        return error;

    char* expr = argv[1]; int size = strlen(argv[1]);
    char* postfix_expr = in_to_postfix(expr, size);

    if (postfix_expr != NULL)
        printf("The Post Fix Expression: %s\n", postfix_expr);
    else
        printf("Failed to allocate Memory\n");
    char* prefix_expr = in_to_prefix(expr, size);

    if(prefix_expr != NULL)
        printf("The Pre Fix Expression:  %s\n", prefix_expr);
    else
        printf("Failed to allocate Memory\n");

    printf("Expression Evaluation: %d\n", eval_postfix(postfix_expr));
    printf("Expression Evaluation: %d\n", eval_postfix(postfix_expr_mine));
    free(postfix_expr);
    free(prefix_expr);
    return 0;
}





int usage(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./inToPre [Expression(No spaces)]\n");
        printf("Operators Recognized:\n");
        printf("1. Addition:       '+'\n");
        printf("2. Subtraction:    '-'\n");
        printf("3. Multiplication: '*'\n");
        printf("4. Divison:        '/'\n");
        printf("5. Exponent:       '^'\n");
        printf("6. Remainder:      '%c'\n", '%');
        printf("7. Parenthesis:    '[]'\n");
        printf("Example Expression: 5^2+3/4\n");
        return 1;
    }
    return 0;
}


bool isFull()
{
	return (top == MAX - 1);
}

bool isEmpty()
{
	return (top == -1);
}

void push(int oprtr)
{
	if (isFull())
	{
		printf("Stack Overflow\n");
		exit(2);
	}
	stack[++top] = oprtr;
}

int pop()
{
        if (isEmpty())
	{
		printf("Stack Underflow\n");
		exit(3);
	}
	return stack[top--];
}


int priority(char oprtr)
{
    switch(oprtr)
    {
        case '[':
                return 0;

        case ']':
                return 0;

        case '+':
                return 1;

        case '-':
                return 1;

        case '*':
                return 2;

        case '/':
                return 2;

        case '^':
                return 3;

        default:
                return 0;
    }
}

bool is_oprtr(char ch)
{
        return (ch == '[' || ch == ']' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%');
}


char* in_to_postfix(char* infix_expr, int size)
{
    char* postfix_expr = (char*)malloc((size + 2)* sizeof(char));
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        char expr = infix_expr[i];
        if (expr == ' ' || expr == '\t')
                continue;

        if (isalnum(expr))
        {
                postfix_expr[j++] = expr;
        }
        else if (is_oprtr(expr))
        {
                if (expr == '[')
                {
                        push(expr);
                        continue;
                }
                else if (expr == ']')
                {
                        for (; !isEmpty() && stack[top] != '['; postfix_expr[j++] = pop());
                        top--;
                        continue;
                }
                while (!isEmpty() && (priority(expr) <= priority(stack[top])) && (stack[top] != '['))
                        postfix_expr[j++] = pop();
                push(expr);
        }
    }
    while(!isEmpty())
    {
        if (!isEmpty() && stack[top] == '[')
        {
                printf("Invalid Expression\n");
                free(postfix_expr);
                return NULL;
        }
        else if(stack[top] == '[')
                pop();

        if (!isEmpty())
                postfix_expr[j++] = pop();
    }

    postfix_expr[j] = '\0';

    return postfix_expr;
}

char* in_to_prefix(char* infix_expr, int size)
{
        char* rev_expr = strrev(infix_expr, size);
        char* rev_in_expr = in_to_postfix(rev_expr, strlen(rev_expr));
        char* prefix_expr = strrev(rev_in_expr, strlen(rev_in_expr));
        free(rev_expr);
        free(rev_in_expr);
        return prefix_expr;
}

char* strrev(char* string, int size)
{
        char* rev_string = (char*)malloc(sizeof(char) * size);

        for (int i = size - 1, j = 0; i >= 0 && j < size;)
        {
                rev_string[j++] = string[i--];
                if (rev_string[j - 1] == '[')
                        rev_string[j - 1] = ']';
                else if (rev_string[j - 1] == ']')
                        rev_string[j - 1] = '[';
        }
        rev_string[size] = '\0';
        return rev_string;
}

int eval_prefix(char* expr)
{
        return (eval_postfix(strrev(expr, strlen(expr))));
}

int eval_postfix(char* expr)
{
        int a, b;
        for (int i = 0; i < strlen(expr); i++)
        {
                if (!is_oprtr(expr[i]))
                        push(expr[i] - '0');
                else
                {
                        b = pop();
                        a = pop();
                        push(oprtr_e(a, b, expr[i]));
                }
        }
        return pop();
}

int oprtr_e(int a, int b, char oprtr)
{
        int result = 1;
        switch(oprtr)
        {
                case '+':
                        result = a + b;
                        break;
                case '-':
                        result = a - b;
                        break;
                case '*':
                        result = a * b;
                        break;
                case '/':
                        result = a / b;
                        break;
                case '%':
                        result = a % b;
                        break;
                case '^':
                        result = (int)pow(a,b);
                        break;
        }
        return result;
}
