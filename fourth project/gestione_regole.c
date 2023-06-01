/*desc: Questo file contiene funzioni che gestiscono Le regole
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747
Gruppo 27*/

#include "list.h"
#include "grafo.h"
#include "gestione_regole.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <regex.h> Questo header file contiene le funzioni per espressioni regolari libreria utilizzabile solo sotto linux*/

/*Funzione che carica delle regole da file e le inserisce in un grafo
INPUT: path del file di testo delle ragole,Grafo allocato,Grafo allocato degli archi di ritodno,Array delle conicidenze allocato
OUTPUT: 0 esito positivo altrimeti la riga che ha causato l'errore
grafi delle regole e delle coincidenze riempito
N.B. Ogni regola non deve superare i 256 caratteri*/
int Costruisci_Grafo(char* File_Di_Testo,LIST*** Grafo,LIST*** Grafo_Ritorno,void***Coin)
{
   FILE *Pf=NULL;
   char Stringa[MAXREG],*Regola,Carattere;
   int Cont=0,Righe_File=1,Flag=1;
   Pf=fopen(File_Di_Testo,"r");
   if(Pf != NULL)
   {
      Cont=0;
      while( !feof(Pf) && Flag==1)  /* esce quando arriva al termine del file oppure una regola non e valida*/
      {
         Stringa[0]='\0';
	 Cont=0;
	 Carattere=getc(Pf);
	 while( (Carattere != '\n') && !feof(Pf) && Cont<MAXREG-1) /*Esce ad ogni new line*/
	 {
            if(Carattere != ' ')
            {
	       Stringa[Cont]=Carattere;
	       Cont++;	
            }
            Carattere=getc(Pf);
	 }
         if(Cont != 0) /*Controllo se � una possibile stringa*/
	 {
	    Regola=(char*)calloc(Cont+1,sizeof(char));
	    Stringa[Cont]='\0';
	    strcpy(Regola,Stringa);
            if(Flag/*=Controlla_Regola(Regola)*/)   //il Controllo espressione regolare puo essere decommentato solo se si utilizzano piattaforme linux
            {
               Inserisci_Regola(Regola,Grafo,Grafo_Ritorno,Coin);   //creazione nodo e coincidenze
               Righe_File++;
            }
         }
      }
      if(Flag)  //Controllo se c'e' stato qualche errore
      {
         Righe_File=0;
      }
   }
   if(Pf != NULL) fclose(Pf);  /*Il file lo chiudo solo se � stato aperto*/
   return Righe_File;
}

/*Funzione che controlla se la stringa presa in input rispetta le regole del protocollo interno
INPUT:  Stringa da controllare
OUTPUT: 1 se le rispetta,0 altrimenti
N.B.: Quasta funzione puo essere utilizzata solo su piattaforme linu*/

//int Controlla_Regola(char * Stringa)
//{
//  int Esito=1,Status;
//   regex_t Re;
//   if (Status=regcomp(&Re, "^(<([[:alpha:]])+>):((<([[:alpha:]])+>\\|)+|(<([[:alpha:]])+>\\&)+)?((<([[:alpha:]])+>)|(\\*))$", 0|1) != 0) 
//   {
//      Esito=0;/* Report error. */
//   }
//   else
//   {
//      Status=regexec(&Re,Stringa,0,NULL,0);
//      regfree(&Re);
//      if (Status != 0) 
//      {
//         Esito=0; /* Report error. */
//      }
//   }
//   return Esito;
//}

