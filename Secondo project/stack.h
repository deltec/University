/*desc: Questo file contiene funzioni che gestiscono uno stack statico
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					  50/747
Gruppo 27
N.b. Dettaglio implementativo "lo stack viene implementato con un array statico dove nella testa 
c'e' un puntatore ad un intero che indica l'indice d'array dove si trova la testa"
*/

/*Valore massimo che puo raggiungere lo stack*/
#define MAXSTACK 100

/*Quaesta funzione crea e inizializza uno stack ritorna un array di puntatori a void*/
void **CreaStack();

/*Questa funzione ritrona 1 se lo stack e' vuoto altrimenti zero*/
int IsEmpty(void ** Stack);

/*Questa funzione ritrona 1 se lo stack e' pieno altrimenti zero*/
int IsFull(void ** Stack);

/*Funzione che inserisce un elemento sulla testa dello stack ritorna 1 se l'esito e' positivo 0 altrimenti. 
INPUT puntatore allo Stack, puntatore all'emento da inserire*/
int Push(void ** Stack,void * Elem);

/*Funzione che estrae l'elemento di testa sullo stack ritorna l'indirizzo se e' positivo NULL altrimenti. 
INPUT puntatore allo Stack*/
void* Pop(void ** Stack);

/*Funzione che estrae senza eliminare l'elemento di testa sullo stack ritorna l'indirizzo se e' positivo NULL altrimenti. 
INPUT puntatore allo Stack*/
void * ViewHead(void ** Stack);
