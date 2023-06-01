#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "funzioni_menu.h"

/*desc: Questo file contiene funzioni per creare e stampare menu
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/

/*Funzione che ritorna un array di stringhe che rappresentano un menu. 
/*Al primo posto: nome menu , i restanti posti prima dell'ultimo le scelte,
all'ultimo posto la domanda di scelta.
Le possibili scelte inseribili in questa funzione sono 9
Inoltre viene ritornato il numero di elementi nell'indirizzo di Elem 
(se tutto va a buon fine). altrimenti ritorna NULL e 0 in Elem.*/
/*INPUT: Path del file di testo nel quale c'e' il menu*/
char ** Crea_Menu(char* File_Di_Testo,int *Elem)
{
   FILE *Pf=NULL;
   char **Menu=NULL,Stringa[STRINGAMAX],Carattere;
   int Cont=0,Righe_Array=0;

   Pf=fopen(File_Di_Testo,"r");
  /*alloco lo spazio per il menu di dimensione MENUMAX*/
   Menu=(char**)calloc(MENUMAX,sizeof(char*));
   if(Pf && Menu)
   {
	  Cont=0;
	  Stringa[0]='\0';
	  while( !feof(Pf)  && (Righe_Array<MENUMAX) )  /* esce quando arriva al termine del file o quando il menu contiene piu di 11 voci copresa l'intestazione e la domanda finale*/
	  {  
		 Stringa[0]='\0';
		 Cont=0;
		 Carattere=getc(Pf);
		 while( (Carattere != '\n') && !feof(Pf) ) /*Esce ad ogni new line*/
		 {
		    Stringa[Cont]=Carattere;
			Cont++;	
			Carattere=getc(Pf);
		 }
		 if(strlen(Stringa) != 0) /*Controllo se è una possibile stringa*/
		 {  
			Menu[Righe_Array]=(char*)calloc(sizeof(char),strlen(Stringa)+1);
			Stringa[Cont]='\0';
			strcpy(Menu[Righe_Array],Stringa);
			Righe_Array++;
		 }
	  }		
	}
   if(Pf==NULL && Menu != NULL) /*significa che apro un file e alloco in Array spazio sprecato*/
   {
      free(Menu);
      Menu=NULL;
   }
   if(Pf != NULL) fclose(Pf);  /*Il file lo chiudo solo se è stato aperto*/
   *Elem=Righe_Array;
   return Menu;
}

/*Funzione che stampa a video un menu. Prende in input: l'array di stringhe che rappresenta il menu (Ritornato dalla funzione Crea_Menu) e il numero 
di elemnti*/
void Stampa_Menu(char ** Menu,int Elem)
{
   int i;
   if(Menu)
   {
	  for(i=0;i<Elem;i++)
	  {
		 printf("%s\n",Menu[i]);
	  }	
   }
   else
   {
	  printf("Errore nella creazione del menu\n");
   }
}

