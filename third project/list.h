/*desc: Questo file contiene funzioni che gestiscono una lista dinamica
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747
Gruppo 27*/

/*Struttura dati che implementa un oggetto di una lista, Elem rappresenta il puntatore ad una area di memoria di un elemento
Next rappresenta l'oggetto successivo, Prev rappresenta l'oggeto precedente*/
typedef struct List {
void *Elem;
struct List *Next;
} LIST;

/*Questa funzione iserisce un nuovo oggetto nella testa della lista e ritorna la nuova testa
se la lista e' vuota allora ritorna il singolo oggetto
INPUT: Lista in questione, Elem rappresenta il puntatore all'area di memoria dell'elemento
OUTPUT : nuova testa della lista*/
LIST *InsElem(LIST *,void *);

/*Questa funzione alloca e inizializza una struttura LIST
INPUT:   Inidirizzo dell'elemento
OUTPUT:  elemento allocato */
LIST *AllocaElem(void *);


/*Questa funzione iserisce un novo oggetto nella lista in ordine e ritorna la nuova testa
se la lista e' NULLA allora ritorna il singolo oggetto
INPUT : Testa della lista, Elem elemento da inserire , puntatore alla funzione di ordinamento*/
LIST *InsElemByOrder(LIST *,void *,int (*Confronto) (void *,void *));

/*Funzione di Confronto, Confronta gli elementi dell'indirizzo dgli elementi della lista ritorna <0 se a<b, 0 se a==b , >0 se a>b In questo caso la funzione confronta 2 stringhe*/
int conf(void * ,void * );

/*Questa funzione dealloca ricorsivamente una lista 
INPUT Testa della Lista e funzione di deallocazione Elemento*/
void Dealloca_Ric(LIST *Lista,void (*Dealloca_Elem) (void *));

/*Funzionme ricorsiva che stampa a video dei valore della lista
INPUT: Lista da stampare, funzione che stampi l'elemento
Print prende in input l'elemento della lista*/
void Stampa_Ric(LIST *Lista,void (*Print) (void *));

/*Questa funzione fa il marge tra 2 liste senza aggiungere doppioni
alloca una nuova lista
INPUT: Lista 1 Lista2 funzione di confronto tra elementi di liste
OUTPUT: Lista compattata
n.b. le liste non devono essere deallocate*/
LIST *Merge(LIST *Lista1,LIST *Lista2,int (*Confronto) (void *,void *));

/*Questa funzione ritorna il campo info di una lista
INPUT: nodo di una lista
OUTPUT: putatore all'area di memoria del campo Elem (informazione della lista)*/
void * GetInfoList(LIST * Lista);
