/*desc: Questo file contiene funzioni che gestiscono un grafo
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747
Gruppo 27*/

#include "list.h"
#include "grafo.h"
#include "coda.h"
#include <stdio.h>
#include <stdlib.h>

/*Funzione che costruisce e inizializza a NULL un grafo rappresentato da liste di adicenza 
INPUT: quantita nodi del grafo da creare
OUTPUT: array dei nodi creati
N.B. dettaglio implementativo la struttura che contiene i nodi viene allocata di 10 elementi in piu rispetto Q_Nodi*/
LIST **Crea_Grafo(int Q_Nodi)
{
   int *Nodi,*Archi,*Blocchi; 
   LIST **List_Ad;
   List_Ad=(LIST**)calloc(Q_Nodi+1+10,sizeof(LIST*)); //Q_Nodi=nodi grafo,1 e'il nodo che contiene le informazioni del grafo,10 rappresenta i blocchi in piu del grafo
   Nodi=(int*)malloc(sizeof(int));
   *Nodi=Q_Nodi; //Assegno la quantita di nodi del grafo
   Archi=(int*)malloc(sizeof(int));
   *Archi=0; //Assegno la quantita di archi del grafo
   Blocchi=(int*)malloc(sizeof(int));
   *Blocchi=Q_Nodi+10;//Assegno la quantita di blocchi verticali dell'array
   List_Ad[0]=InsElem(NULL,(void*)Blocchi); //Inserisco nella lista
   List_Ad[0]=InsElem(List_Ad[0],(void*)Archi); //Inserisco nella lista
   List_Ad[0]=InsElem(List_Ad[0],(void*)Nodi); //Inserisco nella lista
   return List_Ad;
}

/*Funzione che ritorna il numero di nodi del grafo 
INPUT: Lista di adiacenza
OUTPUT: numero di nodi*/
int Get_Num_Nodi(LIST ** List_Ad)
{
   int *Nodi;
   Nodi=(int*)List_Ad[0]->Elem;
   return *Nodi; 
}

/*Funzione che ritorna il numero di Archi del grafo 
INPUT: Lista di adiacenza
OUTPUT: numero di archi*/
int Get_Num_Archi(LIST ** List_Ad)
{
   int *Archi;
   Archi=(int*)List_Ad[0]->Next->Elem;
   return *Archi; 
}

/*Funzione che ritorna il numero di blocchi dell'array allocati 
INPUT: Lista di adiacenza
OUTPUT: numero di blocchi*/
int Get_Num_Blocchi(LIST ** List_Ad)
{
   int *Blocchi;
   Blocchi=(int*)List_Ad[0]->Next->Next->Elem;
   return *Blocchi; 
}

/*Funzione che dealloca il grafo
INPUT: Lista di adiacenza
ATTENZIONE: dopo la chiamata alla funzione bisogna deallocare anche la variabile al doppio puntatore!!!!
*/
void Dealloca_Grafo(LIST ** List_Ad)
{
   int I,Q_Nodi;
   Q_Nodi=Get_Num_Nodi(List_Ad);
   for(I=0;I<=Q_Nodi;I++)
   {  
      Dealloca_Ric(List_Ad[I],Dealloca);
   }
}

/*Funzione di deallocazione elemento richiesto dalla funzione su implemetata
INPUT: Elemento da deallocare*/
void Dealloca(void*Elem)
{ 
   free(Elem);
}

/*Funzione che realloca di 10 nodi il grafo rispetto ai bocchi correnti
INPUT: Lista di adiacenza
OUTPUT: ritorna il grafo reallocato se tutto va a buon fine altrimente NULL*/
LIST ** Realloca_Grafo(LIST ** List_Ad)
{
   LIST ** New_List_Ad;
   int *Index;
   int Blocchi=Get_Num_Blocchi(List_Ad);
   New_List_Ad = (LIST**)realloc(List_Ad,(Blocchi+10) * sizeof(LIST*));
   if(New_List_Ad != NULL)
   {
      Index=New_List_Ad[0]->Next->Next->Elem;  // accedo alla lista dei blochi
      *Index=*Index+10;
   }
   return New_List_Ad;
}

