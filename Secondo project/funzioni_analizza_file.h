#define MAXPRIORITA 5/*grandezza massima di un tag*/
#define MAXTEXT 1000   /*Testo massimo di una stringa*/
#define MAXTAG 64     /*Priorita massima definita dalle regole*/

/*desc: Questo file contiene funzioni Analizzare un file
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739			50/747		
gruppo 27*/

/*Funzione che costruisce le regole di inclusione TAG 
(Queste regole sono statiche possono essere cambiate sole se create nuove 
funzioni regole) ritorna una array di liste_regole*/
LIST **Costruisci_Regole();

/*Questa funzione controlla se il  TagDaInserire rispetti le regole del TagInTesta  
INPUT Lista dell'Array delle Regole, Il TagInTesta reppresenta il tag nella testa dello stack,TagDaInserire rappresenta il tag che vorrei inserire in testa
n.b. se il TagIntesta e' NULLO allora per default si controlla la priorita piu bassa 0
OUTPUT ritorna l'indirzzo della struttura TAG (allocato) se lo si puo inserire altrimenti NULL*/
TAG *Poss_Inserire(LIST ** Array_Regole,TAG * TagInTesta,char * TagDaInserire);

/*Questa funzione controlla se il parametro TagDaEstrarre rispetta le regole del TagDiTesta (deve essere un tag di chiusura)
INPUT: TagDiTesta rappresenta il tag sullo stack mentre il TagDaEstrarre reppresenta il tag incontrato nel testo
OUTPUT : Ritorna 1 se lo posso estrarre, altrimenti 0*/
int Poss_Estrarre(LIST ** Array_Regole,TAG *TagDiTesta,char *TagDaEstrarre);

/*Questa funzione controlla se il TAG puo contenere testo se il tag e NULL per definizione non puo essereci testo.
ritorna 1 se si puo inserire 0 atrimenti
INPUT Tag da conrollare*/
int Contr_Text(TAG * Tag);

/*Funzione che analizza un file di testo 
INPUT: path del file
OUTPUT:ritorna 0 se la correttezza e' verificata 1 se e' errore di TAg 2 se e' errore di stack 3 se e' erroe di apertura file*/
int  Analizza_Testo(char* File_Di_Testo);

