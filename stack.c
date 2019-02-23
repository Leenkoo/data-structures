#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
	int data;
	struct Node* next;
} Node;


typedef struct Stack
{
	Node* head;
} Stack;


Stack StackCreate()
{
	Stack stack;
	stack.head = NULL;
	return stack;
}

void StackPush(Stack* stack, const int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = stack->head;
	stack->head = node;
}

int StackTop(Stack* stack)
{
	if (stack->head == NULL)
		exit(1);
	return stack->head->data;
}

void StackPop(Stack* stack)
{
	if (stack->head == NULL)
		return;
	Node* prev = stack->head;
	stack->head = stack->head->next;
	free(prev);
}

void NodeFree(Node* node)
{
	if (node == NULL)
		return;
	NodeFree(node->next);
	node->next = NULL;
	free(node);
}

void StackDelete(Stack* stack)
{
	if (stack->head == NULL)
		return;
	NodeFree(stack->head);
	stack->head = NULL;
}

bool StackEmpty(Stack* stack)
{
	return stack->head == NULL;
}


int main()
{
	Stack stack = StackCreate();


	for (int i = 1; i < 11; ++i)
	{
		StackPush(&stack, i);
	}

	while (StackEmpty(&stack) == 0)
	{
		printf("%d", StackTop(&stack));
		StackPop(&stack);
		if (StackEmpty(&stack) == 0)
			printf("->");
		else
			printf("\n");
	}
	StackTop(&stack);
	StackDelete(&stack);

	return 0;
}
