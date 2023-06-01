#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "grafo.h"
#include "stack.h"
#include "controllo_sintattico.h"
#include "gestione_regole.h"


/*desc: Questo file contiene funzioni il controllo sintattico
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/

/*Funzione che controlla la sintassi del file di testo preso in input
INPUT: path del file,array delle coincidenze,Grafo,Grafo delle regole con archi di ritorno
OUTPUT: ritorna 0 se il controllo sintattico e'giusto 1 se non e' giusto 2 se e' errore di stack 3 errore di apertura file*/
int Controlla_Sintassi(char* File_Di_Testo,void** Array_Coinc,LIST**Grafo,LIST**Grafo_Ritorno)
{
   FILE *Pf;  /*Puntatore a File*/
   char Stringa[MAXTEXT],Carattere,*Stringa_Dinamica,*TempChar;
   int Test=0,Cont=0,Errore=0,Testo,Index,*Attuale,*Temp,Direzione=1; //La variabile direzione indica la direzione del grafo 1 indica andata
   void ** Stack,*Elem;

   Attuale=(int*)malloc(sizeof(int));
   Stack=CreaStack();
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
/*******************************Controllo Regole*****************************************************/
      Stringa[Cont]='\0';/*termino la stinga*/
      if(Testo)/*controllo Se ho confezionato almeno un Tag oppure un testo*/
      {
         Stringa_Dinamica=(char*)calloc(sizeof(char),strlen(Stringa)+1);/*alloco e copio dello spazio necessario*/
         strcpy(Stringa_Dinamica,Stringa);
         /*** Controllo se e' un tag di apertura ***/
         if( IsTag(Stringa_Dinamica) == 1  ) 
         { 
            if( IsEmpty(Stack) )/*Se lo stack e' vuoto inserisco il nodo di start grafo*/
            {
               if(!Search_String(Array_Coinc,Stringa_Dinamica))  //caso non coincidesse con il tag di start
               {
                  Errore=1;        //Errore di sintassi
               }
               else
               {
                  Temp=(int*)malloc(sizeof(int));
                  *Temp=1;
                  *Attuale=*Temp;
                  if(!Push(Stack,(void*)Temp))  //Metto nello stack
                  {
                     Errore=2; 
                  }
               }
            }
            else 
            {
               if(Direzione) //Controllo se sto in andata
               {
                  Index=Search_String(Array_Coinc,Stringa_Dinamica);
                  if(Esiste(Grafo,*Attuale,Index))  //Devo controllare che l'elemento in testa allo stack ha liste si adiacente con il nodo cercato
                  {
                     Temp=(int*)malloc(sizeof(int));
                     *Temp=Index;
                     *Attuale=Index;
                     if( !Push(Stack,(void*)Temp) )/*Iserisco nello Stack Il puntatore al nodo dell'albero*/
                     { 
                        Errore=2; /*Errore di Stack overflow*/
                     }
                  }
                  else
                  {
                     Errore=1;
                  }
               }
               else   //nel caso fossimo di ritorno
               {
                  Direzione=1;   //Cambio direzione
                  Index=Search_String(Array_Coinc,Stringa_Dinamica);
                  if((Temp=(int*)ViewHead(Stack)) != NULL)
                  {
                     if(Esiste(Grafo,*Temp,Index))  //Devo controllare che l'elemento in testa allo stack ha liste si adiacente con il nodo cercato
                     {
                        Temp=(int*)malloc(sizeof(int));
                        *Temp=Index;
                        if( Push(Stack,(void*)Temp) )/*Iserisco nello Stack Il puntatore al nodo dell'albero*/
                        { 
                           *Attuale=Index;  //VARIATO
                        }
                        else
                        {
                           Errore=2; /*Errore di Stack overflow*/
                        }
                     }
                     else
                     {
                        Errore=1;
                     }
                  }
                  else
                  {
                     Errore=1;
                  }
               }
            }
         }
         /**** Controllo se e' un tag di chiusura ****/
         else if(IsTag(Stringa_Dinamica) == 2 ) 
         { 
            if(Direzione)     //Caso in andata
            {
               Index=GetTagApertura(Stringa_Dinamica,Array_Coinc);
               if((Temp=(int*)Pop(Stack)) != NULL)
               {
                  if( *Temp!= Index )/*controllo se il tag letto coincide con quello di chiusura*/
                  { 
                     Errore=1;
                  }
               }
               else
               {
                  Errore=1; 
               }
            }
            else        //caso di ritorno
            {
               Index=GetTagApertura(Stringa_Dinamica,Array_Coinc);
               if((Temp=(int*)Pop(Stack)) != NULL)
               {
                  if( *Temp== Index )/*controllo se il tag letto coincide con quello di chiusura*/
                  { 
                     if(Esiste(Grafo_Ritorno,*Attuale,Index))  //Devo controllare che l'elemento in testa allo stack ha liste si adiacente con il nodo cercato
                     {
                        *Attuale=Index;
                     }
                     else
                     {
                        Errore=1;
                     }
                  }
                  else
                  {
                     Errore=1;
                  }
               }
               else
               {
                  Errore=1; 
               }
            }
         }
         else if( IsTag(Stringa_Dinamica)==0 ) /*La stringa e' un Testo*/
         {
            Direzione=0;
            Temp=(int*)malloc(sizeof(int));
            *Temp=Search_String(Array_Coinc,"*");
            if(!Esiste(Grafo,*Attuale,*Temp))/*Se sulla testa dello stack c'e' il nodo '*' */
            {
               Errore=1;
            }
         }
      }
   }/*****Chiusura del while lettura file**/		
 /**************************Controllo Errori********************************/
   if(Pf) 
   {
      fclose(Pf); /*Chiudo il file se e' stato aperto*/
   }
   if(!IsEmpty(Stack))/*Se lo stack e' vuoto inserisco il nodo di start grafo*/
   {
      Errore=1;
   }
   return Errore;
}

