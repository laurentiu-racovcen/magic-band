/* RACOVCEN Laurentiu - 315CD */
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
  QueueItem operation;
  unsigned char param;
  struct QueueNode* next;
} QueueNode;

typedef struct Queue {
  QueueNode* front;
  QueueNode* rear;
  long size;
} Queue;

// Crearea unei cozi
Queue* createQueue(void) {
  Queue* q = (Queue*)calloc(1, sizeof(Queue));
  return q;
}

// Verifica daca coada este goala
int isQueueEmpty(Queue* q) {
  if (q == NULL || q->rear == NULL) return 1;
  return 0;
}

// Adauga un element in coada
void enqueue(Queue* q, QueueItem temp_oper, unsigned char param) {
  if (q == NULL) return;
  QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
  node->next = NULL;
  /* daca coada este goala */
  if (isQueueEmpty(q) == 1) {
    node->operation = calloc(MAX_CHARS, sizeof(char));

  // while copiere in "operation" al nodului cozii
  for (int i = 0; i < strlen(temp_oper); i++) {
    node->operation[i] = temp_oper[i];
  }
  node->param = param;
  q->rear = q->front = node;
  q->size++;
  return;
  }
  node->operation = calloc(MAX_CHARS, sizeof(char));
  /* daca coada are cel putin un element */
  for (int i = 0; i < strlen(temp_oper); i++) {
    node->operation[i] = temp_oper[i];
  }
  node->param = param;
  q->rear->next = node;
  // "node" devine ultimul nod din coada
  q->rear = node;
  q->size++;
}

// Returneaza valoarea primului element din coada
QueueItem front(Queue* q) {
  return q->front->operation;
}

// Extrage un element din coada (dupa regula FIFO)
void dequeue(Queue* q, FILE* fout) {
  if (q == NULL) return;
  // coada este goala
  if (isQueueEmpty(q) == 1) {
    return;
  }
  // coada contine doar un element
  if (q->front == q->rear) {
    free(q->front->operation);
    free(q->front);
    q->front = q->rear = NULL;
    q->size--;
    return;
  }
  // coada contine mai multe elemente
  QueueNode* aux = q->front;
  q->front = q->front->next;
  free(aux->operation);
  free(aux);
  q->size--;
}

// Dealocare memorie alocata dinamic pentru coada
void destroyQueue(Queue* q) {
  QueueNode* iter = q->front;
  while (iter != NULL) {
    QueueNode* aux = iter;
    iter = iter->next;
    // se elibereaza memoria alocata pentru operatie
    free(aux->operation);
    // se elibereaza memoria alocata pentru nodul precedent al cozii
    free(aux);
  }
  free(q);
}
