/*desc: Questo file contiene funzioni la gestione di TAG
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/

typedef struct Tag {
int Parola;			/*1 se viene accettata un Testo 0 se non viene accettata*/
int Ripetizioni;		/*Questa Flag indica che un TAG dello stessa priorita' puo essere aperto*/
int Priorita;			/*Rappresenta la priorita del TAG*/
char * Tag_Apertura;		/*Puntatore al tag di apertura*/
char * Tag_Chiusura;		/*Puntatore al tag di chiusura*/
} TAG;

/*Questa funzione alloca una struttura TAG e la inizializza il valore di ritorno e' il puntatore alla struttura
INPUT: puntatore a stringa Tag di apertura, puratore a stringa Tag di chiusura,parola,ripetizioni sono
Flag che possono assumere valori 0 e 1,ordine priorita rappresenta la priorita */
TAG * Alloca_Tag(char * Tag_Apertura,char * Tag_Chiusura,int Parola,int Ripetizioni,int Priorita);

/*Questa funzione ritorna 0 se la variabile Tag non e' un tag 1 se e' un tag di apertura 2 se e' un tag di chiusura*/
int IsTag(char * Tag);

/*Questa funzione dealloca il Tag */
void Dealloca_Tag(void * Tag);
