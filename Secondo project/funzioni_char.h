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
