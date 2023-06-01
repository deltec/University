#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tag.h"
#include "list.h"
#include "stack.h"
#include "funzioni_analizza_file.h"

/*desc: Questo file contiene funzioni per analizzare un file
autori: Ferdinandeo Del Trionfo     Paolo Selce
matricole 566/739					50/747		
gruppo 27*/

/*Funzione che costruisce le regole di inclusione TAG (Queste regole sono statiche possono essere cambiate sole se create nuove funzioni regole) ritorna una array di liste_regole*/
LIST ** Costruisci_Regole()
{
   LIST ** Array_Liste;
   Array_Liste=(LIST **)calloc(5,sizeof(LIST *));
   Array_Liste[0]=InsElem(NULL,(void *)Alloca_Tag("<testo>","<\\testo>",0,0,0));
   Array_Liste[1]=InsElem(NULL,(void *)Alloca_Tag("<sec>","<\\sec>",0,0,1));
   Array_Liste[2]=InsElem(NULL,(void *)Alloca_Tag("<div>","<\\div>",0,0,2));
   Array_Liste[3]=InsElem(NULL,(void *)Alloca_Tag("<par>","<\\par>",1,0,3));
   Array_Liste[4]=InsElem(NULL,(void *)Alloca_Tag("<bold>","<\\bold>",1,1,4));
   Array_Liste[4]=InsElem(Array_Liste[4],(void *)Alloca_Tag("<it>","<\\it>",1,1,4));
   return Array_Liste;
}

/*Questa funzione controlla se il  TagDaInserire rispetti le regole del TagInTesta  
INPUT Lista dell'Array delle Regole, Il TagInTesta reppresenta il tag nella testa dello stack,TagDaInserire rappresenta il tag che vorrei inserire in testa
n.b. se il TagIntesta e' NULLO allora per default si controlla la priorita piu bassa 0
OUTPUT ritorna l'indirzzo della struttura TAG (allocato) se lo si puo inserire altrimenti NULL*/
TAG *Poss_Inserire(LIST ** Array_Regole,TAG * TagInTesta,char * TagDaInserire)
{
   int Priorita;
   TAG * Ritorno=NULL;
   LIST * Temp;
   if(TagInTesta == NULL) /*Nel caso lo stack fosse vuoto*/
   {
      Priorita=0;/*Priorita Base*/
      Temp=Array_Regole[Priorita];
      while( Temp != NULL && !Ritorno)/*verfico se uno dei TAG di apertura di livello priorita corrisponde a Tag in input*/
      {
         if( strcmp ( ((TAG*)Temp->Elem)->Tag_Apertura,TagDaInserire ) == 0 ) 
         {
            char *Tag_Apertura=((TAG*)Temp->Elem)->Tag_Apertura;
            char *Tag_Chiusura=((TAG*)Temp->Elem)->Tag_Chiusura;
            int Parola=((TAG*)Temp->Elem)->Parola;
            int Ripetizioni=((TAG*)Temp->Elem)->Ripetizioni;
            int Prior=((TAG*)Temp->Elem)->Priorita;

            Ritorno=Alloca_Tag(Tag_Apertura,Tag_Chiusura,Parola,Ripetizioni,Prior); 
         }
      Temp=Temp->Next; 
      }
   }
   else
   {
      Priorita=TagInTesta->Priorita;
      Temp=Array_Regole[Priorita];
   /*Controllo la proprita ripetizioni per il tag (UTA) e attivo */
      if(TagInTesta->Ripetizioni) /*Controllo se il TAG in testa supporta delle ripetizioni della stessa priorita */
      {
         while( Temp != NULL && !Ritorno)/*verfico se uno dei TAG di apertura di livello priorita corrisponde a Tag in input*/
         {
            if( strcmp ( ((TAG*)Temp->Elem)->Tag_Apertura,TagDaInserire ) == 0 ) 
            {
               char *Tag_Apertura=((TAG*)Temp->Elem)->Tag_Apertura;
               char *Tag_Chiusura=((TAG*)Temp->Elem)->Tag_Chiusura;
               int Parola=((TAG*)Temp->Elem)->Parola;
               int Ripetizioni=((TAG*)Temp->Elem)->Ripetizioni;
               int Prior=((TAG*)Temp->Elem)->Priorita;

               Ritorno=Alloca_Tag(Tag_Apertura,Tag_Chiusura,Parola,Ripetizioni,Prior); 
            }
         Temp=Temp->Next; 
         }
      }
   /*priorita(UTA)+1 == Priorita(TL) come da documetazione esterna*/
      if(!Ritorno && ( (Priorita+1) < MAXPRIORITA) )/*se non ho trovato il tag (nel ciclo superiore) e ci sono altre regole dopo alla priorita corrente*/
      {
         Priorita=Priorita+1;
         Temp=Array_Regole[Priorita];
         while( Temp != NULL && !Ritorno)
         {
            if( strcmp ( ((TAG*)Temp->Elem)->Tag_Apertura , TagDaInserire ) == 0 ) /*verfico se il TAG di apertura corrisponde a Tag in input*/
            {
               char *Tag_Apertura=((TAG*)Temp->Elem)->Tag_Apertura;
               char *Tag_Chiusura=((TAG*)Temp->Elem)->Tag_Chiusura;
               int Parola=((TAG*)Temp->Elem)->Parola;
               int Ripetizioni=((TAG*)Temp->Elem)->Ripetizioni;
               int Prior=((TAG*)Temp->Elem)->Priorita;

               Ritorno=Alloca_Tag(Tag_Apertura,Tag_Chiusura,Parola,Ripetizioni,Prior); 
            }
               Temp=Temp->Next;
         }
      }
   }
   return Ritorno;
}

