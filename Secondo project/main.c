/*desc: Questo file contiene la funzione principale
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739		      50/747		
gruppo 27*/
#include <stdio.h>
#include <stdlib.h>
#include "tag.h"
#include "list.h"
#include "stack.h"
#include "funzioni_char.h"
#include "funzioni_menu.h"
#include "funzioni_analizza_file.h"
#include "funzioni_caric_parole.h"


/*La variabile Caricata indica se la lista i-esima stata caricata
La variabile Analisi rappresenta il valore di ritorno della funzione Analizza_Testo
*/
int main(int argc, char *argv[])
{
   char ** Menu=NULL,Scelta,*Path;
   int Elem_Menu,Uscita=0,Caricata=0,Analisi=3,I,K;
   LIST *Lista1,*Lista2,*ListaMerge;
   
   Menu=Crea_Menu("Menu",&Elem_Menu);  /*Creo il menu*/
   while (!Uscita)
   {
      Stampa_Menu(Menu,Elem_Menu); /*Stampa ogni volta il menu*/  
      switch (Scelta=read_char("1234"))
      {
         case '1':  
                    printf("Inserisci il path relativo oppure assoluto del file: ");
                    Path=read_string("./ \\",60);    /*Leggo la stringa del  path*/
                    Analisi=Analizza_Testo(Path);  /*Analizzo il file*/
                    if(Analisi==3)
                    {
                       printf("\nErrore di Caricamento File\n");
                    }
                    else if(Analisi == 0)
                    {
                       printf("\nSintassi corrette\n");
                    }
                    else if(Analisi == 1)
                    {
                       printf("\nErrore di TAG\n");
                    }
                    else
                    {
                       printf("\nErrore di stack\n");
                    }       
         break;
         case '2':
                    if(Analisi == 0)
                    {
                       Print("\nInserisci il numero delle I-esime parole\n");
 			           scanf("%d",&I);
                       Lista1=Crea_Lista(Path,I);
                       Stampa_Ric(Lista1,Print);
                       Caricata=1;
                    }
                    else
                    {
                       printf("\n!!!L'analisi non e' corretta o il file non e stato caricato!!!\n");
                    }           
         break;        
         case '3':
                    if(Analisi == 0 && Caricata)
                    {
                       Print("\nInserisci il numero delle K-esime parole\n");
 			           scanf("%d",&K);
                       Lista2=Crea_Lista(Path,K);
                       ListaMerge=Merge(Lista1,Lista2,conf);
                       Stampa_Ric(ListaMerge,Print);
                    }
                    else
                    {
                       printf("\n!!!L'analisi non e' corretta o il file non e stato caricato o la lista non e' stata caricata!!!\n");
                    }
         break;
         case '4':
                    Uscita=1;  /*Condizione di uscita*/
         break;
      }
   }

   return 0;
}
