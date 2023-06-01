/*desc: Questo file contiene funzioni per i percorsi minimi
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747
Gruppo 27*/


#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include  "percorso_minimo.h"
#include "grafo.h"

/*Questa funzione stampa ricorsivamente un un percorso
IPUT: Destinazione,array predecessori,array delle coincidenze
OUTPUT: stampa a video del percorso*/
void Print(int Destinazione,int*Pred,void**Array_Coinc)
{
   if(Pred[Destinazione] != -1)
   {
      Print(Pred[Destinazione],Pred,Array_Coinc);
   }
   printf("%s\n",Array_Coinc[Destinazione+1]);
}

/*Questa funzione stampa a video un percorso minimo
INPUT: sorgente,destinazione
OUTPUT: stampa a video*/
Perc_Min(int Sorgente,int Destinazione,LIST** Grafo,void**Array_Coinc)
{
   int*Pred,Indice;
   Pred=Bfs(Grafo,Sorgente);
   Print(Destinazione-1,Pred,Array_Coinc);
}

