#define STRINGAMAX 100
#define MENUMAX 11
/*desc: Questo file contiene funzioni per creare e stampare menu
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739						50/747	
gruppo 27*/


/*Funzione che ritorna un array di stringhe che rappresentano un menu.
/*Al primo posto: nome menu , i restanti posti prima dell'ultimo le scelte,
all'ultimo posto la domanda di scelta.
Le possibili scelte inseribili in questa funzione sono 9
Inoltre viene ritornato il numero di elementi nell'indirizzo di Elem
(se tutto va a buon fine). altrimenti ritorna NULL e 0 in Elem.*/
/*INPUT: Path del file di testo nel quale c'e' il menu*/
char ** Crea_Menu(char* , int *);

/*Funzione che stampa a video un menu. Prende in input: l'array di stringhe che rappresenta il menu (Ritornato dalla funzione Crea_Menu) e il numero
di elemnti*/
void Stampa_Menu(char **,int);

