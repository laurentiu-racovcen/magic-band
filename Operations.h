/* RACOVCEN Laurentiu - 315CD */
void UPDATE(Banda* band, char* operation, unsigned char param,
Stack* UNDO_Stack, Stack* REDO_Stack, FILE* fout) {
  if (strcmp(operation, "MOVE_LEFT") == 0) {
    // daca la stanga degetului se afla santinela, se returneaza
    if (band->current_cell->prev == band->list->first) {
      return;
    }

    // operatia poate fi executata,
    // deci se adauga pozitia curenta a degetului in stiva UNDO
    push(UNDO_Stack, band->current_cell);

    // la stanga nu se afla santinela, deci degetul se muta la stanga
    band->current_cell = band->current_cell->prev;
    return;
  }
  if (strcmp(operation, "MOVE_RIGHT") == 0) {
    // daca la dreapta degetului se afla NULL
    if (!band->current_cell->next) {
      // operatia poate fi executata,
      // deci se adauga pozitia curenta a degetului in stiva UNDO
      push(UNDO_Stack, band->current_cell);

      /* se creeaza un nou nod la dreapta degetului,
       * acest nod se initializeaza cu '#',
       * iar pozitia degetului va indica acest nod din dreapta */
      insertAt(band->list, '#', length(band->list));
      band->current_cell = band->current_cell->next;
      return;
    }
    // la dreapta degetului se afla un element
    /* operatia poate fi executata, deci se adauga pozitia curenta a
     * degetului in stiva UNDO */
    push(UNDO_Stack, band->current_cell);
    band->current_cell = band->current_cell->next;
    return;
  }
  if (strcmp(operation, "MOVE_LEFT_CHAR") == 0) {
    ListNode* iter = band->current_cell;
    // atat timp cat nu s-a ajuns la santinela
    while (iter != band->list->first) {
      if (iter->elem == param) {
        /* operatia poate fi executata, deci se adauga pozitia curenta a
         * degetului in stiva UNDO */
        push(UNDO_Stack, band->current_cell);
        // se modifica pozitia degetului
        band->current_cell = iter;
        return;
      }
      iter = iter->prev;
    }
    /* daca s-a ajuns la santinela => elementul nu a fost gasit
     * => se afiseaza "ERROR" */
    fprintf(fout, "ERROR\n");
    return;
  }
  if (strcmp(operation, "MOVE_RIGHT_CHAR") == 0) {
    /* operatia poate fi executata, deci se adauga pozitia curenta a
     * degetului in stiva UNDO */
    push(UNDO_Stack, band->current_cell);
    // atat timp cat nu s-a ajuns la NULL din dreapta
    while (band->current_cell->next) {
      // daca s-a gasit caracterul cautat, se returneaza
      if (band->current_cell->elem == param) {
        return;
      }
      band->current_cell = band->current_cell->next;
    }
    /* daca fix ultimul element == param,
     * atunci se modifica pozitia curenta a degetului */
    if(band->current_cell->elem == param) return;
    /* daca s-a ajuns la NULL => elementul nu a fost gasit
     * => se adauga '#' la sfarsitul listei */
    insertAt(band->list, '#', length(band->list));
    // degetul se pune pe caracterul '#' de la finalul listei
    band->current_cell = band->current_cell->next;
    return;
  }
  // la pozitia curenta se scrie caracterul primit in variabila "param"
  if (strcmp(operation, "WRITE") == 0) {
    // daca primeste operatia "WRITE", se golesc stivele UNDO si REDO
    destroyStack(UNDO_Stack);
    destroyStack(REDO_Stack);
    band->current_cell->elem = param;
    return;
  }
  if (strcmp(operation, "INSERT_LEFT") == 0) {
    // daca la stanga degetului se afla santinela
    // se afiseaza "ERROR" si se returneaza
    if (band->current_cell->prev == band->list->first) {
      fprintf(fout, "ERROR\n");
      return;
    }
    // daca la stanga nu se afla santinela,
    // se insereaza un caracter in stanga degetului
    ListNode* newNode = createNode(param);
    newNode->next = band->current_cell;
    newNode->prev = band->current_cell->prev;
    band->current_cell->prev->next = newNode;
    band->current_cell->prev = newNode;

    band->current_cell = newNode;
    band->current_cell->elem = param;
    return;
  }
  if (strcmp(operation, "INSERT_RIGHT") == 0) {
    // daca pozitia degetului este pe ultimul caracter din lista
    if (!band->current_cell->next) {
      // se insereaza caracterul din "param" la dreapta degetului
      insertAt(band->list, param, length(band->list));
      band->current_cell = band->current_cell->next;
      return;
    }
    // daca pozitia degetului NU este pe ultimul caracter din lista
    // se insereaza caracterul din "param" la dreapta degetului
    ListNode* newNode = createNode(param);
    newNode->next = band->current_cell->next;
    newNode->prev = band->current_cell;
    band->current_cell->next->prev = newNode;
    band->current_cell->next = newNode;

    band->current_cell = newNode;
    band->current_cell->elem = param;
    return;
  }
  return;
}

