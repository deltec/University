#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "funzioni_caric_file.h"
#include "funzioni_scri_file.h"

/*desc: Questo file contiene funzioni di salvataggio PAROLE
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/



/*funzione che scrive le parole della struttura Array_Di_Parole su file in formato ASCII
prende in input il path del file,la struttura di parole e il numero di parole.
ritorna 0 se nn e' andato a buon fine il salvataggio, 1 se tutto e' andato a buon fine.
modalita di apertura file: se nn esite crea il file altrimenti continua a scrivere nel file.*/
int Salva_Su_File(char* File_Di_Testo,PAROLA ** Array_Di_Parola,int Elem)
{
FILE *Pf;
int Cont=0,Car=0,Len,Err=0;
Pf=fopen(File_Di_Testo,"a+");
	if(Pf && Array_Di_Parola)
	{
		fprintf(Pf,"\t%s\n\n","Analisi del testo");
		while(Cont<Elem)
		{
			
			Len=strlen(Array_Di_Parola[Cont]->Singola_Parola);
			Car=0;
			while(Car<Len)/*scrivi su file la stringa */
			{
				fputc(Array_Di_Parola[Cont]->Singola_Parola[Car],Pf);	
				Car++;
			}
		    fputc(' ',Pf);  /*scrivi su file il numero di occorrenza*/
		    fprintf(Pf, "%d",Array_Di_Parola[Cont]->Numero_Di_Volte);
		    fputc('\n',Pf);
		    Cont++;
		}

	}
	else
    {
		Err=1;	/*Errore o di apertura file o di Array_Di_Parole=NULL*/	
	}
if (Pf) fclose(Pf);
return Err;
}
