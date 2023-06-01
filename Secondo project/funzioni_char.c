#include <stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include "funzioni_char.h"

/*desc: Questo file contiene funzioni di gestioni caratteri e stringhe
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739						50/747	
gruppo 27*/

/*ritorna un carattere preso da standard input solo se esso e' presente nella stringa Exp*/
/*Se Exp  ha Lunghezza zero allora prende qualsiasi carattere*/
char read_char(char * Exp)
{
   int Ind=0,Flag=1,Len;
   char C;
   Len=strlen(Exp);
   if(Len!=0 && Exp!=NULL)
   {
      while( Flag )
      {
         C=getch(stdin);
    	 Ind=0;
    	    while( (Ind<Len) && Flag )
    		{
    		   if( C == Exp[Ind])   /*controllo se il carattere letto sta nell'array*/
    		   {
    		      Flag=0;	
    		   }    	
    		   Ind++;
    		}
      }
   }
   else
   {
      C=getch(stdin); /*prendo qualsiasi carattere preso in input*/
   }
   return C;
}

/*ritorna un puntatore ad un char il quale punta ad una stringa di caratteri alfanumerici o di caratteri contenuti nella stringa Exp*/
/*Se Exp ha Lunghezza zero allora prende qualsiasi carattere alfanumerico*/

char *read_string(char * Exp,int Dim)
{
   int Ind=0,Flag=1,Len,Ind_Str=0;
   char C,* Temp_String,*String;
   Temp_String=(char*)calloc(Dim+1,sizeof(char));
   Len=strlen(Exp);
   while( ((C=getch(stdin))!=13) && Ind_Str < Dim ) /*Leggo un carattere e controllo se � una new line oppure se l'indice di stringa � finito*/
   {
	  if( isalpha(C) || isdigit(C) )  /*Controllo se il carattere e' alfanumerico*/
	  {
	     Temp_String[Ind_Str]=C;
		 Ind_Str++;
		 putc(C,stdout);
	  } 
      else 
      {
    	 Ind=0;
    	 Flag=1;
    	 if(C==8) /*se devo cancellare con l'apposito tasto*/
    	 {      
            if(Ind_Str!=0) /*Se non ho cancellato tutto sullo schermo */
            {
               putc(C,stdout);
               putc(0,stdout);
               putc(C,stdout);
               Ind_Str--;
            }
         } 
         else
         {          
            while( (Ind<Len) && Flag ) /*Controllo se il carattere letto si trova nella strinfa Exp*/
            {
               if( C == Exp[Ind])
        	   {
        	      Flag=0;
        	      Temp_String[Ind_Str]=C;
        	      putc(C,stdout);
        	      Ind_Str++;
        	   }
        	   Ind++;
            }
         }
      }   
   }
   Temp_String[Ind_Str]='\0';    /*Chiudo la stringa*/
   String=(char*)calloc(strlen(Temp_String)+1,sizeof(char)); /*Alloco lo spazio giusto per la stringa*/
   strcpy(String,Temp_String); /*Copio il tutto nella nuova stringa*/
   free(Temp_String); /*Libero la memoria inutilizzata*/
   return String;
}

/*Ritorna 1 se Carattere e' uno dei caratteri della stringa Range 0 altrimenti*/
int Special_Char(char Carattere,char *Range)
{
   int Lung=strlen(Range),Indice=0,Trovato=0;
   while( Indice < Lung  && !Trovato)
   {
      if(Range[Indice] == Carattere)
      {
         Trovato=1;
      }
      Indice++;
   }
   return Trovato;
}
