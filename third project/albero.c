/*desc: Questo file contiene funzioni che gestiscono alberi binari ed ennari
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739				      50/747	
Gruppo 27*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "albero.h"


/* questa funzione crea un nodo di un albero
INPUT: Elem � il puntatore all'area di memoria Informazione
OUTPUT: Ritorna il puntatore al nodo allocato */
NODO *CreaNodo (void *Elem)
{
   NODO*Temp;
   Temp = (NODO*)malloc(sizeof(NODO));
   Temp->Elem=Elem;
   Temp->QuantNodi=0;   /*inizializzo il numero di figli */
   Temp->Testa=NULL;
   return Temp;
}

/* questa funzione inserisce un nodo figlio al nodo padre allocandolo e ritornando il puntatore al figlio allocato
INPUT: Nodo padre, elemento da inserire 
OUTPUT: Ritorna il foglio allocato*/
NODO *InsNodo (NODO* Padre, void* Elem)
{
   NODO* Temp;
   Temp=CreaNodo(Elem);
   Padre->QuantNodi++; /* incremento del numero dei figli */
   Padre->Testa=InsElem(Padre->Testa,(void *)Temp); /*inserimento nella lista*/
   return Temp;
}

/*questa funzione inserisce un nodo in un albero binario (non viene distinto figlio sinistro da figlio destro)
INPUT: Padre rappresenta il nodo padre, elem rappresenta il puntatore dell'elemento
OUTPUT: Ritorna 0 se il figlio non � stato creato perche' non rispetta le regole 
        di albero binario, ritorna 1 invece se il figlio � stato inserito */
int InsNodoBin (NODO* Padre, void* Elem)
{
   int Ritorno=0;
   if (Padre!=NULL)
   {
      if (Padre->QuantNodi<2)
      {
         InsNodo (Padre, Elem);
         Ritorno=1;
      }
   }
   return Ritorno;
}

/*questa funzione inserisce un nodo in un albero ennario
INPUT: Padre rappresenta il nodo padre, elem rappresenta il puntatore dell'elemento
OUTPUT: Ritorna 0 se il figlio non � stato creato, ritorna 1 invece se il 
figlio � stato inserito */
NODO *InsNodoEnn (NODO* Padre, void* Elem)
{
   NODO *Temp=NULL;
   if (Padre!=NULL)
   {
      Temp=InsNodo (Padre, Elem);
   }
   return Temp;
}


/* questa funzione crea la radice di un albero
INPUT: Elem rappresenta l'elemento da inserire
OUTPUT: ritorna la radice dell'albero */
NODO*CreaAlbero (void* Elem)
{
   NODO*Temp;
   Temp=CreaNodo (Elem);
   return Temp;
}

/*Ritorna la lista dei figli
INPUT: Padre rappresenta il padre dei figli
OUTPUT: Ritorna la lista dei figli del padre*/
LIST *GetFigli(NODO *Padre)
{
   return Padre->Testa;
}

/* questa funzione ritorna il campo informazione del nodo
INPUT: Nodo dell'albero
OUTPUT: ritorna il puntatore all'informazione */
void *GetInfo(NODO* Nodo)
{
   return Nodo->Elem;
}

/*Questa funzione costruisce un albero binario a partire da una lista.L'albero viene costruito secondo il seguente protocollo
il padre di ogni figlio ha una etichetta fittizia,se la lista presa in input e nulla allora il valore di ritorno e' nullo,
se la lista contiene un solo elemento allora la radice e' proprio il nodo contenuto nella lista.
INPUT: Lista che nel campo informazione=Elem contiene un nodo di un albero, puntatore all'etichetta
OUTPUT: Radice dell'albero costruito
Attenzione il contenuto di Etichetta non deve essere una varibile locale di qualche funzine
ma deve stare o nello HEAP o nella memoria STATICA*/
NODO *ListToAlberoBin(LIST * Nodi,void *Etichetta)
{
   NODO *NewNodo,*Radice=NULL;
   if(Nodi==NULL)  /*primo Caso*/
   {
      Radice=NULL;        
   }    
   else if(Nodi->Next==NULL)  /*Secondo caso*/
   {
      Radice=(NODO*)GetInfoList(Nodi);     
   }
   else if(Nodi->Next->Next==NULL)      /*Terzo caso (caso base della ricorsione)*/
   {
      NewNodo=CreaNodo(Etichetta);/*Creo il nodo ETichetta!!!*/
      NewNodo->Testa=InsElem(NULL,GetInfoList(Nodi->Next)); /*Assegmo il figli destro al nuovo nodo*/
      NewNodo->Testa=InsElem(NewNodo->Testa,GetInfoList(Nodi));  /*Assegno il figlio sinistro al nuovo nodo*/
      NewNodo->QuantNodi=2;  /*Assegmo la quantita di figli al nuovo nodo*/
      Radice=NewNodo;
   }
   else
   {
      NewNodo=CreaNodo(Etichetta);/*Creo il nodo ETichetta!!!*/
      NewNodo->Testa=InsElem(NULL,(void*)ListToAlberoBin(Nodi->Next,Etichetta)); /*Assegmo il figli destro al nuovo nodo e faccio la chiamata ricorsiva*/
      NewNodo->Testa=InsElem(NewNodo->Testa,GetInfoList(Nodi));   /*Assegno il figlio sinistro al nuovo nodo*/
      NewNodo->QuantNodi=2;  /*Assegmo la quantita di figli al nuovo nodo*/
      Radice=NewNodo;
   }
   return Radice;
}

/*Questa funzione trasforma un albero ennario in albero binario con il seguente protocollo: se esistono piu di 2
nodi fratelli allora vinene creato un nodo fittizio X il quale significa che il il padre del figlio di X e' il padre di X
ovviamente procedendo ricorsivamente verso l'alto finche non si trova una etichetta diversa da X
INPUT: radice dell'albero da convertire,Etichetta fittizia X
OUTPUT: albero binario*/
NODO *EnnarioToBinario(NODO *Albero,void* Etichetta)
{
   NODO *Radice=NULL,*AlbTemp;
   LIST *Figli,*Temp; 
   if(Albero != NULL)
   {
      Figli=GetFigli(Albero);
      Temp=Figli;
      while(Temp != NULL)
      {
         Radice=EnnarioToBinario((NODO*)GetInfoList(Temp),Etichetta);/*chiamata ricorsiva.Arrivo ricorsivamente fino le foglie!!!*/
         Temp=Temp->Next; /*accedo al figlio successivo di albero*/ 
      }
      if(Albero->QuantNodi > 2)
      {  
         AlbTemp=ListToAlberoBin(Figli,Etichetta); /*Questa funzione torna un albero ma, a me servono i suoi figli!!*/
         Albero->Testa=AlbTemp->Testa;  /*Assegno i figli dell'albero precedente all'albero della ricorsione corrente*/
         Albero->QuantNodi=2; /*Assegno il numero di figli correnti*/
         free((void*)AlbTemp); /*Dealloco la struttura dati fittizia!!!*/
         Dealloca_Ric(Figli,NULL);/*Dealloco solo la lista!!! che conteneva i figli del nodo corrente*/
      }
   }
   return Radice;    
}
