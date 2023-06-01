/*desc: Questo file contiene funzioni che gestiscono una coda dinamica
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739				      50/747	
Gruppo 27*/

/*Questa funzione inserisce un nuovo nodo prima dell'oggetto Nodo, Ritorna la testa.
INPUT se Nodo e' NULL Ritorna il Nodo*/
LIST *Push_Coda(LIST* ,void *);

/*Questa funzione Ritorna la coda della coda.
INPUT: coda
OUTPUT: coda*/
LIST *GetCoda(LIST *);

/*Questa funzione controlla se coda e' vuota.
INPUT: coda
OUTPUT: 0 se non e' vuota 1 se e' vuota*/
int IsEmpty_Coda(LIST *Coda);

/*Questa funzione estrae l'elemento dalla coda, e ritorna in Elem l'indirizzo dell'elemento estratto.
INPUT: coda,puntatore a lista non allocata
OUTPUT: ritnora 0 se la coda e' rimasta vuota, ritorna 1 se la coda e' ancora piena*/
int Pop_Coda(LIST*Coda,LIST**Elem);