/*Funzione che inserisce una regola in un grafo
INPUT:  Stringa che contiene la regola,lista di adiacenza delle regole,,Grafo allocato degli archi di ritorno,array delle coincidenze
OUTPUT: esito inserimento, 1 inserimento corretto, 0 inserimento non corretto
N.b. la reagola deve essere ben fomata secondo il protocollo interno
Grafo e array_coinc sono tripli puntatori nel caso si dovessero fare riallocazioni con cambi di indirizzo*/
int Inserisci_Regola(char *Regola,LIST*** Grafo,LIST*** Grafo_Ritorno,void*** Array_Coinc)
{
   int I,Dim,A,B,Esito=0; 
   char ** Lis,S;
   int Dim_Scomp;
   Lis=Scompatta_Regola(Regola,&Dim_Scomp,&S);
   while((Get_Num_Blocchi(*Grafo))<=(Dim_Scomp+Get_Num_Nodi(*Grafo))) // alloco spazio nel caso non ce ne fosse abbastanza
   {
      *Grafo=Realloca_Grafo(*Grafo);   //rialloco
      *Grafo_Ritorno=Realloca_Grafo(*Grafo_Ritorno);
      *Array_Coinc=Adegua_Array_Coinc(*Array_Coinc,*Grafo); //adeguo l'array delle coincidenze
   }

   if(S=='0')      //Regola di solo contenimento
   {
      A=Search_String(*Array_Coinc,Lis[0]);  //Trovo gli indici
      B=Search_String(*Array_Coinc,Lis[1]);
      if(A==0)  //Caso in cui il nodo A non esistono
      {
         A=Ins_Nodo(*Grafo); //inserisco il nodo
         Ins_Nodo(*Grafo_Ritorno); //inserisco il nodo
         Set_Coinc(*Array_Coinc,A,(void *)Lis[0]); //Setto la coincidenza
      }
      if(B==0)  //caso in cui il nodo B non esiste
      {
         B=Ins_Nodo(*Grafo);   //inserisco il nodo
         Ins_Nodo(*Grafo_Ritorno); //inserisco il nodo 
         Set_Coinc(*Array_Coinc,B,(void *)Lis[1]);  //setto la coincidenza
      }
      Ins_Arco(*Grafo,A,B);   //inserisco l'arco apertura
      Ins_Arco(*Grafo_Ritorno,B,A);   //inserisco l'arco  chiusura
      Esito=1;
   }
   else if (S=='|')   //Regola OR
   {
      A=Search_String(*Array_Coinc,(void *)Lis[0]);
      if(A==0)  //Caso in cui il nodo A non esistono
      {
         A=Ins_Nodo(*Grafo);  //creo il nodo
         Ins_Nodo(*Grafo_Ritorno); //inserisco il nodo
         Set_Coinc(*Array_Coinc,A,(void *)Lis[0]);  //aggiungo la coincidenza
      }
      for(I=1;I<Dim_Scomp;I++)
      {   
         B=Search_String(*Array_Coinc,(void *)Lis[I]);
         if(B==0)  //Caso in cui il nodo B non esistono
         {
            B=Ins_Nodo(*Grafo);    //creo il nodo 
            Ins_Nodo(*Grafo_Ritorno); //inserisco il nodo
            Set_Coinc(*Array_Coinc,B,(void *)Lis[I]);  //aggiungo la coincidenza
         }
         Ins_Arco(*Grafo,A,B);             //iserisco l'arco in parallelo di apertura
         Ins_Arco(*Grafo_Ritorno,B,A);             //iserisco l'arco in parallelo di chiusura
      }
      Esito=1;
   }
   else if (S=='&')   //Regola AND
   {
      int C,D;
      A=Search_String(*Array_Coinc,(void *)Lis[0]);
      C=A;    //assegno il primo nodo della serie
      if(A==0)  //Caso in cui il nodo A non esistono
      {
         A=Ins_Nodo(*Grafo);  //creo il nodo
         Ins_Nodo(*Grafo_Ritorno); //inserisco il nodo
         C=A;
         Set_Coinc(*Array_Coinc,A,(void *)Lis[0]);  //aggiungo la coincidenza
      }
      for(I=1;I<Dim_Scomp;I++)
      {
         B=Search_String(*Array_Coinc,(void *)Lis[I]);
         if(B==0)  //Caso in cui il nodo B non esistono
         {
            B=Ins_Nodo(*Grafo);  //creo il nodo
            Ins_Nodo(*Grafo_Ritorno); //inserisco il nodo
            Set_Coinc(*Array_Coinc,B,(void *)Lis[I]);  //aggiungo la coincidenza
         }
         Ins_Arco(*Grafo,A,B);   //iserisco l'arco in serie di apertura
         D=B;   //Assegno l'ultimo nodo della serie
         A=B;
      }
      Ins_Arco(*Grafo_Ritorno,D,C);   //iserisco l'arco in serie di ritorno
      Esito=1;
   }
   return Esito;
}

/*Funzione che cerca una stringa nell'array delle coincidenze, ritorna la posizione
INPUT: Array delle coincidenze,Stringa da cercare
OUTPUT: ritorna l'indice se e' stata trovata altrimenti 0*/
int Search_String(void** Array_Coinc,char* Stringa)
{
   int Q_Nodi=Get_Num_Nodi((LIST**)Array_Coinc);
   int I=1,Confronto=1,Ritorno;
   while( I<=Q_Nodi && Confronto !=0 )
   {
      Confronto=strcmp(Stringa,(char*)Array_Coinc[I]);
      I++;
   }
   if(!Confronto)
   {
      Ritorno=I-1;   //Esito positivo
   }
   else
   {
      Ritorno=0;    //Esito negativo
   }
   return Ritorno;
}