/*Funzione che inserisce un arco tra il nodo a e il nodo b
INPUT: Lista di adiacenza,nodo a e nodo b
OUTPUT: Esito dell'inserimeto, 0 errore inseremto, 1 elemento gai inserito,2 se l'inserimento e avvenuto con successo*/
int Ins_Arco(LIST ** List_Ad,int A, int B)
{
   int Esito,*Archi,*Elem,Trovato=0;
   LIST * List;
   if(A>Get_Num_Nodi(List_Ad) || A<1 || B>Get_Num_Nodi(List_Ad) || B<1)
   {
      Esito=0;
   }
   else
   {
      List=List_Ad[A];
      while(List != NULL && !Trovato)  //Controllo se in nodo gia e' inserito
      {
         Elem=List->Elem;
         if(*Elem == B)
         {
            Trovato=1;
            Esito=1;
         }
         List=List->Next;
      }
      if(!Trovato)
      {
         Elem=(int*)malloc(sizeof(int));
         *Elem=B;
         List_Ad[A]=InsElem(List_Ad[A],(void*)Elem);
         Archi=List_Ad[0]->Next->Elem;
         *Archi=*Archi+1;
         Esito=2;
      }
   }
   return Esito; 
}

/*Funzione che inserisce un nouvo nodo nel grafo
INPUT: Lista di adiacenza
OUTPUT: 0 errore inseremto, altrimenti l'intero del nuovo nodo
N.B.: controllare se c'e' abbastanza spazio per inserire un nuovo nodo*/
int Ins_Nodo(LIST ** List_Ad)
{
   int Ritorno,*Nodi;
   if(Get_Num_Nodi(List_Ad)>=Get_Num_Blocchi(List_Ad))
   {
      Ritorno=0;
   }
   else
   {
      Nodi=List_Ad[0]->Elem;
      *Nodi=*Nodi+1;
      Ritorno=Get_Num_Nodi(List_Ad); 
      List_Ad[Ritorno]=NULL;
   }
   return Ritorno;
}

/*Funzione che elimina un arco A,B nel grafo
INPUT: Lista di adiacenza, Nodo A , Nodo B
OUTPUT: 0 errore Eliminazione,1 Arco inesistente ,2 Eliminazione effettuata con succecco*/
int Elim_Arco(LIST ** List_Ad,int A, int B)
{
   int Esito=1,*Archi,*Elem,Non_Trovato=1;
   LIST * List,*Prev=NULL,*Da_Eliminare=NULL;
   if(A>Get_Num_Nodi(List_Ad) || A<1 || B>Get_Num_Nodi(List_Ad) || B<1)
   {
      Esito=0;
   }
   else
   {
      List=List_Ad[A];
      Prev=NULL;
      while(List != NULL && Non_Trovato)  //Controllo se ho trovato il nodo
      {
         Elem=List->Elem;
         if(*Elem == B)  //Controllo se trovo il nodo cercato
         {
            Non_Trovato=0;
            Esito=2;
	    Da_Eliminare=List;
         }
         else           // Aggiorno il predecessore
         {
            if(Prev==NULL)
	    {
               Prev=List;
            }
            else
            {
               Prev=Prev->Next;
            }
         }
         List=List->Next;
      }
      if(!Non_Trovato)   // Devo effetturare la cancellazione nella lista
      {
         if(Prev == NULL)
         {
            List_Ad[A]=List;
            Dealloca(Da_Eliminare->Elem);
            free(Da_Eliminare);
         }
         else
         {
            Prev->Next=List;
            Dealloca(Da_Eliminare->Elem);
            free(Da_Eliminare);
         }	 
         Archi=List_Ad[0]->Next->Elem;
         *Archi=*Archi-1;
      }
   }
   return Esito; 
}

