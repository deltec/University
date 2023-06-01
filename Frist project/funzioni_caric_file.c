#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funzioni_caric_file.h"

/*desc: Questo file contiene funzioni per caricare e creare PAROLE da un file
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/


/*Crea una Struttura PAROLA Ritorna un puntatore ad una struttura allocata*/
PAROLA* Crea_PAROLA()
{
	PAROLA* P=NULL;
	P=(PAROLA*)malloc(sizeof(PAROLA));
	P->Numero_Di_Volte=0;
	P->Singola_Parola=NULL;
	return P;
}	

/*INIZIALIZZA UNA struttura parola  INPUT: puntatore all struttura da inizializzare, puntatore alla stringa da inserire, campo Numero di volte.
Attenzione il secondo parametro deve essere allocato dinamicamente oppure puo' essere inserito 
Come parametro statico*/

void Inizializza_PAROLA (PAROLA* P ,char* Stringa , int N)
{
	if(P != NULL)
	{
	P->Numero_Di_Volte=N;
	P->Singola_Parola=Stringa;
	}
}

/*Incrementa di un'unita' l'intero Numero_Di_Volte*/
void Incrementa(PAROLA* P)
{
	P->Numero_Di_Volte++;
}

/*Funzione di ricerca sequenziale INPUT: PAROLA ** ,int elem ,char *Parola prola da ricercare OUTPUT:-1 se nn trvato nulla una valore tra[0,elem]  che indica dove si trova quella parola*/
int Ricerca_Parola(PAROLA ** Array_Di_Parole,int elem,char *Parola)
{
int Condizione_Di_Uscita=0,Inc=0;

	while(Condizione_Di_Uscita==0 && Inc!=elem && Array_Di_Parole!=NULL)
	{
		/*la condizionio viene inizializzata ad uno quando viene trovata una parola*/
		if(strcmp(Parola,Array_Di_Parole[Inc]->Singola_Parola) == 0)
		{
			Condizione_Di_Uscita=1;
		}else{
                       Inc++;
                     }
	}
	if(!Condizione_Di_Uscita)
	{
		Inc=-1;		
	}

return Inc;
}


/*Funzione che analizza un file di testo e crea strutture PAROLA per ogni parola trovata oppure incrementa
il contatore se esiste gia. INPUT File di testo , Elem ritnorna il numero di elementi trovati   OUTPUT:ritorna il puntatore all'array dei puntatori 
alle Strutture dati PAROLA*/
PAROLA ** Crea_Struttura(char* File_Di_Testo,int *Elem)
{

FILE *Pf;  /*Puntatore a File*/
PAROLA **Array_Di_Parola=NULL;
char Stringa[MAXWORD],Carattere,*Stringa_Dinamica;
int Cont=0,Righe_Array=0,Error_Mem=0,Allocazione_Totale,Valore;

Pf=fopen(File_Di_Testo,"r");
/*Alloco un array di parole lungo MAXTEST*/
Array_Di_Parola=(PAROLA**)calloc(sizeof(PAROLA*),MAXTEST);


	if(Pf && Array_Di_Parola)
	{
			Allocazione_Totale=MAXTEST;
		while(!feof(Pf))  /* esce quando arriva al termine del file*/
		{
			Stringa[0]='\0';
			Cont=0;
/*Esce quando non e' un carattere alfanumerico,quando c'e' un errore di riallocazione di memoria oppure una parola superi MAXWORD     nota il carattere viene trasformato in minuscolo per il confronto*/
			while( isalpha(Carattere=tolower(getc(Pf)))  && (!feof(Pf)) && !Error_Mem && (Cont < MAXWORD) ) 
			{
				Stringa[Cont]=Carattere;
				Cont++;		
			}

			if(Cont)
			{
			  Stringa[Cont]='\0';
				if( (Valore=Ricerca_Parola(Array_Di_Parola,Righe_Array,Stringa)) == -1)  /*controllo se la parola esiste*/
				{
				Array_Di_Parola[Righe_Array]=Crea_PAROLA();
				Stringa_Dinamica=(char*)calloc(sizeof(char),strlen(Stringa)+1);
				strcpy(Stringa_Dinamica,Stringa);
				Inizializza_PAROLA (Array_Di_Parola[Righe_Array],Stringa_Dinamica,1);
				Righe_Array++;
				}
                else
                {
					Incrementa(Array_Di_Parola[Valore]);	
				
                }
			}
			
			if (Righe_Array==Allocazione_Totale) /*Controllo se è finito lo spazio per inserire parole*/
    			{
		      	      PAROLA ** Temp;
			      Allocazione_Totale=Allocazione_Totale+MAXTEST;
/*Rialloco spazio nel caso ci fossero piu parole di MAXTEST */
                              Temp=realloc(Array_Di_Parola,sizeof(PAROLA*)*Allocazione_Totale);
                              if (Temp)
                              {
                                  Array_Di_Parola=Temp;
				  
					
                              }
                              else
                              {
                                 Error_Mem=1;/*caso di Errore di allocazione*/
                              }
                }
		}
			
	}
if(Pf==NULL && Array_Di_Parola != NULL) /*Se apro un file e da errore  allocherei spazio sprecato in Array_Di_Parola, quindi lo dealloco*/
{
free(Array_Di_Parola);
Array_Di_Parola=NULL;
}

if(Pf) fclose(Pf); /*Chiudo il file se è stato aperto*/
/*valori di ritorno*/
*Elem=Righe_Array;
return Array_Di_Parola;
}

/*Stampa a video le parole e le occorrenze*/
void Stampa_Parole(PAROLA ** Array_Di_Parola ,int Elem)
{
	int i;
	if(Array_Di_Parola)
	{
		for(i=0;i<Elem;i++)
		{
			printf("%s ",Array_Di_Parola[i]->Singola_Parola);
			printf("%d\n",Array_Di_Parola[i]->Numero_Di_Volte);
			if (i%20==0 && i != 0) system("PAUSE"); /*Chiama una pausa ogni 20 parole*/
			
		}	
	}else{
		printf("Errore\n");
	}

}