/*Questa funzione controlla se il parametro TagDaEstrarre rispetta le regole del TagDiTesta (deve essere un tag di chiusura)
INPUT: TagDiTesta rappresenta il tag sullo stack mentre il TagDaEstrarre reppresenta il tag incontrato nel testo
OUTPUT : Ritorna 1 se lo posso estrarre, altrimenti 0*/
int Poss_Estrarre(LIST ** Array_Regole,TAG *TagDiTesta,char *TagDaEstrarre)
{
   int Ritorno=0,Priorita;
   LIST * Temp;
   if(TagDiTesta != NULL)
   {
      Priorita=TagDiTesta->Priorita;
      Temp=Array_Regole[Priorita];
      while( Temp != NULL && !Ritorno)
      {
         if( !strcmp ( ((TAG*)Temp->Elem)->Tag_Chiusura , TagDaEstrarre )  ) /*verfico se il TAG di apertura corrisponde a TagDaEstrarre*/
         {
            Ritorno=1; 
         }
         Temp=Temp->Next;
      }
   }
   else
   {
      Ritorno=0;
   }
   return Ritorno;
}

/*Questa funzione controlla se il TAG puo contenere testo se il tag e NULL per definizione non puo essereci testo.
ritorna 1 se si puo inserire 0 atrimenti
INPUT Tag da conrollare*/
int Contr_Text(TAG * Tag)
{
   int Ritorno=0;
   if(Tag != NULL && Tag->Parola)
   {
      Ritorno=1;
   }
  
   return Ritorno;
}




/*Funzione che analizza un file di testo 
INPUT: path del file
OUTPUT:ritorna 0 se la correttezza e' verificata 1 se e' errore di TAg 2 se e' errore di stack 3 se e' erroe di apertura file*/
int  Analizza_Testo(char* File_Di_Testo)
{
   FILE *Pf;  /*Puntatore a File*/
   char Stringa[MAXTEXT],Carattere,*Stringa_Dinamica;
   int Cont=0,Errore=0,Testo;
   LIST ** Array_Regole;
   void ** Stack,*Elem;

   Stack=CreaStack();
   Array_Regole=Costruisci_Regole();/*creo l'array delle regole*/
   if( !(Pf=fopen(File_Di_Testo,"r")) ) Errore=3;
   else 
/************************Fase di acquisizione da file******************************************************/
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
/*******************************Controllo regole*********************************************************/
      Stringa[Cont]='\0';/*termino la stinga*/
      if(Testo)/*controllo Se ho confezionato un almeno un Tag oppure un testo*/
      {
         Stringa_Dinamica=(char*)calloc(sizeof(char),strlen(Stringa)+1);/*alloco e copio dello spazio necessario*/
         strcpy(Stringa_Dinamica,Stringa);
         
         if( IsTag(Stringa_Dinamica) == 1 ) /*Controllo se e' un tag di apertura oppure non e' ancora stato insrito alcun TAG*/
         {  
            TAG * Tag;
            if( Tag=Poss_Inserire(Array_Regole,(TAG*)ViewHead(Stack),Stringa_Dinamica) ) /*controllo Se posso inserire il tag di apertura*/
            {
               if( !Push(Stack,(void *)Tag) )/*Iserisco nello Stack Il TAG*/
               { 
                  Errore=2; /*Errore di Stack overflow*/
               }
            }
            else
            {
               Errore=1; /*Errore TAG*/  
            }
         }
         else if(IsTag(Stringa_Dinamica) == 2 ) /*Controllo se e' un tag di chiusura */
         {
            if( Poss_Estrarre(Array_Regole,(TAG*)ViewHead(Stack),Stringa_Dinamica) ) /*controllo Se posso inserire il tag di apertura*/
            {
               if( !Pop(Stack) )/*Estraggo dallo Stack Il TAG*/
               {
                  Errore=2; /*Errore di Stack */
               }
            }
            else
            {
               Errore=1;/*Errore TAG*/
            }
         }
         else  /*La stringa e' un Testo*/
         {
            if( !Contr_Text((TAG*)ViewHead(Stack)) )/*Conrollo se il TAG supporta del TESTO*/
            {
               Errore=1; 
            }
         }
      }
		
   }/*****Chiusura del while lettura file**/		
 /**************************Controllo Correttezza********************************/
   if(Pf) 
   {
      fclose(Pf); /*Chiudo il file se e' stato aperto*/
      Dealloca_Ric(Array_Regole[0],Dealloca_Tag);/*Dealloco le liste e i tag*/
      Dealloca_Ric(Array_Regole[1],Dealloca_Tag);
      Dealloca_Ric(Array_Regole[2],Dealloca_Tag);
      Dealloca_Ric(Array_Regole[3],Dealloca_Tag);
      Dealloca_Ric(Array_Regole[4],Dealloca_Tag);
      if(IsEmpty(Stack) && Errore == 0) /*Se lo stack e' vuoto e non ci sono errori allora la sintassi e giusta*/
      {
         Errore=0;/*No errori*/
      }
   }
   return Errore;
}
