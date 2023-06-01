/*desc: Questo file contiene funzioni la gestione di TAG
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tag.h"

/*Questa funzione alloca una struttura TAG e la inizializza il valore di ritorno e' il puntatore alla struttura
INPUT: puntatore a stringa Tag di apertura, puratore a stringa Tag di chiusura,parola,ripetizioni sono
Flag che possono assumere valori 0 e 1,ordine priorita rappresenta la priorita */
TAG * Alloca_Tag(char * Tag_Apertura,char * Tag_Chiusura,int Parola,int Ripetizioni,int Priorita)
{
   TAG * Tag;
   Tag=(TAG *)malloc(sizeof(TAG));
   Tag->Parola=Parola;
   Tag->Tag_Apertura=Tag_Apertura;
   Tag->Tag_Chiusura=Tag_Chiusura;
   Tag->Ripetizioni=Ripetizioni;
   Tag->Priorita=Priorita;
   return Tag;
}

/*Questa funzione ritorna 0 se la variabile Tag non e' un tag 1 se e' un tag di apertura 2 se e' un tag di chiusura*/
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

/*Questa funzione dealloca il Tag */
void Dealloca_Tag(void * Tag)
{
   TAG * Temp;
   Temp=(TAG*)Tag;
   free(Temp);
}
