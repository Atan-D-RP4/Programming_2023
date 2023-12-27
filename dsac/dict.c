#include <stdio.h>
#include <stdlib.h>

#define MAX 7

typedef struct node
{
    int data;
    struct node* link;
}node;

node* table[MAX];

void delete_all();
void display(void);


int main(void)
{
    printf("No.of Elements to Insert: ");
    int n; scanf("%d", &n);
    for (int i = 0; i < MAX; i++)
    {
        table[i] = NULL;
    }

    printf("Enter Elements:\n");

    while (n > 0)
    {
        int key = 0;
        scanf("%d", &key);
        node* new = (node*)malloc(sizeof(node));
        if (new == NULL)
        {
            printf("Insufficient Memory\n");
            delete_all();
            exit(-1);
        }
        new->data = key;
        new->link = NULL;

        int hash = key % MAX;

        node* crsr = NULL;
        if (table[hash] == NULL)
        {
            new->link = table[hash];
            table[hash] = new;
            n--;
            continue;
        }
        for (crsr = table[hash]; crsr->link != NULL && crsr != NULL; crsr = crsr->link);
        new->link = (crsr ? crsr->link : NULL);
        if(crsr)
            crsr->link = new;
        n--;
    }

    display();
    delete_all();
    exit(0);
}


void delete_all()
{
    for (int i = 0; i < MAX; i++)
    {
        if (table[i] == NULL)
            continue;
        for (node* crsr = table[i]; crsr != NULL; )
        {
            node* to_del = crsr;
            crsr = crsr->link;
            free(to_del);
        }
    }
}

void display()
{
    for (int i = 0; i < MAX; i++)
    {
        printf("Index %d: ", i);
        for (node* crsr = table[i]; crsr != NULL; crsr = crsr->link)
            printf("%d ", crsr->data);
        printf("\n");
    }
}
