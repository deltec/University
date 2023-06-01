/* Programma:    acquirente.c
* Autore:        Ferdiando Del Trionfo, Cerulli Francesco , Colella francesco
* Data:          16/07/2007
* Descr.:        Client Acquirnete per server concorrente gestioneaste
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


# define  STDPORT 1024



int scelta_menu()
{
	int s;
	printf("\n\n--------MENU--------\n\n");
	printf("1 - ricevi elenco oggetti in asta\n");
	printf("2 - ricevi elenco oggetti scaduti\n");
	printf("3 - ricevi informazioni sull'oggetto\n");
	printf("4 - effettua un'offerta \n");
	printf("5 - Esci \n\n\n");
	printf("fai la tua scelta ");
        scanf("%d",&s);
	return s ;
}
// **************************************** M A I N *******************************************

int main(int argc, char *argv[])
{

struct sockaddr_in client;

        int porta_acq;
	int fd;
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
		if(s==5)
		exit(-1);

		if(s==1) 		
		{						
			
			*stringa='1';
			write(fd,(void*)stringa,sizeof(char)*150);
			//attendere esito
			while((read(fd,(void*)buffer,sizeof(char)*200))!=1)
				{
				
				printf("ID oggetto, nome oggetto:\n %s\n",buffer);

				   write(fd,(void*)prova,sizeof(char)*1);//sincronizzazione
			
				}					
		}

		if(s==2) 		
		{
			
			*stringa='2';
			
			write(fd,(void*)stringa,sizeof(char)*150);	
			while((read(fd,(void*)buffer,sizeof(char)*170))!=1)
				{
				
				printf("ID oggetto, nome oggetto:\n %s\n",buffer);

				   write(fd,(void*)prova,sizeof(char)*1);//sincronizzazione
			
				}	
		
			
		}
		if(s==3) 		
		{
			
			fgets(stringa,24, stdin);
			*stringa='3';
			printf("Inserisci la stringa -ID oggetto-\n");	
			fgets(stringa+1,150, stdin);
			write(fd,(void*)stringa,sizeof(char)*150);
			read(fd,(void*)buffer,sizeof(char)*170);
printf("ID,nome venditore,nome oggetto,descrizione,scadenza asta,prezzo di partenza,ultima offerta:\n %s\n",buffer);
			
		}

		if(s==4) 		
		{
			
			fgets(stringa,24, stdin);
			*stringa='4';
			printf("Inserisci la tua offerta -ID oggetto-nome offerente-valore monetario in euro-\n");	
			fgets(stringa+1,150, stdin);
			write(fd,(void*)stringa,sizeof(char)*150);
			read(fd,(void*)buffer,sizeof(char)*170);
			printf("%s\n",buffer);
			
		}


	}
}