/*Funzione che crea un array di stringhe '<....>'  data una regole
INPUT: Sringa che contiene la regola,valore di ritorno,valoredi ritorno
OUTPUT: array di puntatori a stringhe allocate,Dim_Arr numero di stringhe -1 allocate,Separatore rappresenta l'operatore logico trovato AND, OR,INGLBAMENTO
es: |  &   oppure 0*/
char** Scompatta_Regola(char* Regola,int *Dim_arr,char *Separatore)
{
   char **Temp,*Stringa1,Stringa[MAXREG];
   int I=0,Cont=0,Dim;
   *Separatore='0';
   Dim=strlen(Regola);
   *Dim_arr=0;
   Temp=(char**)calloc(MAXREG,sizeof(char*)); //Alloco 256 puntatori (per sicurezza)
   while(Regola[Cont] != '>')  //Leggo e alloco il primo TAG 
   {
      Stringa[Cont]=Regola[I];
      Cont++;  //contatore per i caratteri
      I++;    // Contatore per la stringa  
   }
   Stringa[Cont]='>';
   Stringa[Cont+1]='\0';
   Stringa1=(char*)calloc(Cont+2,sizeof(char));
   strcpy(Stringa1,Stringa);
   Temp[*Dim_arr]=Stringa1;
   I=I+2;   // Escludo il carattere due punti
   *Dim_arr=*Dim_arr+1;
   
   while(I<=Dim)  //Scorro i restanti TAG
   {
      Cont=0;
      while(Regola[I] != '>' && Regola[I] != '*')  //Leggo i restanti TAG 
      {
         Stringa[Cont]=Regola[I];
         Cont++;
         I++;
      }
      Stringa[Cont]='>';   //Inserisco il fine TAG
      if(Regola[I] == '*') //Carattere speciale
      {
         Stringa[Cont]='*';
      }
      Stringa[Cont+1]='\0';  //Chiudo la stringa
      Stringa1=(char*)calloc(Cont+2,sizeof(char));
      strcpy(Stringa1,Stringa);
      Temp[*Dim_arr]=Stringa1;   //Assegno il puntatore
      *Dim_arr=*Dim_arr+1;
      if(Regola[I+1]=='|' || Regola[I+1]=='&' )
      {
         *Separatore=Regola[I+1]; 
      }
      I=I+2;
   }
   return Temp;
}

/*Funzione che controlla se il grafo preso in input rispetta le seguenti regole:
Esiste un Nodo di start e che ogni nodo raggiunge il carattere *
INPUT:  Grafo,array delle coincidenze
OUTPUT: 1 se si verificano le condizioni su cutate ,0 altrimenti*/
int Controlla_Grafo(LIST **Grafo,void** Array_Coinc)
{
   int Ritorno=0,*Pred,I,Errore=0,Indice;
   LIST **Grafo_Trasp;
   Pred=Bfs(Grafo,1);   //Esegua la BFS con Nodo sorgente quello di START
   for(I=0;I<Get_Num_Nodi(Grafo);I++)
   {
      if(Pred[I] == -1 && I!=0)
      {
         Errore=1;
      }
   }
   if(!Errore)
   {
      free(Pred);  //Dealloco l'array dei predecessori
      Grafo_Trasp=Trasponi_Grafo(Grafo);
      if(Indice=Search_String(Array_Coinc,"*"))  //Ricerco il numero di nodo con Stringa=*
      {
         Pred=Bfs(Grafo_Trasp,Indice);   //Esegua la BFS con Nodo sorgente quello di END   *
         for(I=0;I<Get_Num_Nodi(Grafo);I++)  //Controllo che nodi siano tutti raggiungibili
         {
            if(Pred[I] == -1 && I!=Indice-1)
            {
               Errore=1;
            }
         }
         free(Pred);  //Dealloco l'array dei predecessori
      }
      else
      {
         Errore=1;
      }
   }
   if(!Errore)
   {
      Ritorno=1;
      Dealloca_Grafo(Grafo_Trasp);  //deallocare il grafo trasposto
      free(Grafo_Trasp);
   }
   return Ritorno;
}

