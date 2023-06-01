/*desc: Questo file contiene funzioni di gestioni caratteri e stringhe
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739						50/747	
gruppo 27*/

/*Ritorna 1 se Carattere e' uno dei caratteri della stringa Range 0 altrimenti*/
int Special_Char(char Carattere,char *Range);

/*ritorna un carattere preso da input solo se esso e' presente nella stringa Exp*/
/*Se Exp e' NULL oppure ha Lunghezza zero allora prende qualsiasi carattere*/
char read_char(char * );

/*ritorna un puntatore ad un char il quale punta ad una stringa di caratteri alfanumerici e caratteri contenuti nella stringa Exp*/
/*Se Exp e' NULL oppure ha Lunghezza zero allora prende qualsiasi carattere alfanumerici,numeri*/
char *read_string(char * ,int );

/*Concatena 2 stringhe "stringa1 stringa1" ritornando un nuovo indirizzo di memoria che punta ad una nuova area di memoria
INPUT stringa1 e stringa2
OUTPUT Stringa3 concatemaneto
n.b. il concatemaneto inserisce una spazio tra le due stringhe*/
char *ConcStr(char* Str1,char* Str2);
