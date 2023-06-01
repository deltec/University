/*desc: Questo file contiene funzione principale
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/
#include <stdio.h>
#include <stdlib.h>
#include "funzioni_caric_file.h"
#include "funzioni_char.h"
#include "funzioni_menu.h"
#include "funzioni_ordinamento.h"
#include "funzioni_scri_file.h"


/*La variabile Caricata indica se la struttura dati è stata caricata
La variabile scelta è la possibile scelta del menu
Elem_Array rappresenta il numero sistruttue PAROLE costruite*/
int main(int argc, char *argv[])
{
char ** Menu=NULL,Scelta,*Path;
int Elem_Menu,Elem_Array,Uscita=0,Caricata=0;
PAROLA ** P;

  Menu=Crea_Menu("Menu",&Elem_Menu);  /*Creo il menu*/
  
  
 while (!Uscita)
 {
      Stampa_Menu(Menu,Elem_Menu); /*Stampa ogni volta il menu*/  
      switch (Scelta=read_char("123456789"))
      {
          case '1':
                   printf("Inserisci il path relativo oppure assoluto del file: ");
                   Path=read_string("./ \\",60);    /*Leggo la stringa del  path*/
                   P=Crea_Struttura(Path,&Elem_Array);  /*Creo la struttura dati*/
                   free(Path);   /*Libero spazio relegato al path*/
                   if(P)
                   {
                        Stampa_Parole(P ,Elem_Array);
                        Caricata=1;
                   }
                   else
                   {
                        printf("\nErrore di Caricamento File\n");
                   }
                   
          break;
         
          case '2':
                    if(Caricata)
                    {
                        SelectionSort( swap , conf ,(void **)P, Elem_Array); /*Ordina*/
                        Stampa_Parole(P ,Elem_Array);
                    }
                    else
                    {
                        printf("\n!!!Devi prima caricare la struttura!!!\n");
                    }
                    
          break;
         
          case '3':
                    if(Caricata)
                    {
                        SelectionSort( swap , conf_2 ,(void **)P, Elem_Array);/*Ordina*/
                        Stampa_Parole(P ,Elem_Array);
                    }
                    else
                    {
                        printf("\n!!!Devi prima caricare la struttura!!!\n");
                    }
          break;
          
          case '4':
                    if(Caricata)
                    {
                        BubleSort( swap , conf ,(void **)P, Elem_Array);/*Ordina*/
                        Stampa_Parole(P ,Elem_Array);
                    }
                    else
                    {
                        printf("\n!!!Devi prima caricare la struttura!!!\n");
                    }
          break;
    
          case '5':
                    if(Caricata)
                    {
                        BubleSort( swap , conf_2 ,(void **)P, Elem_Array);/*Ordina*/
                        Stampa_Parole(P ,Elem_Array);
                    }
                    else
                    {
                        printf("\n!!!Devi prima caricare la struttura!!!\n");
                    }
          break;
    
          case '6':
                    if(Caricata)
                    {
                        QuickSort( swap , conf ,(void **)P, 0 ,Elem_Array-1);/*Ordina*/
                        Stampa_Parole(P ,Elem_Array);
                    }
                    else
                    {
                        printf("\n!!!Devi prima caricare la struttura!!!\n");
                    }
          break;
          
          case '7':
                    if(Caricata)
                    {
                        QuickSort( swap , conf_2 ,(void **)P, 0 ,Elem_Array-1);/*Ordina*/
                        Stampa_Parole(P ,Elem_Array);
                    }
                    else
                    {
                        printf("\n!!!Devi prima caricare la struttura!!!\n");
                    }
          break;
    
          case '8':
                    if(Caricata)
                    {
                        printf("Inserisci il path relativo oppure assoluto del file su cui salvare: ");
                        Path=read_string("./ \\",60);    /*Leggo la stringa del  path*/
                        if(!Salva_Su_File(Path,P,Elem_Array))    /*Salvao su file il risultato*/
                        {
                              printf("\n!!!Stampa su file con successo!!!\n");  
                        }
                        else
                        {
                            printf("\n!!!Qualcosa è andato storto!!!\n");
                        }
                        free(Path);                                                
                    }
                    else
                    {
                        printf("\n!!!Devi prima caricare la struttura!!!\n");
                    }
          break;
          
          case '9':
              Uscita=1;  /*Condizione di uscita*/
          break;
      }
   }
  
  /*
  
  
   printf("%d",Elem_Array);
  /*printf("%s",read_string("./",10));*/
  
  	
  return 0;
}
