/*desc: Questo file contiene funzioni che gestiscono una lista dinamica
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739				      50/747	
Gruppo 27*/
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*Questa funzione inserisce un nuovo nodo prima dell'oggetto Nodo, Ritorna la testa.
INPUT se Nodo e' NULL Ritorna il Nodo*/
LIST *InsElem(LIST *Nodo,void *Elem)
{
   LIST *Temp;
   Temp=AllocaElem(Elem);
   if(Nodo != NULL) /*Verifico se la lista e vuota*/
   {
      Temp->Next=Nodo;
   }
   return Temp;
}

/*Questa funzione alloca e inizializza una struttura LIST
INPUT:   Inidirizzo dell'elemento
OUTPUT:  puntatore all'elemento allocato */
LIST *AllocaElem(void *Elem)
{
   LIST *Lista;
   Lista=(LIST*)malloc(sizeof(LIST));
   Lista->Elem=Elem;   /*Inizializzo l'elemento*/
   Lista->Next=NULL;  /*Inizializzo la lista con NULL*/
   return Lista;
}

/*Questa funzione iserisce un novo oggetto nella lista in ordine e ritorna la nuova testa
se la lista e' NULLA allora ritorna il singolo oggetto
INPUT : Testa della lista, Elem elemento da inserire , puntatore alla funzione di ordinamento*/
/*Funzione di Confronto, Confronta il contenuto degli indirizzi passatogli ritorna <0 se a<b, 0 se a==b , >0 se a>b*/
LIST *InsElemByOrder(LIST *Lista,void *Elem,int (*Confronto) (void *,void *))
{
   int Inserito=0;
   LIST *Temp,*Corrente,*Precedente,*NewTesta;
   Corrente=Lista;
   Precedente=NULL;
   while(Corrente != NULL && Inserito == 0)
   {/*Confronto se l'oggetto della lista in cui mi trovo e' maggiore dell'oggetto da inserire*/
      if (Confronto(Corrente->Elem,Elem) > 0) 
      { 
         if(Precedente==NULL)/*Precedente e' nullo*/
         {
            NewTesta=InsElem(NULL,(void*)Elem); /*Iserisco l'oggetto prima di corrente*/
            NewTesta->Next=Corrente;
            Inserito=1;
         }
         else
         {
            Temp=InsElem(NULL,(void*)Elem);
            Precedente->Next=Temp;  /*Precedente e' non nullo*/
            Temp->Next=Corrente;
            Inserito=1;
            NewTesta=Lista;
         }
      }/*Aggiornamento delle variabili*/
      Precedente=Corrente;
      Corrente=Corrente->Next;
   }
   if(!Inserito) /*se l'oggetto non e' stato inserito deve essere inserito in coda o perche e' vuota!!*/
   {  
      if(Precedente==NULL) /*Controllo se la lista e' vuota */
      {
         NewTesta=InsElem(NULL,(void*)Elem); /*Iserisco l'oggetto in testa*/
      }
      else
      {
         Temp=InsElem(NULL,(void*)Elem);
         Precedente->Next=Temp; /*Inserisco in coda*/
         NewTesta=Lista;
      }
   }
   return NewTesta;
}

/*Questa funzione dealloca ricorsivamente una lista 
INPUT Testa della Lista e funzione di deallocazione Elemento 
se il secondo parametro e' nullo allora viene deallocata solo la lista*/
void Dealloca_Ric(LIST *Lista,void (*Dealloca_Elem) (void *))
{
   if(Lista != NULL)
   {
      Dealloca_Ric(Lista->Next,Dealloca_Elem);/*Chiamata ricorsiva al next*/
      if(Dealloca_Elem != NULL) /* nel caso la funzione fiosse NULL*/
      {
      Dealloca_Elem(Lista->Elem);/*Deallocazione dell'elemento puntato nel nodo*/
      }
      free(Lista);
   }
   return;
}

/*Funzione di Confronto, Confronta gli elementi dell'indirizzo dgli elementi della lista ritorna <0 se a<b, 0 se a==b , >0 se a>b In questo caso la funzione confronta 2 stringhe*/
int conf(void * a,void * b)
{
   int ValRit;
   ValRit=strcmp((char*)a,(char*)b);
   return ValRit;
}

/*Funzionme ricorsiva che stampa a video dei valore della lista
INPUT: Lista da stampare, funzione che stampi l'elemento
Print prende in input l'elemento della lista*/
void Stampa_Ric(LIST *Lista,void (*Print) (void *))
{
   if(Lista != NULL)
   {
      Print(Lista->Elem);
      Stampa_Ric(Lista->Next,Print);
   }
}

/*Questa funzione fa il marge tra 2 liste senza aggiungere doppioni
alloca una nuova lista
INPUT: Lista 1 Lista2 funzione di confronto tra elementi di liste
OUTPUT: Lista compattata
n.b. le liste non devono essere deallocate*/
LIST *Merge(LIST *Lista1,LIST *Lista2,int (*Confronto) (void *,void *))
{
   LIST *Temp1=Lista1,*Temp2=Lista2,*NewLista=NULL;
   while(Temp1 != NULL && Temp2 != NULL)
   {
      if(Confronto((void*)Temp1->Elem,(void*)Temp2->Elem) < 0)  /*caso Temp1 < Temp2*/
      {
         NewLista=InsElemByOrder(NewLista,(void*)Temp1->Elem,Confronto);
         Temp1=Temp1->Next;
      }
      else if(Confronto((void*)Temp1->Elem,(void*)Temp2->Elem) > 0) /*caso Temp1 > Temp2*/
      {
         NewLista=InsElemByOrder(NewLista,(void*)Temp2->Elem,Confronto);
         Temp2=Temp2->Next;
      }
      else
      {
         Temp1=Temp1->Next;  /*caso Temp1 = Temp2*/
      }
   }
   while(Temp1 != NULL )  /*Copia restanti elementi*/
   {
      if(Confronto((void*)NewLista->Elem,(void*)Temp1->Elem) != 0)  /*Inserisco solo se non c'e' gia*/
      {
         NewLista=InsElemByOrder(NewLista,(void*)Temp1->Elem,Confronto);
      }
      Temp1=Temp1->Next;
   }
   while(Temp2 != NULL )  /*Copia restanti elementi*/
   {
      if(Confronto((void*)NewLista->Elem,(void*)Temp2->Elem) != 0 )  /*Inserisco solo se non c'e' gia*/
      {
         NewLista=InsElemByOrder(NewLista,(void*)Temp2->Elem,Confronto);
      }
      Temp2=Temp2->Next;
   }
   return NewLista;
}

/*Questa funzione ritorna il campo info di una lista
INPUT: nodo di una lista
OUTPUT: putatore all'area di memoria del campo Elem (informazione della lista)*/
void * GetInfoList(LIST * Lista)
{
   return Lista->Elem;
}

