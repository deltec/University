/*desc: Questo file contiene funzioni che gestiscono una coda dinamica
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739				      50/747	
Gruppo 27*/
#include "list.h"
#include "coda.h"
#include<stdio.h>
#include<stdlib.h>

/*Questa funzione inserisce un nuovo nodo prima dell'oggetto Nodo, Ritorna la testa.
INPUT se Nodo e' NULL Ritorna il Nodo*/
LIST *Push_Coda(LIST *Nodo,void *Elem)
{
   LIST *Temp;
   Temp=AllocaElem(Elem);
   if(Nodo != NULL) /*Verifico se la lista e vuota*/
   {
      Temp->Next=Nodo;
   }
   return Temp;
}

/*Questa funzione Ritorna la coda della coda.
INPUT: coda
OUTPUT: coda*/
LIST *GetCoda(LIST * Coda)
{
   LIST *Temp=Coda ,*Ritorno=Coda;
   while(Temp != NULL)
   {
      Ritorno=Temp;  //Assegno la Coda;
      Temp=Temp->Next;  //Vado al successivo
   }
   return Ritorno;  // ritorno l'ultimo elemento
}

/*Questa funzione controlla se coda e' vuota.
INPUT: coda
OUTPUT: 0 se non e' vuota 1 se e' vuota*/
int IsEmpty_Coda(LIST *Coda)
{
   int Ritorno=0;
   if(Coda == NULL)
   {
      Ritorno=1;
   }
   return Ritorno;
}

/*Questa funzione estrae l'elemento dalla coda, e ritorna in Elem l'indirizzo dell'elemento estratto.
INPUT: coda,puntatore a lista non allocata
OUTPUT: ritnora 0 se la coda e' rimasta vuota, ritorna 1 se la coda e' ancora piena*/
int Pop_Coda(LIST*Coda,LIST**Elem)
{
   LIST*Prev,*Next,*Att;
   int Ritorno; 
   if(Coda==NULL)
   {
      Ritorno=0;
      *Elem=NULL;
   }
   else if(Coda->Next == NULL)
   {
      *Elem=Coda;
      Ritorno=0; 
   }
   else
   {
      Prev=Coda;
      Att=Coda->Next;
      Next=Coda->Next->Next;
      while(Next != NULL)
      {
         Prev=Prev->Next;
         Att=Att->Next;
         Next=Next->Next;
      }
      *Elem=Att;
      Prev->Next=NULL;
      Ritorno=1;
   }
   return Ritorno;
}
