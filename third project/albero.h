/*desc: Questo file contiene funzioni che gestiscono alberi binari ed ennari
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739				      50/747	
Gruppo 27*/

/*Struttura dati che implementa un nodo di un albero, Elem rappresenta il 
puntatore ad una area di memoria di un elemento
QuantNodi rappresenta il numero di nodi figli, Testa rappresenta la lista dei 
figli di NODO*/
typedef struct Nodo {
void *Elem;   /*Campo informazione*/
int QuantNodi;   /*Numero di figli*/
struct List *Testa;     /*Lista dei figli*/
} NODO;

/* questa funzione crea un nodo di un albero
INPUT: Elem � il puntatore all'area di memoria dell'elemento
OUTPUT: Ritorna il nodo creato */
NODO *CreaNodo (void *Elem);


/* questa funzione inserisce un nodo figlio al nodo padre
INPUT: Nodo padre, elemento da inserire */
NODO* InsNodo (NODO* Padre, void* Elem);


/*questa funzione inserisce un nodo in un albero binario
INPUT: Padre rappresenta il nodo padre, elem rappresenta il puntatore dell'elemento
OUTPUT: Ritorna 0 se il figlio non � stato creato perche' non rispetta le regole 
        di albero binario, ritorna 1 invece se il figlio � stato inserito */
int InsNodoBin (NODO* Padre, void* Elem);

/*questa funzione inserisce un nodo in un albero ennario
INPUT: Padre rappresenta il nodo padre, elem rappresenta il puntatore dell'elemento
OUTPUT: Ritorna 0 se il figlio non � stato creato, ritorna 1 invece se il 
figlio � stato inserito */
NODO *InsNodoEnn (NODO* Padre, void* Elem);

/* questa funzione crea la radice di un albero
INPUT: Elem rappresenta l'elemento da inserire
OUTPUT: ritorna la radice dell'albero */
NODO*CreaAlbero (void* Elem);

/* questa funzione ritorna il campo informazione del nodo
INPUT: Nodo dell'albero
OUTPUT: ritorna il puntatore all'informazione */
void *GetInfo(NODO* Nodo);

/*Ritorna la lista dei figli
INPUT: Padre rappresenta il padre dei figli
OUTPUT: Ritorna la lista dei figli del padre*/
LIST *GetFigli(NODO *Padre);

/*Questa funzione costruisce un albero binario a partire da una lista.L'albero viene costruito secondo il seguente protocollo
il padre di ogni figlio e' una etichetta fittizia,se la lista presa in input e nulla allora il valore di ritorno e' nullo,
se la lista contiene un solo elemento allora la radice e' proprio il nodo contenuto nella lista.
INPUT: Lista che nel campo informazione=Elem contiene un nodo di un albero, puntatore all'etichetta
OUTPUT: Radice dell'albero costruito
Attenzione il contenuto di Etichetta non deve essere una varibile locale di qualche funzine
ma deve stare o nello HEAP o nella memoria STATICA*/
NODO *ListToAlberoBin(LIST * Nodi,void *Etichetta);

/*Questa funzione trasforma un albero ennario in albero binario con il seguente protocollo: se esistono piu di 2
nodi fratelli allora vinene creato un nodo fittizio X il quale significa che il il padre del figlio di X e' il padre di X
ovviamente procedendo ricorsivamente verso l'alto finche non si trova una etichetta diversa da X
INPUT: radice dell'albero da convertire,Etichetta fittizia X
OUTPUT: albero binario*/
NODO *EnnarioToBinario(NODO *Albero,void* Etichetta);

