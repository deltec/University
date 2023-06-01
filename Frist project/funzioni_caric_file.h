/*desc: Questo file contiene funzioni per caricare e creare PAROLE da un file
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/

#define MAXTEST 128
#define MAXWORD 64

typedef struct Parola {
int Numero_Di_Volte;
char* Singola_Parola;
} PAROLA;

/*Crea una Struttura PAROLA Ritorna un puntatore ad una struttura allocata*/
PAROLA* Crea_PAROLA()  ;

/*INIZIALIZZA UNA struttura parola  INPUT: puntatore all struttura da inizializzare, puntatore alla stringa da inserire, campo Numero di volte.
Attenzione il secondo parametro deve essere allocato dinamicamente oppure puo' essere inserito
Come parametro statico*/

void Inizializza_PAROLA (PAROLA* ,char*  , int );

/*Incrementa di un'unita' l'intero Numero_Di_Volte*/
void Incrementa(PAROLA* P);

/*Funzione di ricerca sequenziale INPUT: PAROLA ** ,int elem ,char *Parola prola da ricercare OUTPUT:-1 se nn trvato nulla una valore tra[0,elem]  che indica dove si trova quella parola*/
int Ricerca_Parola(PAROLA ** ,int ,char *);

/*Funzione che analizza un file di testo e crea strutture PAROLA per ogni parola trovata oppure incrementa
il contatore se esiste gia INPUT File di testo , Elem ritnorna il numero di elementi trovati   OUTPUT:ritorna il puntatore all'array dei puntatori 
alle Strutture dati PAROLA*/
PAROLA ** Crea_Struttura(char* ,int *);
