#define MAXPRIORITA 5
#define MAXTEXT 1000 
#define MAXTAG 64 
/*desc: Questo file contiene funzioni per creare un albero
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747
gruppo 27*/

/*Funzione che crea un albrero ennario (Vincolo che il testo deve essere sintatticamente corretto altrimenti non lo costruisce!!!)
INPUT: path del file
OUTPUT:ritorna Il puntatore alla radice, 0 altrimenti*/
NODO * Crea_Albero(char * File_Di_Testo);

/*Stampa Ricorsivamente i campi info dell'albero
INPUT: Radice dell' albero,funzione che stampa l'informazione del nodo
OUTPUT: stampa grafica a video*/
void Stampa_Ric_Albero(NODO *Albero,void (*Print) (NODO *),int Tab);

/*Questa funzione Stampa a video il campo informazione di un Nodo dell'albero
INPUT: NODO dell'albero
OUTPUT Stampa STDOUT*/
void Print_Albero(NODO * A);

