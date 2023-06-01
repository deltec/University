
/*desc: Questo file contiene funzioni di ordinamento
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/


/*Funzione di scambio tra PAROLE input: doppio puntatore ad un void e a e b rappresentano i due indici*/
void swap(void ** ,int ,int );


/*Confronta gli interi di indici a,b della struttura PAROLA ritorna <0 se a<b, 0 se a==b , >0 se a>b*/
int conf(void ** ,int ,int );

/*Confronta le stinghe di indice a,b della struttura PAROLA ritorna <0 se a<b, 0 se a==b , >0 se a>b*/
int conf_2(void ** ,int ,int );


/*Funzione di ordinamento (Selection Sort)
INPUT : funzione di scambio tra due elementi, funzione di confronto,array , dimensione dell'array*/
void SelectionSort( void (*swap) (void **,int,int) , int (*conf) (void **,int,int) ,void ** , int );



/*Funzione di ordinamento (Buble Sort)
INPUT : funzione di scambio tra due elementi, funzione di confronto,array , dimensione dell'array*/
void BubleSort( void (*swap) (void **,int,int) , int (*conf) (void **,int,int) ,void **, int );


/*Funzione di ordinamento ricorsiva (Quick sort)
INPUT : funzione di scambio tra due elementi, funzione di confronto,array , dimensione dell'array*/
void QuickSort(void (*swap) (void **,int,int) , int (*conf) (void **,int,int),void **, int , int); 
