#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "tag.h"
#include "funzioni_char.h"
#include "funzioni_caric_parole.h"

/*desc: Questo file contiene funzioni per caricare parole da file
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739                   50/747
Gruppo 27						*/

/*Funzione che ritorna la I-esima parola dei paragrafi <par>  
OUTPUT:ritorna il puntatore alla lista ordinata delle parole */
LIST * Crea_Lista(char* File_Di_Testo,int I)
{
   FILE *Pf;  /*Puntatore a File*/
   char Stringa[MAXWORD],Carattere,*Stringa_Dinamica;
   int Cont=0,ParIsOpen=0,NumParole=0,Inserito=1;
   LIST *Lista=NULL;

   Pf=fopen(File_Di_Testo,"r");
   if(Pf)
   {
/**************Sacnsione sequenziale caratteri************************************/			
      while(!feof(Pf))  /* esce quando arriva al termine del file*/
      {
         Stringa[0]='\0';
	 Cont=0;
           /**********Riconoscimento dei caratteri ********************************/
         while(( isalnum(Carattere=tolower(getc(Pf))) || Special_Char(Carattere,"<\\èàòùì")) && (!feof(Pf)) && (Cont < MAXWORD)) 
	 {
	    Stringa[Cont]=Carattere;
	    Cont++;	
	 }
         if(Carattere == '>')
         {
            Stringa[Cont]=Carattere;
            Cont++;	
         }
/*****************Controllo una stringa valida****************************/
	 if(Cont)
	 {
	    Stringa[Cont]='\0';
            Stringa_Dinamica=(char*)calloc(sizeof(char),strlen(Stringa)+1);
	    strcpy(Stringa_Dinamica,Stringa);
	    if( strcmp(Stringa_Dinamica,"<par>")==0 ) /*Se trovo un paragrafo <par> di apertura*/
	    {
	       ParIsOpen=1; /*Questa variabile mi indica che ho trovato il paragrafo di aertura*/
               Inserito=0; /*inizializzo che la parola non e' stata inserita nella lista*/
	    }
            if( strcmp(Stringa_Dinamica,"<\\par>")==0 ) /*Se trovo un paragrafo di chiusura*/
	    {
	       ParIsOpen=0;
	       NumParole=0;
               if(!Inserito)
               {
                  Lista=InsElemByOrder(Lista,(void*)"xxx",conf);
                  Inserito=0;
               }
            }
	    if( ParIsOpen ) /*Se ho trovato un par aperto inizio a conteggiare*/
	    {
               if(!IsTag(Stringa_Dinamica) )/*Controllo se la Stringa dinamica non e' un TAG*/
	       {
                  NumParole++;
                  if(NumParole == I)
                  {
                     Lista=InsElemByOrder(Lista,(void*)Stringa_Dinamica,conf);
		     Inserito=1;   /*VAriabile che mi indica l'iserimento dell'iesima parola*/
                  }
 	       }				
	    }
	 }
      }
   }
   if(Pf) /*Se apro un file e da errore  allocherei spazio precato in Array_Di_Parola, quindi li dealloco*/
   {
      fclose(Pf);
   }
   return Lista;
}

/*Funzione che stampa un Elem di una Lista*/
void Print(void *Elem)
{
  printf("%s\n",(char*)Elem);
}

