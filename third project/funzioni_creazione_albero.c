#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tag.h"
#include "list.h"
#include "albero.h"
#include "stack.h"
#include "funzioni_char.h"
#include "funzioni_menu.h"
#include "funzioni_analizza_file.h"
#include "funzioni_caric_parole.h"
#include "funzioni_creazione_albero.h"

/*desc: Questo file contiene funzioni per creare un albero
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/

/*Funzione che crea un albrero ennario (Vincolo che il testo deve essere sintatticamente corretto altrimenti non lo costruisce!!!)
INPUT: path del file
OUTPUT:ritorna Il puntatore alla radice, 0 altrimenti*/
NODO *Crea_Albero(char* File_Di_Testo)
{
   FILE *Pf;  /*Puntatore a File*/
   char Stringa[MAXTEXT],Carattere,*Stringa_Dinamica,*TempChar;
   int Cont=0,Errore=0,Testo;
   NODO * Albero=NULL,*Temp;
   void ** Stack,*Elem;

   Stack=CreaStack();
   Errore=Analizza_Testo(File_Di_Testo);
   if( !(Pf=fopen(File_Di_Testo,"r")) ) Errore=3;
   else 
/************************Fase di acquisizione da file TESTO o TAG********************************************/
   Carattere=getc(Pf);/*Leggo il primo carattere*/
   while(!Errore && !feof(Pf)  )  /* esce quando arriva al termine del file oppure trovo un errore di TAG ecc.*/
   {
      Testo=0;/*Questa variabile mi indica 1 se il testo letto potrebbe essere una stringa valida*/
      Stringa[0]='\0';
      Cont=0;
      if(Carattere != '<')   /*Potrebbe iniziare un testo*/
      {
         if(!isspace(Carattere)) /*Controllo se leggo almeno un carattere diverso dagli spazi!!*/
         {
            Testo=1;
         }
         Stringa[Cont]=Carattere;
	 Cont++;	
	 while( ((Carattere=getc(Pf)) != '<')  && (!feof(Pf))  && (Cont < MAXTEXT) ) /*leggo finche trovo caratteri*/
	 {
            if(!isspace(Carattere)) /*Controllo se leggo almeno un carattere diverso dagli spazi!!*/
            {
               Testo=1;
            }
	    Stringa[Cont]=Carattere;
	    Cont++;		
         }
      }else if(Carattere == '<') /*Qui distinguo che inizia unTAG*/
      {
         Testo=1;
         Stringa[Cont]=Carattere;
	 Cont++;	
         while( (Carattere=getc(Pf)) && Carattere!='>'  && (!feof(Pf))  && (Cont < MAXTAG-1) )/*fine TAG*/ 
	 { 
	    if(isalpha(Carattere) || Carattere=='\\')/*iserisco caratteri eil carattere di chiusuratag*/
	    {
	       Stringa[Cont]=Carattere;
	       Cont++;
	    }
	 }
	 if(Carattere=='>')
	 {
	    Stringa[Cont]='>';
	    Cont++;
            Carattere=getc(Pf);/*Devo prendere il successivo carattere*/
         }
      }else
      {
         Carattere=getc(Pf);
      }
/*******************************Fine*acquisizione*******************************************************/
/*******************************Costruzione ALBERO*****************************************************/
      Stringa[Cont]='\0';/*termino la stinga*/
      if(Testo)/*controllo Se ho confezionato almeno un Tag oppure un testo*/
      {
         Stringa_Dinamica=(char*)calloc(sizeof(char),strlen(Stringa)+1);/*alloco e copio dello spazio necessario*/
         strcpy(Stringa_Dinamica,Stringa);

         /*** Controllo se e' un tag di apertura diverso da <it> e <bold> ***/
         if( IsTag(Stringa_Dinamica) == 1 && strcmp("<it>",Stringa_Dinamica) && strcmp("<bold>",Stringa_Dinamica) ) 
         {  
            if( IsEmpty(Stack) )/*Se lo stack e' vuoto creo l'albero*/
            {
               Albero=CreaAlbero ((void*)Stringa_Dinamica);
               Temp=Albero;
            }
            else /*prendo l'elemento in cima allo stack e gli aggiungo come figlio il nuovo nodo*/
            {
               Temp=InsNodoEnn((NODO*)ViewHead(Stack),(void*)Stringa_Dinamica);
            }
            if( !Push(Stack,(void*)Temp) )/*Iserisco nello Stack Il puntatore al nodo dell'albero*/
            { 
               Errore=2; /*Errore di Stack overflow*/
            }
         }
         /**** Controllo se e' un tag di chiusura ****/
         else if(IsTag(Stringa_Dinamica) == 2 && strcmp("<\\it>",Stringa_Dinamica) && strcmp("<\\bold>",Stringa_Dinamica)) 
         {
            if( !(Temp=(NODO*)Pop(Stack)) )/*Estraggo dallo Stack Il primo TAG*/
            {
               Errore=2; /*Errore di Stack */
            }
            else if( IsTag((char*)GetInfo((NODO*)Temp)) ==0 ) /*nel caso il campo info del nodo estratto fosse un TESTO*/
            {
               Pop(Stack); /*Estraggo Nuovamente*/
            }

         }
         else if( IsTag(Stringa_Dinamica)==0 ) /*La stringa e' un Testo*/
         {
            Temp=(NODO*)ViewHead(Stack);
            if( IsTag((char*)GetInfo(Temp))== 0 )/*Se sulla testa dello stack c'e' un nodo che contine testo*/
            {
               TempChar=ConcStr((char*)GetInfo(Temp),Stringa_Dinamica); /*Concateno la stringa in testa allo stack con la stringa letta*/
               Temp->Elem=(void*)TempChar; /*Assegno il nuovo indirizzo della stringa concatenata*/
            }
            else
            {
               Temp=InsNodoEnn((NODO*)ViewHead(Stack),(void*)Stringa_Dinamica); /*inserisco nell'albero il nuovo nodo*/
               if( !Push(Stack,(void*)Temp) )/*Iserisco nello Stack Il puntatore al nodo inserito nell'albero*/
               { 
                  Errore=2; /*Errore di Stack overflow*/
               }
            }
         }
      }
		
   }/*****Chiusura del while lettura file**/		
 /**************************Controllo Errori********************************/
   if(Pf) 
   {
      fclose(Pf); /*Chiudo il file se e' stato aperto*/
      if( Errore != 0) /*Se ci sono errori*/
      {
         Albero=NULL;
      }
   }
   return Albero;
}

/*Stampa Ricorsivamente i campi info dell'albero
INPUT: Radice dell' albero,funzione che stampa l'informazione del nodo
OUTPUT: stampa grafica a video*/
void Stampa_Ric_Albero(NODO *Albero,void (*Print) (NODO *),int Tab)
{
   LIST * Figli;
   int I;
   if(Albero != NULL)
   {  
      for(I=1;I<=Tab;I++)
      {  
         printf("%*c",3,'|');  
      }
      Print(Albero);
      Figli=GetFigli(Albero);
      Tab++; 
      while(Figli != NULL)
      {
         Stampa_Ric_Albero((NODO*)GetInfoList(Figli),Print,Tab);
         Figli=Figli->Next;
      }
   }     
}

/*Questa funzione Stampa a video il campo informazione di un Nodo dell'albero
INPUT: NODO dell'albero
OUTPUT Stampa STDOUT*/
void Print_Albero(NODO * A)
{
   printf("%.10s\n",GetInfo(A));
}
