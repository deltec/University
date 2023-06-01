/* Programma:    SERVER_P.c
* Autore:        Ferdiando Del Trionfo, Cerulli Francesco , Colella francesco
* Data:          16/07/2007
* Descr.:        Client Veditore per server concorrente gestioneaste
*
**************************************************************************************************/

//  LIB_SOCK.h contiene tutte le inclusioni delle altre librerie necessarie
//   e le funzioni di lettura e scrittura dal socket.


#include <unistd.h>            // interfaccia Unix standard
#include <errno.h>             // codici di errore
#include <sys/types.h>         // tipi predefiniti
#include <arpa/inet.h>         // per convertire ind. IP
#include <sys/socket.h>        // socket
#include <stdio.h>             // i/o
#include <stdlib.h>            // utilita’standard
#include <string.h>            // stringhe
#include <fcntl.h>             // file a basso livello
#include <time.h>              // tempo


# include <pthread.h>


# define  STDPORT 1025



int scelta_menu()
{
	int s;
	printf("\n\n--------MENU--------\n\n");
	printf("1 - metti all'asta un oggetto\n");
	printf("2 - ricevi informazioni sugli oggetti all'asta\n");
	printf("3 - Esci \n\n\n");
	printf("fai la tua scelta ");
        scanf("%d",&s);
	return s ;
}
// **************************************** M A I N *******************************************

int main(int argc, char *argv[])
{

struct sockaddr_in client;

        int porta_acq,i;
	int fd,index;
	int val=1,s=0;
	char *stringa,buffer[170],prova[1];

	
// ******************************************************************************************


     if (argc > 3 || argc ==1) 
     {
         printf("\nErrore\n");
         printf("./acquirente IP porta\n");
         exit(-1);
     }

    if (argc == 2) 
     {
       	porta_acq=STDPORT;
     }
	else
	{
		// Porta Acquirente:
		porta_acq = atoi(argv[2]);
	}
       // ind di tipo INET
printf("porta %d\n",porta_acq);
     client.sin_family = AF_INET;  

     client.sin_port = htons(porta_acq);  

 // rende il socket riusabile
     setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

     // Crea socket per Acquirente:

     if ( (fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
     {     
	perror("Errore nella creazione del Socket");
     	exit(-1);


     }
     // connessiona ip       
     inet_aton(argv[1],&client.sin_addr);    

	if( (connect(fd,(struct sockaddr *)&client,sizeof(client)))!=0)
	{
		printf("Errore di connessione\n");
		exit(-1);
	}
	
        while(1)
	{
		stringa=(char*)calloc(170,sizeof(char));

	  s=scelta_menu();
		if(s==3)
		exit(-1);
//1-nome oggetti-descrizione-prezzo di partenza-giorni di chiusura asta-nome venditore-
		if(s==1) 		
		{						
			fgets(stringa,24, stdin);
			*stringa='1';
			printf("Inserisci la stringa -nome-descrizione-venditore-prezzo-minuti-\n");	
			fgets(stringa+1,150, stdin);
			write(fd,(void*)stringa,sizeof(char)*150);
			read(fd,(void*)buffer,sizeof(char)*50);
			printf("%s\n");
							
		}
		if(s==2) 		
		{
			fgets(stringa,24, stdin);
			*stringa='2';
			printf("Inserisci la stringa -nome venditore-\n");	
			fgets(stringa+1,150, stdin);
			write(fd,(void*)stringa,sizeof(char)*150);
			
			while((read(fd,(void*)buffer,sizeof(char)*200))!=1)
				{
				
				printf("nome venditore,nome oggetto,descrizione,scadenza asta,ultima offerta e offerente:\n %s\n",buffer);
				   write(fd,(void*)prova,sizeof(char)*1);//sincronizzazione
			
				}
			
		}


	}

}