/*Funzione che elimina un Nodo nel grafo
INPUT: Lista di adiacenza, Nodo da eliminare
OUTPUT: 0 errore Eliminazione,1 Eliminazione effettuata con succecco*/
int Elim_Nodo(LIST ** List_Ad,int A)
{
   int Esito=1,*Nodi,Indice,I;
   LIST* Temp;
   if(A<1 && A>Get_Num_Nodi(List_Ad)) //Controllo se posso eliminare un nodo
   {
      Esito=0;
   }
   else
   {
      
      for (I=1;I<=Get_Num_Nodi(List_Ad);I++)
      {
         Temp=List_Ad[I];   
         while(Temp != NULL)
         {
            Nodi=Temp->Elem;
            if(*Nodi>A)
            {   
               *Nodi=*Nodi-1;
            }
            Temp=Temp->Next;
         }
      }
      Indice=1;
      while(Get_Num_Nodi(List_Ad)>=Indice)  // Elimino tutti gli archi verso A (che e' stato cancellato)
      {
         Elim_Arco(List_Ad,Indice,A);
         Elim_Arco(List_Ad,A,Indice);
         Indice++;
      }
      Indice=A;
      while(Get_Num_Nodi(List_Ad)>Indice)  //Ricompatto l'array
      {
         List_Ad[Indice]=List_Ad[Indice+1];
         Indice++;
      }
      List_Ad[Indice]=NULL;
      Nodi=List_Ad[0]->Elem;   //Aggiorno il numero di nodi
      *Nodi=*Nodi-1;
      Indice=1;
   }
   return Esito;
}

/*Funzione che elimina una coincidenza
INPUT: Lista di adiacenza, Nodo da eliminare
OUTPUT: 0 errore Eliminazione,1 Eliminazione effettuata con succecco*/
int Elim_Nodo_Coinc(void**Array_Coinc,int A)
{
   int Esito=1,*Nodi,Indice;
   if(A<1 && A>Get_Num_Nodi((LIST**)Array_Coinc)) //Controllo se posso eliminare un nodo
   {
      Esito=0;
   }
   else
   {
      Indice=A;
      while(Get_Num_Nodi((LIST**)Array_Coinc)>Indice)  //Ricompatto l'array
      {
         Array_Coinc[Indice]=Array_Coinc[Indice+1];
         Indice++;
      }
      Array_Coinc[Indice]=NULL;
      Nodi=((LIST**)Array_Coinc)[0]->Elem;
      *Nodi=*Nodi-1;
      Indice=1;
   }
   return Esito;
}

/*Funzione che Converte una lista di adiacenza in matrice di adicenza,mettendo ad 1 gli archi
INPUT: Lista di adiacenza
OUTPUT: Matrice di adiacenza
N.B. Il Grafo e' rappresentato come segue: arco(i,j) appartiene al grafo se e solo se Mat_Ad[i][j]=1
la matrice va da (0 a Q_Nodi-1) mentre i nodi nella lista di adiacenza e nella rappresentazione vanno da (1 a Q_Nodi)*/
int **Converti(LIST ** List_Ad)
{
   int ** Mat_Ad,I,J,*Nodo;
   LIST * List;
   Mat_Ad=(int**)calloc(Get_Num_Nodi(List_Ad),sizeof(int*));    //Alloco la matrice di adiacenza
   for(I=0;I<Get_Num_Nodi(List_Ad);I++)
   {
      Mat_Ad[I]=(int*)calloc(Get_Num_Nodi(List_Ad),sizeof(int));
   }
   for(I=0;I<Get_Num_Nodi(List_Ad);I++)
   {
         for(J=0;J<Get_Num_Nodi(List_Ad);J++)
         {
            Mat_Ad[I][J]=0;      //Inizializzo la matrice di adiacenza
         }
   }
   for(I=1;I<=Get_Num_Nodi(List_Ad);I++)
   {
      List=List_Ad[I];
      while(List != NULL)
      {
         Nodo=List->Elem;
         Mat_Ad[I-1][(*Nodo)-1]=1;
         List=List->Next;
      }
   }
   return Mat_Ad;
}

/*Funzione che stampa a video una grafo rappresentato da una matrice di adiacenza
INPUT: Matrice di adiacenza,Numero di nodi
OUTPUT: Stampa a video
N.B. Il Grafo e' rappresentato come segue: arco(i,j) appartiene al grafo se e solo se Mat_Ad[i][j]=1;
la matrice va da (0 a Q_Nodi-1) mentre i nodi nella lista di adiacenza e nella rappresentazione vanno da (1 a Q_Nodi)*/
void Stampa_Grafo(int ** Mat_Ad,int Q_Nodi)
{
   int I,J;
   for(I=0;I<Q_Nodi;I++)
   {
      printf("\t%d",I+1);
   }
   printf("\n\n");
   for(I=0;I<Q_Nodi;I++)
   {
      printf("%d\t",I+1);
         for(J=0;J<Q_Nodi;J++)
         {
            printf("%d\t",Mat_Ad[I][J]);
         }
         printf("\n");
   }
}

