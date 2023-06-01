#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "grafo.h"
#include "gestione_regole.h"
#include "controllo_sintattico.h"
#include "funzioni_menu.h"
#include "percorso_minimo.h"
#include "funzioni_char.h"

int main(int argc, char *argv[])
{
   LIST ** Grafo,**Grafo_Ritorno,**Grafo_Trasposto;            
   void** Coin;
   int **Mat,Esito=1;
   char ** Menu=NULL,Scelta,*Path,*Regola,*Stringa;
   int Elem_Menu,Uscita=0,Caricata=0,Indice,Indice1;
   
   Menu=Crea_Menu("Menu",&Elem_Menu);  /*Creo il menu*/

   while (!Uscita)
   {
      Stampa_Menu(Menu,Elem_Menu); /*Stampa ogni volta il menu*/
      switch (Scelta=read_char("12345678")) /*Attendo uno dei 8 caratteri della funzione*/
      {
          case '1':  /*Carica i grafi delle regole da file*/
                   printf("Inserisci il path relativo oppure assoluto del file: ");
                   Path=read_string("./ \\",60);    /*Leggo la stringa del  path*/
                   Grafo=Crea_Grafo(0);            /*Creo grafo archi andata*/
                   Grafo_Ritorno=Crea_Grafo(0);    /*Creo grafo archi ritorno*/
                   Coin=Crea_Array_Coinc(Grafo);  /*creo l'array delle coincidenze*/
                   Esito=Costruisci_Grafo(Path,&Grafo,&Grafo_Ritorno,&Coin);  /*Costruisce i grafi*/
                   
                   if(!Esito)
                   {
                      printf("\nCaricamento delle regole corretto(RICORDA CHE IL COTROLLO DELLE EXE REG FUNZIONA SOLO SU PIATTAFORME LINUX) !!!\n",Esito);
                      if(!Controlla_Grafo(Grafo,Coin))
                      {
                         printf("\n!!!ATTENZIONE!!!  il grafo e' stato creato ma non e' connesso\n",Esito);
                      }
                   }
                   else
                   {
                      printf("\nErrore di costruzione Grafi!!!\n");
                   }    
          break;

          case '2':    /*Aggiunge una regola nel grafo*/
                    if(!Esito)
                    {
                       printf("\n!!!Inserire la regole(RICORDA CHE IL COTROLLO DELLE EXE REG FUNZIONA SOLO SU PIATTAFORME LINUX)!!!\n"); 
                       Regola=read_string("<>:&|*",256);    /*Leggo la stringa del  path*/
                       if(Inserisci_Regola(Regola,&Grafo,&Grafo_Ritorno,&Coin))
                       {  
                          printf("\n!!!La regola e' stata inserita!!!\n");    
                       }
                       else
                       {
                          printf("\n!!!La regola e' sintatticamente scorretta!!!\n");
                       }   
                    }
                    else
                    {
                       printf("\n!!!Il grafo con le regole non e' stato ancora caricato!!!\n");
                    }
          break;

          case '3':     /*Elimina un nodo dal grafo*/
                    if(!Esito)
                    {
                       Stampa_Array_Coinc(Coin);
                       printf("\n!!!Insersci il numero del nodo corrispondente!!!\n");
                       scanf("%d",&Indice);
                       if(Elim_Nodo(Grafo,Indice))  /*Elimino il nodo dal grafo*/
                       {
                          Elim_Nodo(Grafo_Ritorno,Indice);   /*Elimino il nodo dal grafo di ritorno*/
                          Elim_Nodo_Coinc(Coin,Indice);    /*Elimino il nodo dall'array delle coincidenze*/
                          printf("\n!!!Eliminazione con successo!!!\n",Stringa,Indice);
                       }
                       else
                       {
                          printf("\n!!!Errore di Eliminazione!!!\n");
                       }
                       
                    }
                    else
                    {
                       printf("\n!!!Il grafo con le regole non e' stato ancora caricato!!!\n");
                    }
          break;
          
          case '4':     /*Elimina un arco dal grafo*/
                    if(!Esito)
                    {
                       printf("\nInserisci il primo nodo dell'arco da eliminare: \n");
                       scanf("%d",&Indice);
                       printf("\nInserisci il primo nodo dell'arco da eliminare: \n");
                       scanf("%d",&Indice1);
                       if(!Elim_Arco(Grafo,Indice,Indice1))  //Elimino il nodo
                       {
                          printf("L'arco non esiste!!!\n");
                       }
                    }
                    else
                    {
                       printf("\n!!!Il grafo con le regole non e' stato ancora caricato!!!\n");
                    }
          break;
          
          case '5':     /*Controlla correttezza del file*/
                    if(!Esito)
                    {
                       printf("Inserisci il path relativo oppure assoluto del file: ");
                       Path=read_string("./ \\",60);    /*Leggo la stringa del  path*/
                       if(!(Indice=Controlla_Sintassi(Path,Coin,Grafo,Grafo_Ritorno)))  //controllo la sintassi
                       {
                          printf("\nIl Testo rispetta le regole del grafo!!!\n");
                       }
                       else
                       {
                          if(Indice==1)
                          {
                             printf("\nERRORE di SINTASSI!!\n");      
                          }
                          else if(Indice==2)
                          {
                             printf("\nERRORE di STACK!!\n");
                          }
                          else
                          {
                             printf("\nIl file non esiste!!\n");      
                          }
                          
                       }
                    }
                    else
                    {
                       printf("\n!!!Il grafo con le regole non e' stato ancora caricato!!!\n");
                    }
          break;
          
          case '6':     /*Calcolo percorso minimo*/
                    if(!Esito)
                    {
                       printf("Questo e' il percorso minimo dal nodo di STRAT al nodo* nel grafo di andata\n");
                       Perc_Min(1,Search_String(Coin,"*"),Grafo,Coin);  //percorso minimo del grafo
                       Stampa_Array_Coinc(Coin);   //stampa dell'array delle coincidenze
                       printf("Questo e' il percorso minimo del grafo trasposto dal nodo * allo start\n");
                       Grafo_Trasposto=Trasponi_Grafo(Grafo);  //Trsposizione del greafo
                       Perc_Min(Search_String(Coin,"*"),1,Grafo_Trasposto,Coin);  //Percorso minimo del grafo trasposto
                    }
                    else
                    {
                       printf("\n!!!il grafo delle regole non e' caricato!!!\n");
                    }
          break;
          
          case '7':     /*Stampa regole*/
                    if(!Esito)
                    {
                       Stampa_Array_Coinc(Coin);  //Sampa l'array delle coincidenze
                       Mat=Converti(Grafo);  //matrice di adiacenza
                       printf("Grafo degli archi di andata\n");
                       Stampa_Grafo(Mat,Get_Num_Nodi(Grafo));   //Stampa a video del grafo 
                       Mat=Converti(Grafo_Ritorno);
                       printf("Grafo degli archi di ritorno\n");
                       Stampa_Grafo(Mat,Get_Num_Nodi(Grafo_Ritorno));  //Stampa a video del nodo del grafo di ritorno
                    }
                    else
                    {
                       printf("\n!!!Le regole non sono state caricato!!!\n");
                    }
          break;
          
          case '8':   /*Esci*/
              Uscita=1;  /*Condizione di uscita*/
          break;
      }
   }
   return 0;
  system("PAUSE");	
  return 0;
}
