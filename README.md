# **Tema 1 - Banda magică**

>Banda magică conține elemente asupra cărora putem efectua anumite operații. Câteva din aceste operații sunt: mutarea degetului la stânga, la dreapta sau până la un element egal cu un anumit simbol, scrierea caracterelor și inserarea caracterelor pe bandă.

Pentru a efectua operațiile necesare, a fost creată o structură `"Banda"` ce conține o listă dublu-înlănțuită cu santinelă `"List *list"` și adresa celulei care indică degetul `"ListNode *current_cell"`. Funcțiile necesare efectuării tuturor operațiilor au fost scrise în fișierele de tip header `"DoubleLinkedList.h"`, `"Queue.h"`, `"Stack.h"` și `"Operations.h"`.

## **FUNCȚIA "MAIN"**

**1.** Se definesc 2 variabile de tip `FILE*` (fin, fout) pentru a accesa fișierele:
- `fin` corespunde fișierului de intrare tema1.in, din care se citește fiecare operație, care urmeaza a fi procesată și efectuată;
- `fout` corespunde fișierului de ieșire tema1.out, în care se scriu rezultatele efectuării operațiilor din fișierul "tema1.in";

**2.** Se creează și se inițializează lista `"Banda *band"`, stivele `"Stack *UNDO_Stack"` și `"Stack *REDO_Stack"` și coada `"Queue *q"`;

**3.** În `"nr_oper"` se citește numărul de operații din fișier;

**4.** Cu ajutorul unei bucle `"for"` și funcției `"getline"` se citește fiecare linie din fișierul "tema1.in", iar denumirea operației corespunzătoare liniei se stochează în vectorul "operation", care are memorie alocată dinamic pentru o operație de maxim 25 de caractere; În cazul în care operația are parametru, acesta se stochează în variabila `"param"` de tip unsigned char ("param" are valoarea '-' dacă operația curentă nu are parametru);

**5.** În cadrul buclei `"for"` are loc procesarea operației fiecărei linii. în funcție de aceasta, se intra pe unul din următoarele cazuri:
- operația dată este `EXECUTE`, caz în care se apelează funcția `"EXECUTE"` și operația se scoate din coadă;
- operația dată este `SHOW` sau `SHOW_CURRENT`, caz în care se apelează funcția `"QUERY"`;
- operația dată este `UNDO`, caz în care se apelează funcția `"UNDO"`;
- operația dată este `REDO`, caz în care se apelează funcția `"REDO"`;
- dacă operația nu este niciuna din cele de mai sus, atunci operația cu parametrul corespunzător se adaugă în coadă.

La finalul buclei, se eliberează memoria alocată dinamic pentru linia curentă și pentru operația corespunzătoare acesteia.

**6.** După ieșirea din bucla "for", are loc eliberarea memoriei alocate pentru listă, stive și coadă;

**7.** Se închid fișierele "fin" și "fout".

## **FUNCȚIILE PENTRU OPERAȚIILE DIN FIȘIERUL DE INTRARE**

### **"UPDATE"**:
Funcție care efectuează modificări ale poziției degetului și ale benzii în funcție de următoarele operații primite ca parametru:
- `MOVE_LEFT` - operație care mută degetul cu o poziție la stânga;
- `MOVE_RIGHT` - operație care mută degetul cu o poziție la dreapta;
- `MOVE_LEFT_CHAR` - operație care mută degetul spre stânga până când ajunge la caracterul primit ca parametru;
- `MOVE_RIGHT_CHAR` - operație care mută degetul spre dreapta până când ajunge la caracterul primit ca parametru;
- `WRITE` - operație care scrie caracterul primit ca parametru la poziția curentă;
- `INSERT_LEFT` - operație care inserează un nou caracter la stânga poziției curente;
- `INSERT_RIGHT` - operație care inserează un nou caracter la dreapta poziției curente.

### **"QUERY"**:
Funcție care afișează caractere în dependență de următoarele operații:
- `SHOW_CURRENT` - operație care afișează caracterul corespunzător poziției degetului;
- `SHOW` - operație care afișează toate caracterele benzii cu evidențierea caracterului corespunzător poziției degetului.

### **"UNDO"**:
Funcție care permite anularea ultimei operații aplicate.

### **"REDO"**:
Funcție care permite refacerea ultimei operații aplicate.

### **"EXECUTE"**:
Funcție care efectuează următoarele acțiuni:
- Extrage prima operație din coadă (care poate fi insoțită de parametru);
- Apelează funcția `"UPDATE"` cu operația și parametrul primit.

## **FUNCȚIILE LISTEI DUBLU-ÎNLĂNȚUITE**

- `"initList"` - inițializează o listă cu santinelă;
- `"createNode"` - creează un nou nod al listei;
- `"createList"` - creează o noua listă (goală);
- `"isEmpty"` - determină dacă lista este goală sau nu;
- `"length"` - determină lungimea listei;
- `"insertAt"` - introduce un nou element în listă la poziția dată ca parametru;
- `"destroyList"` - eliberează memoria ocupată de lista alocată dinamic;

## **FUNCȚIILE COZII**

- `"createQueue"` - creează o coadă;
- `"isQueueEmpty"` - determină dacă coada este goală sau nu;
- `"enqueue"` - introduce un nou element în coadă;
- `"dequeue"` - extrage un element din coadă;
- `"front"` - returneaza valoarea primului element din coadă;
- `"destroyQueue"` - eliberează memoria ocupată de coada alocată dinamic;

## **FUNCȚIILE STIVEI**

- `"createStack"` - creează o stivă;
- `"isStackEmpty"` - determină dacă stiva este goală sau nu;
- `"push"` - introduce un nou element în stivă;
- `"pop"` - extrage elementul din vârful stivei;
- `"destroyStack"` - eliberează memoria ocupată de stiva alocată dinamic.
