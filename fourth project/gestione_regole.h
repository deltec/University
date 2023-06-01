/*desc: Questo file contiene funzioni che gestiscono Le regole
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747
Gruppo 27*/
/*rappresenta il numero massiono di caratteri che puo contenere una regola*/
#define MAXREG  256    

/*Funzione che carica delle regole da file e le inserisce in un grafo
INPUT: path del file di testo delle ragole,Grafo allocato,Array delle conicidenze allocato
OUTPUT: 0 esito positivo altrimeti il valore della riga che ha causato l'errore
grafi delle regole e delle coincidenze riempito
N.B. Ogni regola non deve superare i 256 caratteri*/
int Costruisci_Grafo(char*,LIST***,LIST***,void***);

/*Funzione che controlla se la stringa presa in input rispetta le regole del protocollo interno
INPUT:  Stringa da controllare
OUTPUT: 1 se le rispetta,0 altrimenti*/
int Controlla_Regola(char * );

/*Funzione che inserisce una regola in un grafo
INPUT:  Stringa che contiene la regola,lista di adiacenza delle regole,Grafo allocato degli archi di ritodno,array delle coincidenze
OUTPUT: esito inserimento, 1 inserimento corretto, 0 inserimento non corretto
N.b. la reagola deve essere ben fomata secondo il protocollo interno
Grafo e array_coinc sono tripli puntatori nel caso si dovessero fare riallocazioni con cambi di indirizzo*/
int Inserisci_Regola(char * ,LIST***,LIST***,void*** );

/*Funzione che cerca una stringa nell'array delle coincidenze, ritorna la posizione
INPUT: Array delle coincidenze,Stringa da cercare
OUTPUT: ritorna l'indice se e' stata trovata altrimenti 0*/
int Search_String(void** ,char* );

/*Funzione che crea un array di stringhe '<...>' data una regole
INPUT: Sringa che contiene la regola,valore di ritorno,valoredi ritorno
OUTPUT: array di puntatori a stringhe allocate,numero di stringhe allocate,Separatore rappresenta l'operatore logico trovato
es: |  &   oppure 0*/
char** Scompatta_Regola(char* ,int *,char *);

/*Funzione che controlla se il grafo preso in input rispetta le seguenti regole:
Esiste un Nodo di start e che ogni nodo raggiunge il carattere *
INPUT:  Grafo,array delle coincidenze
OUTPUT: 1 se si verificano le condizioni su cutate ,0 altrimenti*/
int Controlla_Grafo(LIST **,void**);


