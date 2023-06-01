/*desc: Questo file contiene funzioni per i percorsi minimi
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747
Gruppo 27*/



/*Questa funzione stampa ricorsivamente un un percorso
IPUT: Destinazione,array predecessori,array delle coincidenze
OUTPUT: stampa a video del percorso*/
void Print(int,int*,void**);

/*Questa funzione stampa a video un percorso minimo
INPUT: sorgente,destinazione
OUTPUT: stampa a video*/
Perc_Min(int Sorgente,int Destinazione,LIST** Grafo,void**Array_Coinc);
