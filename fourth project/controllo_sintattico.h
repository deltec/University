/*desc: Questo file contiene funzioni il controllo sintattico
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/
#define MAXTEXT 1024
#define MAXTAG 64

/*Funzione che controlla la sintassi del file di testo preso in input
INPUT: path del file,array delle coincidenze,Grafo,Grafo delle regole con archi di ritorno
OUTPUT:ritorna Il puntatore alla radice, 0 altrimenti*/
int Controlla_Sintassi(char*,void**,LIST**,LIST**);

/*Questa funzione prende un TAG di chiusura e ritorna il nodo di apertura corrispondente
INPUT: Tag di chiusura,Array delle coincidenze
OUTPUT: ritorna 0 se non corrisponde a nessun nodo, altrimenti ritorna l'intero che gli corrisponde
N.B. Il Tag di chiusura e delineato dal carattere \ esempio <\....>*/
int GetTagApertura(char*,void**);

/*Questa funzione ritorna controlla se la stringa Tag e' di chiusura o apertura
INPUT:stringa Tag
OUTPUT: Ritorna 1 se tag e di apertura, 2 se Tag e' di chiusura, 0 altrimenti  */
int IsTag(char*);