void QUERY(Banda* band, char* operation, FILE* fout) {
  // se afiseaza caracterul din pozitia degetului
  if (strcmp(operation, "SHOW_CURRENT") == 0) {
    fprintf(fout, "%c\n", band->current_cell->elem);
    return;
  }
  // afisare continut banda
  ListNode* iter = band->list->first->next;
  if (strcmp(operation, "SHOW") == 0) {
    // se afiseaza caracterele pana la pozitia degetului
    while (iter != band->current_cell) {
      fprintf(fout, "%c", iter->elem);
      iter = iter->next;
    }
    // se afiseaza caracterul de pe pozitia degetului
    fprintf(fout, "|%c|", iter->elem);
    // se afiseaza caracterele de dupa pozitia degetului
    if (iter->next) {
      iter = iter->next;
      while (iter) {
        fprintf(fout, "%c", iter->elem);
        iter = iter->next;
      }
    }
    fprintf(fout, "\n");
  }
}

void UNDO(Banda* band, Stack* UNDO_Stack, Stack* REDO_Stack) {
  // in "temp" se salveaza pointerul din varful stivei pentru UNDO
  ListNode* temp = UNDO_Stack->head->elem;
  // se extrage pointerul din varful stivei pentru UNDO
  pop(UNDO_Stack);
  // se adauga pointerul pozitiei curente a degetului in stiva pentru REDO
  push(REDO_Stack, band->current_cell);
  // degetul va indica spre pointerul extras din stiva pentru UNDO
  band->current_cell = temp;
  return;
}

void REDO(Banda* band, Stack* UNDO_Stack, Stack* REDO_Stack) {
  // in "temp" se salveaza pointerul din varful stivei pentru REDO
  ListNode* temp = REDO_Stack->head->elem;
  // se extrage pointerul din varful stivei pentru REDO
  pop(REDO_Stack);
  // se adauga pointerul pozitiei curente a degetului in stiva pentru UNDO
  push(UNDO_Stack, band->current_cell);
  // degetul va indica spre pointerul extras din stiva pentru REDO
  band->current_cell = temp;
  return;
}

void EXECUTE(Banda* band, Queue* q, Stack* UNDO_Stack, Stack* REDO_Stack,
             FILE* fout) {
  char* operation = NULL;
  unsigned char param = '-';

  /* alocare si initializare operation (unde se pastreaza operatia de pe
   * fiecare linie) */

  operation = q->front->operation;
  param = q->front->param;

  // daca "operation" face parte din operatiile valabile pentru tipul UPDATE,
  // atunci aceasta se executa
  // daca nu => se returneaza din functie fara sa fi efectuat vreo modificare
  UPDATE(band, operation, param, UNDO_Stack, REDO_Stack, fout);

  return;
}
