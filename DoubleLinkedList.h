/* RACOVCEN Laurentiu - 315CD */
#include <stdlib.h>

typedef struct ListNode {
  Item elem;
  struct ListNode* next;
  struct ListNode* prev;
} ListNode;

typedef struct List {
  ListNode* first;
  ListNode* last;
} List;

List* initList() {
  List* sentinel = (List*)calloc(1, sizeof(List));
  return sentinel;
}

// Creeaza un nou nod
ListNode* createNode(Item elem) {
  ListNode* node = (ListNode*)malloc(sizeof(ListNode));
  node->next = NULL;
  node->prev = NULL;
  node->elem = elem;
  return node;
}

// Creeaza o noua lista (goala)
List* createList(void) {
  List* list = initList();
  list->first = calloc(1, sizeof(ListNode));
  return list;
}

// Determina daca lista este goala
// returneaza 1 - daca e goala, 0 - daca nu e goala
int isEmpty(List* list) {
  if (list->first->next == NULL) return 1;
  return 0;
  // return (!list->first && !list->last);
}

int length(List* list) {
  if (list == NULL) return 0;

  if (isEmpty(list)) return 0;

  ListNode* iter = list->first->next;
  int len = 0;
  while (iter != NULL) {
    iter = iter->next;
    len++;
  }

  return len;
}

// Introduce un nou element in lista la pozitia "pos" (pos incepe cu 0)
void insertAt(List* list, Item elem, int pos) {
  if (list == NULL) return;

  ListNode* iter = list->first->next;
  /* daca pozitia data este mai mare decat lungimea listei,
  nu se efectueaza schimbari asupra listei */
  if (pos > length(list)) return;
  // se itereaza in lista pana se ajunge la nodul de la pozitia "pos"
  int k = 0;
  while (iter != NULL && k < pos) {
    iter = iter->next;
    k++;
  }

  if (pos == k) {
    /* daca lista e goala */
    if (isEmpty(list) == 1) {
      ListNode* newNode = NULL;
      newNode = createNode(elem);
      newNode->prev = list->first;
      list->first->next = newNode;
      list->last = newNode;
      return;
    }
    /* daca lista nu e goala */
    // insert pe ultima pozitie (dupa toate elementele)
    if (iter == NULL) {
      ListNode* newNode = NULL;
      newNode = createNode(elem);
      list->last->next = newNode;
      newNode->prev = list->last;
      newNode->next = NULL;
      list->last = newNode;
      return;
    }
    // insert pe prima pozitie
    if (iter->prev->prev == NULL) {
      ListNode* newNode = NULL;
      newNode = createNode(elem);
      newNode->next = list->first->next;
      newNode->prev = list->first;
      newNode->next->prev = newNode;
      list->first->next = newNode;
      return;
    }
    // insert normal (in interiorul listei)
    ListNode* newNode = NULL;
    newNode = createNode(elem);
    newNode->next = iter;
    newNode->prev = iter->prev;
    iter->prev->next = newNode;
    iter->prev = newNode;
  }
}

List* destroyList(List* list) {
  if (list == NULL) return NULL;

  if (isEmpty(list)) {
    free(list->first);
    free(list);
    return NULL;
  }

  ListNode* iter = list->first;
  while (iter->next != NULL) {
    iter = iter->next;
    free(iter->prev);
  }

  // eliberarea memoriei pentru ultimul nod din lista
  free(iter);

  // eliberarea memoriei pentru lista alocata dinamic
  free(list);

  list = NULL;
  return list;
}
