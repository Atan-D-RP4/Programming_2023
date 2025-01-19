#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
	int *data;
	struct Node *next;
} Node;

typedef struct List {
	Node *head;
} List;

List* init_list() {
	List *list = (List *)malloc(sizeof(List));
	list->head = NULL;
	return list;
}

List* insert_list(List *list, Node *item) {
	item->next = list->head;
	list->head = item;
	return list;
}

List* delete_list(List *list, Node *target) {
	Node **p = &list->head;
	while (*p != target) {
		p = &(*p)->next;
	}
	*p = target->next;
	free(target);

	return list;
}

List* reverse_list(List *list) {
	Node* prev = NULL;
	Node* curr = list->head;
	Node* next = NULL;

	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	return list;
}

void print_list(List *list) {
	Node *p = list->head;
	while (p) {
		printf("%d ", *p->data);
		p = p->next;
	}
	printf("\n");
}
