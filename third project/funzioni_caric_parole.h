/*desc: Questo file contiene funzioni per caricare parole da file
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739                   50/747
Gruppo 27							*/
#define MAXWORD 64

/*Ritorna 1 se Carattere e' uno dei caratteri della stringa Range 0 altrimenti*/
int Special_Char(char Carattere,char *Range);

/*Funzione che ritorna la I-esima parola dei paragrafi <par>  
OUTPUT:ritorna il puntatore alla lista ordinata delle parole */
LIST * Crea_Lista(char* File_Di_Testo,int I);

/*Funzione che stampa un Elem di una Lista*/
void Print(void *Elem);
