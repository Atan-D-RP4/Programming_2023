#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct string
{
    char *str;
    uint32_t size;
}string;

typedef struct list
{
    uint8_t data;
    struct list* next;
}list;

typedef struct stack
{
    list* top;
}stack;

typdef struct queue
{
    list* front;
    list* rear;
}queue;

typedef struct dict
{
    list** table;
    uint8_t size;
}dict;

