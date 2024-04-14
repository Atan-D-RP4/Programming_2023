// A basic Generic Singly-Linked List implemented in C using void pointers
// Has only Append, Preppend, Print, and Drop methods implemented
// Just for practice

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct GList {
    size_t size;
    Node *head;
} GList;

void print_int(void* integer) {
    printf("%d ", *((int*) integer));
}

void print_string(void* string) {
    printf("%s", (char*) string);
}

GList* GList_new(size_t size);
Node* get_node(void *data);
void GList_append(GList *list, void* data);
void GList_preppend(GList *list, void* data);
void GList_print(GList *list, void (*print)(void*));
void GList_drop(GList *list);

int main(void) {
    printf("Tests: \n");

    GList *list1 = GList_new(sizeof(int64_t));

    int arr[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
        GList_preppend(list1, &arr[i]);
    GList_print(list1, print_int);

    printf("%p\n%p\n%zu\n", list1, list1->head, list1->size);

    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
        GList_append(list1, &arr[i]);
    GList_print(list1, print_int);

    char* strings[] = {
        "Hello",
        ",",
        " World",
        "!",
        "\nFuck You"
    };

    GList *list2 = GList_new(sizeof(int64_t));

    for (int i = (sizeof(strings) / sizeof(char *)) - 1; i >= 0; --i)
        GList_preppend(list2, strings[i]);
    GList_print(list2, print_string);

    for (int i = (sizeof(strings) / sizeof(char *)) - 1; i >= 0; --i)
        GList_append(list2, strings[i]);
    GList_print(list2, print_string);

    printf("%p\n%p\n%zu\n", list2, list2->head, list2->size);

    GList_drop(list1);
    GList_drop(list2);
}


GList* GList_new(size_t size) {
    GList *list = malloc(sizeof(GList));
    if (list == NULL)
    {
        fprintf(stderr, "Out of Memory to create new List!\n");
        return NULL;
    }

    list->head = NULL;
    list->size = size;

    return list;
}


Node* get_node(void *data) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
    {
        fprintf(stderr, "Out of Memory to create new Node!\n");
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

void GList_append(GList *list, void* data) {

    Node *node = get_node(data);
    if (node == NULL)
    {
        fprintf(stderr, "Preppend Op failed\n");
        return;
    }

    if (list->head == NULL)
    {
        list->head = node;
        return;
    }

    Node* start = list->head;
    Node* crsr = start;
    for ( ; crsr->next != NULL; crsr = crsr->next);
    crsr->next = node;
}


void GList_preppend(GList *list, void* data) {
    Node *node = get_node(data);
    if (node == NULL)
    {
        fprintf(stderr, "Preppend Op failed\n");
        return;
    }

    if (list->head == NULL)
    {
        list->head = node;
        return;
    }

    node->next = list->head;
    list->head = node;
}

void GList_print(GList *list, void (*print)(void*))
{
    Node *start = list->head;
    if (start == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    for (Node *crsr = start; crsr != NULL; crsr = crsr->next)
        print(crsr->data);
    printf("\n");
}

void GList_drop(GList *list)
{
    if (list->head == NULL)
        return;

    Node* start = list->head;
    for (Node *crsr = start; crsr != NULL; ) {
        Node *dropped = crsr;
        crsr = crsr->next;
        free(dropped);
    }
    free(list);
}