/*Funzione che alloca l'array delle coincidenze
INPUT: Lista di adiacenza
OUTPUT: Array delle coincidenze
N.B. Il primo elemento contiene gli stessi elementi della matrice di adiacenze cioe le info relative al grafo,
     e la dimensione dell'array delle coincidenze ha la stessa dimensione della lista di adiacenza in tutte le sue parti*/
void** Crea_Array_Coinc(LIST ** List_Ad)
{
   void** Array_Coinc;
   int *Nodi,*Blocchi,*Archi;
   Array_Coinc=(void**)calloc(Get_Num_Blocchi(List_Ad),sizeof(void*));
   Nodi=(int*)malloc(sizeof(int));
   *Nodi=Get_Num_Nodi(List_Ad); //Assegno la quantita di nodi del grafo
   Archi=(int*)malloc(sizeof(int));
   *Archi=Get_Num_Archi(List_Ad); //Assegno la quantita di archi del grafo
   Blocchi=(int*)malloc(sizeof(int));
   *Blocchi=Get_Num_Blocchi(List_Ad);//Assegno la quantita di blocchi verticali dell'array
   Array_Coinc[0]=InsElem(NULL,(void*)Blocchi); //Inserisco nella lista
   Array_Coinc[0]=InsElem(Array_Coinc[0],(void*)Archi); //Inserisco nella lista
   Array_Coinc[0]=InsElem(Array_Coinc[0],(void*)Nodi); //Inserisco nella lista
   return Array_Coinc;
}

/*Funzione che setta l'array delle coincidenze. Associa un numero ad un indirizzo
INPUT: Array delle coincidenze allocato,numero di nodo, Indirizzo da assegnare
OUTPUT: 1 inserimento corretto,0 inserimento non corretto*/
int Set_Coinc(void** Array_Coinc,int Num_Nodo, void * Nodo)
{
   int Esito=0,*Index;
   if(Num_Nodo>=1)
   { 
      Array_Coinc[Num_Nodo]=Nodo;
      Index=((LIST *)Array_Coinc[0])->Elem;
      *Index=*Index+1;
      Esito=1;
   }
   return Esito;
}

/*Funzione che prende un indirizzo dall'array delle coincidenze.
INPUT: Array delle coincidenze allocato,numero di nodo, Indirizzo da assegnare
OUTPUT: Ritorna l'indirizzo altrimenti NULL*/
void* Get_Coinc(void** Array_Coinc,int Num_Nodo)
{
   void* Esito=NULL;
   if(Num_Nodo<=Get_Num_Nodi((LIST**)Array_Coinc) && Num_Nodo>1)
   {
      Esito=Array_Coinc[Num_Nodo];
   }
   return Esito;
}

/*Funzione che riadegua il numero di bocchi nel caso fosse stato riallocata la lista di adiacenza
INPUT: Lista delle coincidenze,Lista di adiacenza
OUTPUT: ritorna il nuovo indirizzo se tutto va a buon fine altrimente se non c'e' bisogno di riallocare NULL*/
void** Adegua_Array_Coinc(void** Array_Coinc,LIST ** List_Ad)
{
   void** New_Array_Coinc=NULL;
   int *Index;
   int Blocchi_Ad=Get_Num_Blocchi(List_Ad);
   int Blocchi_Coinc=Get_Num_Blocchi((LIST**)Array_Coinc);
   if(Blocchi_Ad != Blocchi_Coinc)
   {
      New_Array_Coinc = (void**)realloc(Array_Coinc,(Blocchi_Ad) * sizeof(void*));
      if(Array_Coinc != NULL)
      {
         Index=((LIST*)New_Array_Coinc[0])->Next->Next->Elem;  // accedo alla lista dei blochi
         *Index=*Index+10;
      }
   }
   return New_Array_Coinc;
}
/*Funzione che ritorna un grafo trasposto
INPUT:Grafo lista di adiacenza
OUTPUT: Grafo trasposto*/
LIST **Trasponi_Grafo(LIST **Grafo)
{
   int I,*A;
   LIST **Trasp_Grafo,*Temp;
   Trasp_Grafo=Crea_Grafo(Get_Num_Nodi(Grafo));
   for(I=1;I<=Get_Num_Nodi(Grafo);I++)
   {
      Temp=Grafo[I];
      while(Temp != NULL)
      {
         A=Temp->Elem;
         Ins_Arco(Trasp_Grafo,*A,I);
         Temp=Temp->Next;
      }
   }
   return Trasp_Grafo;
}

