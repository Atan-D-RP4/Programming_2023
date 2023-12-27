// Infix Expresssion to [Pre/Post]-Fix Expression Converter
// Only for Single Digit Numbers

// Fuck Evalution of Converted Expressions
// The Double-Digit version of this can handle it

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define MAX 50
char stack[MAX];
int top = -1;

int usage(int argc, char* argv[]);
bool isFull();
bool isEmpty();
void push(char oprtr);
char pop();
int priority(char oprtr);
char* in_to_postfix(char* infix_expr, int size);
char* in_to_prefix(char* infix_expr, int size);
char* strrev(char* string, int size);
int eval_postfix(char *expr);
int eval_prefix(char *expr);
int oprtr_e(int a, int b, char oprtr);


int main(int argc, char* argv[])
{
    int error = usage(argc, argv);
    if(error != 0)
        return error;

    char* expr = argv[1]; int size = strlen(argv[1]);
    char* postfix_expr = in_to_postfix(expr, size);
    if (postfix_expr != NULL)
    {
        printf("The Post Fix Expression: %s\n", postfix_expr);
        free(postfix_expr);
    }
    char* prefix_expr = in_to_prefix(expr, size);
    if(prefix_expr != NULL)
    {
        printf("The Pre Fix Expression:  %s\n", prefix_expr);
        free(prefix_expr);
    }
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
        printf("5. Parenthesis:    '[]'\n");
        printf("6. Exponent:       '^'\n");
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

void push(char oprtr)
{
	if (isFull())
	{
		printf("Stack Overflow\n");
		exit(2);
	}
	stack[++top] = oprtr;
}

char pop()
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
        return (ch == '[' || ch == ']' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}


char* in_to_postfix(char* infix_expr, int size)
{
    char* postfix_expr = (char*)malloc((size + 2)* sizeof(char));
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (infix_expr[i] == ' ' || infix_expr[i] == '\t')
                continue;

        if (isalnum(infix_expr[i]))
        {
                postfix_expr[j++] = infix_expr[i];
        }
        else if (is_oprtr(infix_expr[i]))
        {
                if (infix_expr[i] == '[')
                {
                        while (!isEmpty() && (priority(infix_expr[i]) <= priority(stack[top])) && (stack[top] != '['))
                                postfix_expr[j++] = pop();
                        push(infix_expr[i]);
                        continue;
                }
                else if (infix_expr[i] == ']')
                {
                        for (; !isEmpty() && stack[top] != '['; postfix_expr[j++] = pop());
                        top--;
                        continue;
                }
                while (!isEmpty() && (priority(infix_expr[i]) <= priority(stack[top])) && (stack[top] != '['))
                        postfix_expr[j++] = pop();
                push(infix_expr[i]);
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

int eval_postfix(char* expr)
{
        int a, b;
        for (int i = 0; i < strlen(expr); i++)
        {
                if (!is_oprtr(expr[i]))
                        push(expr[i]);
                else
                {
                        a = pop();
                        b = pop();
                        push((char)oprtr_e(b, a, expr[i]));
                }
        }
        return pop();
}

int eval_prefix(char* expr)
{
        return (eval_postfix(strrev(expr, strlen(expr))));
}

int oprtr_e(int a, int b, char oprtr)
{
        int result;
        switch(oprtr)
        {
                case '+':
                        result = b + a;
                        break;
                case '-':
                        result = b - a;
                        break;
                case '*':
                        result = b * a;
                        break;
                case '/':
                        result = b / a;
                        break;
                case '^':
                        result = pow(b,a);
                        break;
        }
        return result;
}
