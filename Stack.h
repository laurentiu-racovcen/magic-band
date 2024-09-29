/* RACOVCEN Laurentiu - 315CD */
#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
  StackItem elem;
  struct StackNode* next;
} StackNode;

typedef struct Stack {
  StackNode* head;
  long size;
} Stack;

// Creeaza stiva
Stack* createStack(void) {
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  stack->size = 0;
  stack->head = NULL;
  return stack;
}

// Verifica daca stiva este goala
int isStackEmpty(Stack* stack) {
  if (stack == NULL) return 1;
  if (stack->head == NULL) return 1;
  return 0;
}

// Adauga un element in stiva
void push(Stack* stack, StackItem elem) {
  if (stack == NULL) return;
  if (isStackEmpty(stack) == 1) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->next = NULL;
    newNode->elem = elem;
    stack->head = newNode;
    stack->size++;
  } else {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->next = stack->head;
    stack->head = newNode;
    newNode->elem = elem;
    stack->size++;
  }
}

// Extrage elementul din varful stivei
void pop(Stack* stack) {
  if (isStackEmpty(stack) == 1) return;
  StackNode* aux = stack->head;
  stack->head = stack->head->next;
  free(aux);
  stack->size--;
}

// Dealocarea memoriei alocata pentru stiva
void destroyStack(Stack* stack) {
  StackNode* iter = stack->head;
  while (iter != NULL) {
    StackNode* prev = iter;
    iter = iter->next;
    free(prev);
  }
  stack->head = NULL;
}