/*questa funzione implementa una visita in ampiezza di un grafo
INPUT: Grafo , Nodo sorgente da cui iniziare la BFS
OUTPUT:ritorna l'array dei predecessori*/
int* Bfs(LIST**Grafo, int Sorgente) 
{ 
   int I,*W,*V,*Colore,*Pred,*Elem,Nodi;
   LIST * Coda=NULL,*Temp,*Next;
   Nodi=Get_Num_Nodi(Grafo);
   Colore=(int*)calloc(Nodi,sizeof(int));  //Allocati e inizializzati
   for(I=0;I<Nodi;I++)
   {
      Colore[I]=BIANCO;
   }
   Pred=(int*)calloc(Nodi,sizeof(int));   // Allocati e inizializzati
   for(I=0;I<Nodi;I++)
   {
      Pred[I]=-1;
   }
   Elem=(int*)malloc(sizeof(int));
 
   *Elem=Sorgente;                     //inizializzazione
   Colore[*Elem-1] = GRIGIO;              /*Coloro il nodo grigio*/
   Pred[*Elem-1] = -1;                 //inizializzo il predecessore
   Coda=Push_Coda(Coda,(void*)Elem);      //accodo
   while(!IsEmpty_Coda(Coda)) 
   {
      if(!Pop_Coda(Coda,&Temp))               /*Decoda v*/
      {
         Coda=NULL;
      }
      V=Temp->Elem;                  //prendo l'elemento V
      Next=Grafo[*V];        /*prendo il primo nodo adiacente di V*/ 
      while(Next != NULL)              /*Cicla i nodi adiacenti*/
      { 
         W=Next->Elem;
         if(Colore[*W-1] == BIANCO) 
         {               /*visita il nodo*/
            Elem=(int*)malloc(sizeof(int));
            *Elem=*W;
            Coda=Push_Coda(Coda,(void*)Elem);             /*Accora il nodo w*/
            Colore[*W-1] = GRIGIO;        /*Coloro di gragio perche entra in coda*/
            Pred[*W-1]=*V-1;     //assegno il predecessore
         }
         Next=Next->Next;        /*prende il successiova nodo adiacente*/
      }
      Colore[*V-1] = NERO;
   }
   return Pred;
}

/*Questa funzione controlla se esite l'arco (A,B) esiste nel grafo rappresentato come liste di adiacenza
INPUT: Grafo,nodo a , nodo b
OUTPUT:ritorna 0 se non esite , altrimenti 1*/
int Esiste(LIST**Grafo,int A,int B)
{
   LIST* Temp;
   int *Nodo,Ritorno=0;
   if(A != 0 && B != 0)
   {
      Temp=Grafo[A];
      while(Temp != NULL && !Ritorno)
      {
         Nodo=Temp->Elem;
         if(*Nodo == B)
         {
            Ritorno=1; 
         }
         Temp=Temp->Next;
      }
   }
   return Ritorno;
}

/*Questa funzione stampa i nomi dell'array di adicenza con i relativi nueri nel grafo
INPUT: Array delle coincidenze
OUTPUT: Stdout 
*/
void Stampa_Array_Coinc(void** Array_Coinc)
{
   LIST ** Temp=(LIST**)Array_Coinc;
   char *Str;
   int Nodi=Get_Num_Nodi(Temp),I;
   for(I=1;I<=Nodi;I++)
   {
      Str=(char*)Array_Coinc[I];
      printf("%d=%s  ",I,Str);
   }
   printf("\n");
}

