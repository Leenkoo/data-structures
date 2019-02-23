#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
	int data;
	struct Node* next;
} Node;

typedef struct List
{
	Node* head;
	Node* tail;
} List;

List ListCreate()
{
	List list;
	list.head = NULL;
	list.tail = NULL;
	return list;
}

void ListPrepend(List* list, int data)
{
	if (list == NULL)
		return;
	Node* t = malloc(sizeof(Node));
	t->data = data;
	t->next = list->head;
	list->head = t;
	if (list->tail == NULL)
		list->tail = t;
}

void ListAppend(List* list, int data)
{
	if (list == NULL)
		return;
	Node* t = malloc(sizeof(Node));
	t->data = data;
	t->next = NULL;
	if (list->head == NULL)
		list->head = t;
	if (list->tail != NULL)
		list->tail->next = t;
	list->tail = t;
}

void NodeFree(Node* node)
{
	if (node == NULL)
		return;
	//free(node->data);
	NodeFree(node->next);
	node->next = NULL;
	free(node);
}
void ListDestroy(List* list)
{
	if (list == NULL)
		return;
	NodeFree(list->head);
	list->head = NULL;
}

void ListPrint(List* list)
{
	printf("List: ");
	for (Node* it = list->head; it != NULL; it = it->next)
	{
		if (it != list->head)
			printf("->");
		printf("%d", it->data);
	}
	printf("\n");
}

int main()
{
	List list = ListCreate();
	for (int i = 1; i <= 10; ++i)
	{
		ListPrint(&list);
		ListAppend(&list, i);
	}
	ListPrint(&list);
	ListDestroy(&list);
	ListPrint(&list);
	return 0;
}