/*Questa funzione prende un TAG di chiusura e ritorna il nodo di apertura corrispondente
INPUT: Tag di chiusura,Array delle coincidenze
OUTPUT: ritorna 0 se non corrisponde a nessun nodo, altrimenti ritorna l'intero che gli corrisponde
N.B. Il Tag di chiusura e delineato dal carattere \ esempio <\....>*/
int GetTagApertura(char*Tag_Chiusura,void**Array_Coinc)
{
   int I=1,Trovato=0,J=0,C=0;
   char *Temp;
   Temp=(char*)malloc(strlen(Tag_Chiusura)*sizeof(char));
   for(J=0;J<strlen(Tag_Chiusura);J++)   //copio tutto tranne che il carattere di chiusura TAG
   {
      if(Tag_Chiusura[J] != '\\')
      {
         Temp[C]=Tag_Chiusura[J];
         C++;
      }
   }
   Temp[C]='\0';
   while(I<Get_Num_Nodi((LIST**)Array_Coinc) && !Trovato)
   {
      if(strcmp(Temp,Array_Coinc[I]) == 0)
      {
         Trovato=I;
      }
      I++;
   }
   return Trovato;
}

/*Questa funzione ritorna controlla se la stringa Tag e' di chiusura o apertura
INPUT:stringa Tag
OUTPUT: Ritorna 1 se tag e di apertura, 2 se Tag e' di chiusura, 0 altrimenti  */
int IsTag(char * Tag)
{
   int Ritorno;
   if(strlen(Tag)<2)
   {
      Ritorno=0;
   }
   else if(Tag[0]=='<' && Tag[strlen(Tag)-1]=='>')
   {
      if(Tag[1]=='\\')
      {
         Ritorno=2;
      }
      else 
      {
         Ritorno=1;
      }
   }
   else
   {
      Ritorno=0;
   }
   return Ritorno;
}
