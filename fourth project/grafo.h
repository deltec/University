/*desc: Questo file contiene funzioni che gestiscono un grafo
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747
Gruppo 27*/
/*Valori utilizzati per BFS*/
#define NERO 0
#define BIANCO 1
#define GRIGIO 2

/*Funzione che costruisce e inizializza a NULL un grafo rappresentato da liste di adicenza 
INPUT: quantita nodi del grafo da creare
OUTPUT: array di liste, dei nodi creati
N.B. dettaglio implementativo la struttura che contiene i nodi viene allocata di 10 elementi in piu rispetto Q_Nodi*/
LIST **Crea_Grafo(int);

/*Funzione che ritorna il numero di nodi del grafo 
INPUT: Lista di adiacenza
OUTPUT: numero di nodi*/
int Get_Num_Nodi(LIST **);

/*Funzione che ritorna il numero di Archi del grafo 
INPUT: Lista di adiacenza
OUTPUT: numero di archi*/
int Get_Num_Archi(LIST **);

/*Funzione che ritorna il numero di blocchi dell'array allocati 
INPUT: Lista di adiacenza
OUTPUT: numero di blocchi*/
int Get_Num_Blocchi(LIST **);

/*Funzione che dealloca il grafo
INPUT: Lista di adiacenza
ATTENZIONE: dopo la chiamata alla funzione bisogna deallocare anche la variabile al doppio puntatore!!!!
*/
void Dealloca_Grafo(LIST **);

/*Funzione di deallocazione elemento richiesto dalla funzione su implemetata
INPUT: Elemento da deallocare*/
void Dealloca(void*);

/*Funzione che realloca di 10 nodi il grafo rispetto ai bocchi correnti
INPUT: Lista di adiacenza
OUTPUT: ritorna il grafo reallocato se tutto va a buon fine altrimente NULL*/
LIST ** Realloca_Grafo(LIST **);

/*Funzione che inserisce un arco tra il nodo a e il nodo b
INPUT: Lista di adiacenza,nodo a e nodo b
OUTPUT: Esito dell'inserimeto, 0 errore inseremto, 1 elemento gai inserito,2 se l'inserimento e avvenuto con successo*/
int Ins_Arco(LIST ** ,int , int );

/*Funzione che inserisce un nouvo nodo nel grafo
INPUT: Lista di adiacenza
OUTPUT: 0 errore inseremto, altrimenti l'intero del nuovo nodo
N.B.: controllare se c'e' abbastanza spazio per inserire un nuovo nodo*/
int Ins_Nodo(LIST **);

/*Funzione che elimina un arco A,B nel grafo
INPUT: Lista di adiacenza, Nodo A , Nodo B
OUTPUT: 0 errore Eliminazione,1 Arco inesistente ,2 Eliminazione effettuata con succecco*/
int Elim_Arco(LIST **,int, int);

/*Funzione che elimina un Nodo nel grafo
INPUT: Lista di adiacenza, Nodo da eliminare
OUTPUT: 0 errore Eliminazione,1 Eliminazione effettuata con succecco*/
int Elim_Nodo(LIST **,int);

/*Funzione che elimina una coincidenza
INPUT: Lista di adiacenza, Nodo da eliminare
OUTPUT: 0 errore Eliminazione,1 Eliminazione effettuata con succecco*/
int Elim_Nodo_Coinc(void**,int );

/*Funzione che Converte una lista di adiacenza in matrice di adicenza,mettendo ad 1 gli archi
INPUT: Lista di adiacenza
OUTPUT: Matrice di adiacenza
N.B. Il Grafo e' rappresentato come segue: arco(i,j) appartiene al grafo se e solo se Mat_Ad[i][j]=1
la matrice va da (0 a Q_Nodi-1) mentre i nodi nella lista di adiacenza e nella rappresentazione vanno da (1 a Q_Nodi)*/
int **Converti(LIST **);

/*Funzione che stampa a video una grafo rappresentato da una matrice di adiacenza
INPUT: Matrice di adiacenza
OUTPUT: Stampa a video
N.B. Il Grafo e' rappresentato come segue: arco(i,j) appartiene al grafo se e solo se Mat_Ad[i][j]=1
la matrice va da (0 a Q_Nodi-1) mentre i nodi nella lista di adiacenza e nella rappresentazione vanno da (1 a Q_Nodi)*/
void Stampa_Grafo(int **,int);

/*Funzione che alloca l'array delle coincidenze
INPUT: Lista di adiacenza
OUTPUT: Array delle coincidenze
N.B. Il primo elemento contiene gli stessi elementi della matrice di adiacenze cioe le info relative al grafo,
     e la dimensione dell'array delle coincidenze ha la stessa dimensione della lista di adiacenza in tutte le sue parti*/
void** Crea_Array_Coinc(LIST **);

/*Funzione che setta l'array delle coincidenze. Associa un numero ad un indirizzo
INPUT: Array delle coincidenze allocato,numero di nodo, Indirizzo da assegnare
OUTPUT: 1 inserimento corretto,0 inserimento non corretto*/
int Set_Coinc(void**,int, void *);

/*Funzione che prende un indirizzo dall'array delle coincidenze.
INPUT: Array delle coincidenze allocato,numero di nodo, Indirizzo da assegnare
OUTPUT: Ritorna l'indirizzo altrimenti NULL*/
void* Get_Coinc(void**,int);

/*Funzione che riadegua il numero di bocchi nel caso fosse stato riallocata la lista di adiacenza
INPUT: Lista delle coincidenze,Lista di adiacenza
OUTPUT: ritorna il nuovo indirizzo se tutto va a buon fine altrimente se non c'e' bisogno di riallocare NULL*/
void** Adegua_Array_Coinc(void**,LIST **);

/*Funzione che ritorna un grafo trasposto
INPUT:Grafo lista di adiacenza
OUTPUT: Grafo trasposto*/
LIST **Trasponi_Grafo(LIST **Grafo);

/*questa funzione implementa una visita in ampiezza di un grafo
INPUT: Grafo , Nodo sorgente da cui iniziare la BFS
OUTPUT:ritorna l'array dei predecessori*/
int* Bfs(LIST**, int );

/*Questa funzione stampa i nomi dell'array di adicenza con i relativi nueri nel grafo
INPUT: Array delle coincidenze
OUTPUT: Stdout 
*/
void Stampa_Array_Coinc(void** );

/*Questa funzione controlla se esite l'arco (A,B) esiste nel grafo rappresentato come liste di adiacenza
INPUT: Grafo,nodo a , nodo b
OUTPUT:ritorna 0 se non esite , altrimenti 1*/
int Esiste(LIST**,int ,int );
