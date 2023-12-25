#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct node
{
    int key;
    struct node* link;
}node;

node* append(node* start, int key)
{
    node* new = (node*)malloc(sizeof(node));
    if (new == NULL)
    {
        printf("List Overflow. Failed to Allocate Memory!");
        exit(1);
    }
    new->key = key;
    new->link = NULL;
    if (start == NULL)
    {
        start = new;
        return start;
    }
    new->link = start;
    start = new;
    return start;
}

int main(void)
{
    printf("Enter List\n");
    int size = 0;
    node* list = NULL; long list_median = 0.0;

    while (true)
    {
        char key[1];
        printf("Enter 'x' to exit\n");
        printf("Enter Element: ");
        scanf("%s", key);
        if (key[0] == 'x')
            break;
        list = append(list, atoi(key));
        size++;
    }

    int arr[size];
    int mid = size / 2;

    int i = size - 1; node* cursor = list;

    while(cursor != NULL)
    {
        node* tmp = cursor;
        arr[i--] = cursor->key;
        cursor = cursor->link;
        free (tmp);
    }

    if (mid % 2 == 1)
        list_median = arr[mid];
    else
        list_median = (arr[mid - 1] + arr[mid]) / 2;

    printf("Median of the List is %ld\n", list_median);
}
