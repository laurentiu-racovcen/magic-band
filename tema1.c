/* RACOVCEN Laurentiu - 315CD */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char Item;
#include "DoubleLinkedList.h"

// nodurile din stiva sunt de tip ListNode*
typedef ListNode *StackItem;
#include "Stack.h"

// numarul maxim de caractere a unei operatii
#define MAX_CHARS 25

// Operatiile din coada se salveaza sub forma de string-uri
typedef char *QueueItem;
#include "Queue.h"

// banda impreuna cu degetul
typedef struct band_components {
  List *list;
  ListNode *current_cell;
} Banda;

#include "Operations.h"

int main() {
  // declararea variabilelor pentru utilizarea instructiunii "getline"
  ssize_t line_size = 0;
  char *current_line = NULL;
  size_t buf_size = 0;

  // initializare variabila "operation"
  char *operation = NULL;

  // initializare parametrul operatiei (un caracter) citite de pe linie
  unsigned char param = '-';

  // pentru citire si scriere din/in fisier
  FILE *fout = fopen("tema1.out", "w"), *fin = fopen("tema1.in", "r");

  // alocare memorie pentru dublu lantuita (banda)
  Banda *band = calloc(1, sizeof(Banda));
  band->list = createList();

  // primul element din lista se initializeaza cu '#'
  insertAt(band->list, '#', 0);

  // se initializeaza pozitia degetului pe banda
  band->current_cell = band->list->first->next;

  // se initializeaza stivele pentru operatiile UNDO/REDO
  Stack *UNDO_Stack = createStack();
  Stack *REDO_Stack = createStack();

  // se initializeaza coada
  Queue *q = createQueue();

  // se initializeaza numarul de operatii cu 0
  int nr_oper = 0;

  // citirea numarului de operatii din fisierul tema1.in
  fscanf(fin, "%d\n", &nr_oper);

  // current_line primeste prima linie ce contine o operatie din fisier
  line_size = getline(&current_line, &buf_size, fin);

  // alocare si initializare operation
  // (unde se pastreaza operatia de pe linia curenta)
  operation = calloc(MAX_CHARS, sizeof(char));

  // citire din fisierul "tema1.in" a fiecarei linii si procesarea acesteia
  for (int i = 0; i < nr_oper; i++) {
    // se declara j pentru a parcurge linia citita
    unsigned int j = 0;
    // se citeste operatia de pe linie in variabila "operation"
    while (current_line[j] != ' ' && current_line[j] != '\0' &&
           current_line[j] != '\n') {
      operation[j] = current_line[j];
      j++;
    }
    /* daca operatia contine spatiu pe pozitia "j" => operatia
    are parametru => parametrul operatiei se salveaza in "param" */
    if (current_line[j] == ' ') {
      param = current_line[j + 1];
    }
    // daca operatia este EXECUTE, se executa prima operatie din coada
    if (strcmp(operation, "EXECUTE") == 0) {
      EXECUTE(band, q, UNDO_Stack, REDO_Stack, fout);
      // se scoate din coada operatia executata
      dequeue(q, fout);
      // daca operatia este de tip QUERY
    } else if (strcmp(operation, "SHOW") == 0 ||
               strcmp(operation, "SHOW_CURRENT") == 0) {
      // daca operatia face parte din operatiile valabile
      // pentru tipul QUERY, atunci aceasta se executa
      // daca nu => se returneaza din functie fara sa afiseze nimic
      QUERY(band, operation, fout);
      // daca primeste operatia "UNDO"
    } else if (strcmp(operation, "UNDO") == 0) {
        UNDO(band, UNDO_Stack, REDO_Stack);
    }
      // daca primeste operatia "REDO"
    else if (strcmp(operation, "REDO") == 0) {
        REDO(band, UNDO_Stack, REDO_Stack);
      /* daca operatia nu este niciuna din cele de mai sus,
      atunci operatia se adauga in coada */
    } else {
      char *temp = NULL;
      temp = operation;
      enqueue(q, operation, param);
    }
    // se elibereaza memoria alocata dinamic pentru linia curenta si operatie
    free(current_line);
    free(operation);
    // se aloca memorie initializata
    // (pentru a nu pastra caractere din iteratia precedenta)
    current_line = calloc(MAX_CHARS, sizeof(char));
    operation = calloc(MAX_CHARS, sizeof(char));
    // current_line primeste linia urmatoare din fisierul "tema1.in"
    line_size = getline(&current_line, &buf_size, fin);
  }
  /* dealocare memorie pentru ultima linie citita din fisier
  si pentru operatia de pe aceasta */
  free(current_line);
  free(operation);

  // dealocare memorie pentru lista
  destroyList(band->list);

  /* dealocare memorie pentru stive */

  // daca stiva mai are elemente, se elibereaza memoria alocata pentru ele
  if (UNDO_Stack->head) destroyStack(UNDO_Stack);
  if (REDO_Stack->head) destroyStack(REDO_Stack);
  // daca stiva e goala
  // (sau devine goala in urma executarii instructiunii precedente)
  free(UNDO_Stack);
  free(REDO_Stack);
  destroyQueue(q);
  // dealocare memorie pentru banda
  free(band);
  // inchiderea fisierelor
  fclose(fin);
  fclose(fout);

  return 0;
}
