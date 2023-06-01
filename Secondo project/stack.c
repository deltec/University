#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
/*desc: Questo file contiene funzioni che gestiscono uno stack statico
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					
N.b. Dettaglio implementativo "lo stack viene implementato con un array statico dove nella testa 
c'e' un puntatore ad un intero che indica l'indice d'array dove si trova la testa"
*/

/*Quaesta funzione crea e inizializza uno stack ritorna un array di puntatori a void*/
void ** CreaStack()
{
   int *Testa;
   void **Stack;
   Stack=(void**)calloc(MAXSTACK+1,sizeof(void*)); /*Alloco lo stack di uno in piu xche nella posizione 0 c'e' l'indice della testa dello stack*/
   Testa=(int*)malloc(sizeof(int)) ;
   *Testa=0;  /*inizializzo la testa dello stack*/
   Stack[0]=(void*)Testa; /*assegno la testa dello stack nella prima posizione*/
   return Stack;
}

/*Questa funzione ritrona 1 se lo stack e' vuoto altrimenti zero*/
int IsEmpty(void ** Stack)
{
   int Risultato=0,*Testa;
   Testa=(int*)Stack[0];
   if(*Testa==0) /*Controllo se lo Stack e vuoto*/
   {
      Risultato=1;	
   }
   return Risultato;
}

/*Questa funzione ritrona 1 se lo stack e' pieno altrimenti zero*/
int IsFull(void ** Stack)
{
   int Risultato=0,*Testa;
   Testa=(int*)Stack[0];
   if((*Testa)==MAXSTACK) /*Controllo se lo Stack e pieno*/
   {
      Risultato=1;	
   }
   return Risultato;
}

/*Funzione che inserisce un elemento sulla testa dello stack ritorna 1 se l'esito e' positivo 0 altrimenti. 
INPUT puntatore allo Stack, puntatore all'emento da inserire*/
int Push(void ** Stack,void * Elem)
{
   int Esito=0,*Testa;
   if( !IsFull(Stack) )
   {
      Testa=(int*)Stack[0];
      (*Testa)++;            /*Incremento la testa dello stack*/
      Stack[*Testa]=Elem;   /*Assegno il puntatore dell'elemento alla nuova testa*/
      Esito=1;
   }
   return Esito;
}

/*Funzione che estrae l'elemento di testa sullo stack ritorna l'indirizzo se e' positivo NULL altrimenti. 
INPUT puntatore allo Stack*/
void * Pop(void ** Stack)
{
   void* Elem=NULL;
   int *Testa;
   if( !IsEmpty(Stack) )
   {
      Testa=(int*)Stack[0];
      Elem=Stack[*Testa];      /*Assegno il puntatore dell'elemento alla nuova testa*/
      (*Testa)--;              /*Decremento la testa dello stack*/
   }
   return Elem;
}

/*Funzione che estrae senza eliminare l'elemento di testa sullo stack ritorna l'indirizzo se e' positivo NULL altrimenti. 
INPUT puntatore allo Stack*/
void * ViewHead(void ** Stack)
{
   void* Elem=NULL;
   int *Testa;
   if( !IsEmpty(Stack) )
   {
      Testa=(int*)Stack[0];
      Elem=Stack[*Testa];      /*Assegno il puntatore dell'elemento alla nuova testa*/
   }
   return Elem;
}

