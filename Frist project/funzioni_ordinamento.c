#include <stdio.h>
#include <stdlib.h>
#include "funzioni_caric_file.h"
#include "funzioni_ordinamento.h"
/*desc: Questo file contiene funzioni di ordinamento, confronto parole , scambio 
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/


/*Funzione di scambio tra PAROLE input: doppio puntatore ad un void e a e b rappresentano i due indici da scambiare*/
void swap(void ** array,int a,int b)
{
PAROLA * Temp;
PAROLA ** Cast;
Cast=(PAROLA**)array;
Temp=Cast[a];
Cast[a]=Cast[b];
Cast[b]=Temp;
}


/*Confronta gli interi di indici a,b della struttura PAROLA ritorna <0 se a<b, 0 se a==b , >0 se a>b*/
int conf(void ** array,int a,int b)
{
int Equal_Str;
PAROLA ** Cast;
Cast=(PAROLA**)array;
Equal_Str=strcmp(Cast[a]->Singola_Parola,Cast[b]->Singola_Parola);	
return Equal_Str;
}

/*Confronta le stinghe di indice a,b della struttura PAROLA ritorna <0 se a<b, 0 se a==b , >0 se a>b*/
/*Il confronto di stringhe si basa sulla funzione di libreria strcmp*/
int conf_2(void ** array,int a,int b)
{
int Equal_Str;
PAROLA ** Cast;
Cast=(PAROLA**)array;	
	if(Cast[a]->Numero_Di_Volte < Cast[b]->Numero_Di_Volte)
	{
		Equal_Str=-1;
	}else if(Cast[a]->Numero_Di_Volte==Cast[b]->Numero_Di_Volte)
	{
		Equal_Str=0;
	}else    
	{
		Equal_Str=1;
	}
return Equal_Str;
}


/*Funzione di ordinamento (Selection Sort)
INPUT : funzione di scambio tra due elementi, funzione di confronto,array , dimensione dell'array*/
void SelectionSort( void (*swap) (void **,int,int) , int (*conf) (void **,int,int) ,void **array, int size)
{
  int i, j, min;
 
  for (i = 0; i < size - 1; i++)
  {
    min = i;
    for (j = i+1; j < size; j++)
    {
       if ( (*conf)(array,j,min)<0  ) /* ritorna <0 se a<b, 0 se a==b , >0 se a>b*/
       {
          min = j;
       }
    }
    (*swap)(array,i,min);
  }
}



/*Funzione di ordinamento (Buble Sort)
INPUT : funzione di scambio tra due elementi, funzione di confronto,array , dimensione dell'array*/
void BubleSort( void (*swap) (void **,int,int) , int (*conf) (void **,int,int) ,void **array, int size)
{
   int i, tmp;
   int alto=size;
 
   while (alto > 0)
   {
         for (i=0; i<alto-1; i++)
         {
           if ( (*conf)(array,i,i+1)>0  )  /* ritorna <0 se a<b, 0 se a==b , >0 se a>b*/
           {
	     (*swap)(array,i,i+1);
           }
	 }
	alto--;
   }
     
}


/*Funzione di ordinamento ricorsiva (Quick sort)
INPUT : funzione di scambio tra due elementi, funzione di confronto,array , dimensione dell'array*/
void QuickSort(void (*swap) (void **,int,int) , int (*conf) (void **,int,int),void **array, int begin, int end) 
{
    int pivot, l, r; 

    if (end > begin) {
       pivot = begin;
       l = begin + 1;
       r = end+1;
       while(l < r)
          if ( (*conf)(array,l,pivot)<0 ) 
             l++;
          else {
             r--;
             (*swap)(array,l,r);
          }
       l--;
       (*swap)(array,begin,l);
       QuickSort((*swap),(*conf),array, begin, l);
       QuickSort((*swap),(*conf),array, r, end);
    }
 }



