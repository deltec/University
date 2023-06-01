#include <stdio.h>
#include <stdlib.h>
#include "tag.h"
#include "list.h"
#include "stack.h"
#include "funzioni_char.h"
#include "funzioni_menu.h"
#include "funzioni_analizza_file.h"
#include "funzioni_caric_parole.h"
#include "albero.h"
#include "funzioni_creazione_albero.h"
#include "funzioni_menu.h"

int main(int argc, char *argv[])
{
   NODO *Albero=NULL;
   LIST * Figli;
   char ** Menu=NULL,Scelta,*Path;
   int Elem_Menu,Uscita=0,Caricata=0;
   
   Menu=Crea_Menu("Menu",&Elem_Menu);  /*Creo il menu*/

   while (!Uscita)
   {
      Stampa_Menu(Menu,Elem_Menu); /*Stampa ogni volta il menu*/
      switch (Scelta=read_char("1234")) /*Attendo uno dei 4 caratteri della funzione*/
      {
          case '1':  /*Analisi sintattica e caricamento albero ennario*/
                   printf("Inserisci il path relativo oppure assoluto del file: ");
                   Path=read_string("./ \\",60);    /*Leggo la stringa del  path*/
                   Albero=Crea_Albero(Path); /*Creo l'albero*/
                   if(Albero)
                   {
                      printf("\nSintassi corrette,albero ennario costruito!!!\n");
                   }
                   else
                   {
                      printf("\nErrore di costruzione albero!!!\n");
                   }    
          break;

          case '2':    /*Trasformazione albero ennario in albero binario*/
                    if(Albero)
                    {
                       EnnarioToBinario(Albero,(void*)"X");
                       printf("\n!!!La trasformazione e' stat fatta con successo!!!\n");
                    }
                    else
                    {
                       printf("\n!!!L'albero non e' caricato!!!\n");
                    }
          break;

          case '3':     /*Stampa albero*/
                    if(Albero)
                    {
                       Stampa_Ric_Albero(Albero,Print_Albero,0);
                    }
                    else
                    {
                       printf("\n!!!L'albero non e' caricato!!!\n");
                    }
          break;

          case '4':   /*Esci*/
              Uscita=1;  /*Condizione di uscita*/
          break;
      }
   }
   return 0;
}
