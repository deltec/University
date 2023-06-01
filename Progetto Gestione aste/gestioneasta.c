/* Programma:    gestioneasta.c
* Autore:        Ferdiando Del Trionfo, Cerulli Francesco , Colella francesco
* Data:          16/07/2007
* Descr.:        Server concorrente TCP/IP per la gestione di aste.,
*                Con scrittura di LOG.
*
**************************************************************************************************/




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
#include <unistd.h>            // interfaccia Unix standard
#include <netdb.h>
#include "list.c"		//Funzioni che gestiscono le liste
#include "readerwriter.c"	//funzioni che implementano sinc reader writer

# define STDPORT_A 1024
# define STDPORT_V 1025
# define  MAX      256
# define  BACKLOG  20




//---------------------------------
int log_att;  //descrittore dello attivity_log_file
pthread_mutex_t sinc_log=PTHREAD_MUTEX_INITIALIZER; //mutex per la muta esclusione del descrittore
//---------------------------------

//-------------------------------
int id=0;    //id univoco per gli oggetti
pthread_mutex_t mutex_id=PTHREAD_MUTEX_INITIALIZER; //mutex per la sincronizzazione dei thread
//-------------------------------------



//------------------------------------+-
struct sockaddr_in client_acq;    //struttura che contiene le informazioni dei client acquirenti connessi!!!
pthread_mutex_t mutex_client_acq=PTHREAD_MUTEX_INITIALIZER; //mutex per la sincronizzazione dei thread acq
//--------------------------------------


//------------------------------------+-
struct sockaddr_in client_ven;    //struttura che contiene le informazioni dei client venditori connessi!!!
pthread_mutex_t mutex_client_ven=PTHREAD_MUTEX_INITIALIZER; //mutex per la sincronizzazione dei thread ven
//--------------------------------------



//-----------------------
pthread_mutex_t management=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t esito=PTHREAD_MUTEX_INITIALIZER;

struct oggetto *inserisci_asta; //oggetto da inserire nell'asta
int esito_inserimento=-1; // 1 indica che l'oggetto e' stato inserito 0 indica che l'oggetto non e' stato inserito  -1 inconsistenza
//-------------------------


//-----------------------------
struct oggetto *asta;	//puntatore globale dell'asta
//-------------------------------

// Funzione (THREAD) gestione Acquirente  il parametro di input e' il descrittore
void *acquirente(void* SD)
{
	struct oggetto *object,*temp ;
	struct oggetto object1 ;
	struct hostent *Host;
	int count,i,pre,contatore,flag=1; 
	time_t scadenza;
	char *t,*p,*nome,*id,*descrizione,*venditore,*minuti,*prezzo,buffer[170],stringa[200],*ora,ident[10];
	int Socket=*(int*)SD; //Importante assegnazione, xche l'area di memoria utilizzata da SD in tutti i  thread e' la stessa!!
	struct sockaddr_in data_net=client_acq; 
	pthread_mutex_unlock(&mutex_client_acq); //Sblocco il gestore di connessione

	printf("Acquirente connesso!!\n");
		
		//scrittura del log
		pthread_mutex_lock(&sinc_log);  //sincronizzazione
	
		time_t tempo=time(NULL);
		ora=asctime(localtime(&tempo));	
		write(log_att,ora,strlen(ora)-1);
		write(log_att," Acquirente ",sizeof(char)*12);

		p=inet_ntoa(data_net.sin_addr);
		Host=gethostbyaddr((char*)&(data_net.sin_addr),4,AF_INET);
		if(Host->h_name != NULL)
		{
			
		write(log_att,Host->h_name,sizeof(char)*strlen(Host->h_name));	
		}else{
		write(log_att,p,sizeof(char)*strlen(p));//inserimento nome simbolico oppure indirizzo IP
		}

		write(log_att," Connesso\n",sizeof(char)*10);
		
		
					
		pthread_mutex_unlock(&sinc_log);

	
	while((count=read(Socket,t=(char*)malloc(170*sizeof(char)),sizeof(char)*170)) != 0)
	{
		
		printf("contatore scritto %d\n",count);

		if(t[0]=='1')  //scelta 1 del menu acquirente
		{	
			temp=asta;
			void lock_reader();
			while(!is_empty(temp))
			{
				contatore=0;

				if(time(NULL)<(temp->scadenza))
				{

				sprintf(ident,"%d",temp->id);

				strcpy(stringa,ident);
				contatore=strlen(ident);
				stringa[contatore]=',';
								
				strcpy(stringa+(contatore)+1,temp->nome_oggetto );
				write(Socket,(void*)stringa,170);
				read(Socket,(void*)buffer,sizeof(char)*1);  //sincronizzazione
				}
				
				temp=temp->next;
			}
			void unlock_reader();
			write(Socket,(void*)stringa,1);//stringa di uscita
		}
		if(t[0]=='2')  //scelta 2 del menu acquirente
		{	
			temp=asta;
			void lock_reader();
			while(!is_empty(temp))
			{
				contatore=0;

				if(time(NULL)>(temp->scadenza))
				{

				sprintf(ident,"%d",temp->id);

				strcpy(stringa,ident);
				contatore=strlen(ident);
				stringa[contatore]=',';
								
				strcpy(stringa+(contatore)+1,temp->nome_oggetto );
				write(Socket,(void*)stringa,170);
				read(Socket,(void*)buffer,sizeof(char)*1);  //sincronizzazione
				}
				
				temp=temp->next;
			}
			void unlock_reader();
			write(Socket,(void*)stringa,1);//stringa di uscita
		}
		if(t[0]=='3')  //scelta 3 del menu acquirente
		{
			p = strtok(t, "-");   //funzione che divide una stringa a seconda del pattern contenuto nel secondo parametro
			id = strtok(NULL, "-");
			flag=1;
			
			temp=asta;
			contatore=0;
			void lock_reader();
			while(!is_empty(temp) && flag)
			{
				

				if(temp->id==atoi(id))
				{
				flag=0;
				sprintf(ident,"%d",temp->id);
				strcpy(stringa,ident);
				contatore=strlen(ident);
				stringa[contatore]=',';
				strcpy(stringa+(contatore)+1,temp->nome_venditore);
				contatore=strlen(temp->nome_venditore)+contatore+1;
				stringa[contatore]=',';

				strcpy(stringa+(contatore)+1,temp->nome_oggetto);
				contatore=strlen(temp->nome_oggetto)+contatore+1;
				stringa[contatore]=',';
			
				strcpy(stringa+(contatore)+1,temp->descrizione);
				contatore=strlen(temp->descrizione)+contatore+1;
				stringa[contatore]=',';


				ora=asctime(localtime(&(temp->scadenza)));
				strcpy(stringa+(contatore)+1,ora);
				contatore=strlen(ora)+contatore;
				stringa[contatore]=',';

				sprintf(ident,"%d",temp->prezzo);
				strcpy(stringa+(contatore)+1,ident);
				contatore=strlen(ident)+contatore+1;
				stringa[contatore]=',';
				
				if(ci_sono_offerte(temp))
				{
					sprintf(ident,"%d",temp->off->prezzo);
					strcpy(stringa+(contatore)+1,ident);
				        
		
				}else   //falsa
				{
					
					strcpy(stringa+(contatore)+1,"0 offerte");
						
				}

				


				
	
				write(Socket,(void*)stringa,170);
				
				}
				
				temp=temp->next;
			}
			void unlock_reader();
			if(flag)
			{
			      write(Socket,"Non ci sono oggetti in asta con questo ID!!",170);	
			}
			

		}
		if(t[0]=='4')  //scelta 4 del menu acquirente
		{	
			
			flag=1;
			p = strtok(t, "-");   //funzione che divide una stringa a seconda del pattern contenuto nel secondo parametro
			id = strtok(NULL, "-");
			nome = strtok(NULL, "-");
			prezzo = strtok(NULL, "-");
			temp=asta;
			void lock_reader();
			while(!is_empty(temp) && flag)
			{
				
				if(atoi(id)==temp->id )//controllo id e se l'oggetto e ancora in asta
				{
					
					flag=0;
					if((time(NULL)<(temp->scadenza)))
					{			
						if(fai_offerta(atoi(prezzo),temp,nome))
						{
						
						write(Socket,"Offerta eseguita con successo",sizeof(char)*30);
											
	//scrittura del log
		pthread_mutex_lock(&sinc_log);  //sincronizzazione
	
		tempo=time(NULL);
		ora=asctime(localtime(&tempo));	
		write(log_att,ora,strlen(ora)-1);
		write(log_att," Acquirente ",sizeof(char)*12);
		//inserimento nome simbolico oppure indirizzo IP
		p=inet_ntoa(data_net.sin_addr);
		Host=gethostbyaddr((char*)&(data_net.sin_addr),4,AF_INET);
		if(Host->h_name != NULL)
		{
			
		write(log_att,Host->h_name,sizeof(char)*strlen(Host->h_name));	
		}else{
		write(log_att,p,sizeof(char)*strlen(p));//inserimento nome simbolico oppure indirizzo IP
		}

		write(log_att," Offerta eseguita con successo\n",sizeof(char)*31);
		
		
					
		pthread_mutex_unlock(&sinc_log);

						}else{
							
						write(Socket,"Offerta non eseguita con successo",sizeof(char)*35);

						}			
					}else   {
						write(Socket,"Oggetto scaduto",sizeof(char)*16);
						}
					
		
				
				}
			temp=temp->next;
			}
			void unlock_reader();
			if(flag==1) write(Socket,"Oggetto non presente",sizeof(char)*21);


			
				
			
		}

			
	}
printf("Acquirente disconnesso!!\n");

		//scrittura del log
		pthread_mutex_lock(&sinc_log);  //sincronizzazione
	
		tempo=time(NULL);
		ora=asctime(localtime(&tempo));	
		write(log_att,ora,strlen(ora)-1);
		write(log_att," Acquirente ",sizeof(char)*12);
		//inserimento nome simbolico oppure indirizzo IP
		p=inet_ntoa(data_net.sin_addr);
		Host=gethostbyaddr((char*)&(data_net.sin_addr),4,AF_INET);
		if(Host->h_name != NULL)
		{
			
		write(log_att,Host->h_name,sizeof(char)*strlen(Host->h_name));	
		}else{
		write(log_att,p,sizeof(char)*strlen(p));//inserimento nome simbolico oppure indirizzo IP
		}

		write(log_att," Disconnesso\n",sizeof(char)*13);
		
		
					
		pthread_mutex_unlock(&sinc_log);


}


// Funzione (THREAD) gestione Venditore il parametro di input e' il descrittore 


void *venditore(void* SD)
{
	struct oggetto *object,*temp ;
	struct oggetto object1 ;
	struct hostent *Host;
	int count,i,pre,contatore; 
	time_t scadenza;
	char *t,*p,*nome,*descrizione,*venditore,*minuti,*prezzo,buffer[170],stringa[200],*ora;
	int Socket=*(int*)SD; //Importante assegnazione, xche l'area di memoria utilizzata da SD in tutti i  thread venditori e' la stessa!!
	struct sockaddr_in data_net=client_ven; 

	pthread_mutex_unlock(&mutex_client_ven); //Sblocco il gestore di connessione

	printf("Venditore connesso!!\n");
		//scrittura del log
		pthread_mutex_lock(&sinc_log);  //sincronizzazione
	
		time_t tempo=time(NULL);
		ora=asctime(localtime(&tempo));	
		write(log_att,ora,strlen(ora)-1);
		write(log_att," Venditore ",sizeof(char)*11);

		//inserimento nome simbolico oppure indirizzo IP
		p=inet_ntoa(data_net.sin_addr);
		Host=gethostbyaddr((char*)&(data_net.sin_addr),4,AF_INET);
		
		if(Host->h_name != NULL)
		{
		write(log_att,Host->h_name,sizeof(char)*strlen(Host->h_name));	
		}else{
		write(log_att,p,sizeof(char)*strlen(p));//inserimento nome simbolico oppure indirizzo IP
		}

		write(log_att," Connesso\n",sizeof(char)*10);
		
		
					
		pthread_mutex_unlock(&sinc_log);

	
	while((count=read(Socket,t=(char*)malloc(170*sizeof(char)),sizeof(char)*170)) != 0)
	{
		
		printf("contatore scritto %d\n",count);

		if(t[0]=='1')  //scelta 1 del menu venditore
		{	
			p = strtok(t, "-");   //funzione che divide una stringa a seconda del pattern contenuto nel secondo parametro
			
			nome = strtok(NULL, "-");
			
			descrizione = strtok(NULL, "-");
			
			venditore = strtok(NULL, "-");
			
			prezzo = strtok(NULL, "-");
			
			minuti = strtok(NULL, "-");
			
			
			//sincronizzo l'incremento dell'identificativo oggetto
			pthread_mutex_lock(&mutex_id);
			i=id;
			id++;
			pthread_mutex_unlock(&mutex_id);
			
			scadenza=time(NULL);
			scadenza=scadenza+(60*atoi(minuti));
	
			pre=atoi(prezzo);
			object=create_object(nome,descrizione,pre,scadenza,venditore,i);

			//inserisco l'oggetto al management


			pthread_mutex_lock(&mutex);

				inserisci_asta=object; 
				pthread_mutex_unlock(&management);
				pthread_mutex_lock(&esito);
				if(esito_inserimento == 1)
				{
					write(Socket,"Oggetto inserito correttamente",sizeof(char)*31);

//scrittura del log
		pthread_mutex_lock(&sinc_log);  //sincronizzazione
	
		tempo=time(NULL);
		ora=asctime(localtime(&tempo));	
		write(log_att,ora,strlen(ora)-1);
		write(log_att," Venditore ",sizeof(char)*11);
		//inserimento nome simbolico oppure indirizzo IP
		p=inet_ntoa(data_net.sin_addr);
		Host=gethostbyaddr((char*)&(data_net.sin_addr),4,AF_INET);
		
		if(Host->h_name != NULL)
		{
		write(log_att,Host->h_name,sizeof(char)*strlen(Host->h_name));	
		}else{
		write(log_att,p,sizeof(char)*strlen(p));//inserimento nome simbolico oppure indirizzo IP
		}

		write(log_att," Oggetto inserito correttamente\n",sizeof(char)*32);
		
		
					
		pthread_mutex_unlock(&sinc_log);

				}else{
					write(Socket,"Oggetto inserito non corrttamente",sizeof(char)*34);
				}
					
				
			pthread_mutex_unlock(&mutex);
		
	
	
		}
		if(t[0]=='2')  //scelta 2 del menu venditore
		{	
			
			p = strtok(t, "-");   //funzione che divide una stringa a seconda del pattern contenuto nel secondo parametro
			
			nome = strtok(NULL, "-");
			
			
			temp=asta;
			void lock_reader();
			while(!is_empty(temp))
			{
				
				if(strcmp(nome,temp->nome_venditore)==0 )
				{
				//invia informazioni al client
				
				strcpy(stringa,temp->nome_venditore);
				contatore=strlen(temp->nome_venditore);
				stringa[contatore]=',';

				strcpy(stringa+(contatore+1),temp->nome_oggetto);
				contatore=strlen(temp->nome_oggetto)+contatore+1;

				stringa[contatore]=',';
				strcpy(stringa+(contatore)+1,temp->descrizione);
				contatore=strlen(temp->descrizione)+contatore+1;
				stringa[contatore]=',';

				ora=asctime(localtime(&(temp->scadenza)));

				strcpy(stringa+(contatore)+1,ora);



				if(ci_sono_offerte(temp))
				{
					contatore=strlen(ora)+contatore+1;
					stringa[contatore]=',';

					sprintf(prezzo,"%d",temp->off->prezzo);
					strcpy(stringa+(contatore)+1,prezzo);
					contatore=contatore+strlen(prezzo)+1;
					stringa[contatore]=',';

					strcpy(stringa+(contatore)+1,temp->off->nome_offerente);
					
					

					contatore=strlen(temp->off->nome_offerente)+contatore+2; 						

								
				}else   //falsa
				{
					contatore=strlen(ora)+contatore+1;
					stringa[contatore]=',';
					strcpy(stringa+(contatore)+1,"0 offerte");
					contatore=9+contatore+2; 							
				}

				

				
				
	
				write(Socket,(void*)stringa,contatore);
				read(Socket,(void*)buffer,sizeof(char)*1);  //sincronizzazione

				}
				temp=temp->next;
				
			}
			void unlock_reader();

			write(Socket,"\0",1);
			free(t); //lo spazio di nn mi serve e quindi lo dealloco!!
			
		}

			
	}
//scrittura del log
		pthread_mutex_lock(&sinc_log);  //sincronizzazione
	
		tempo=time(NULL);
		ora=asctime(localtime(&tempo));	
		write(log_att,ora,strlen(ora)-1);
		write(log_att," Venditore ",sizeof(char)*11);

		//inserimento nome simbolico oppure indirizzo IP
		p=inet_ntoa(data_net.sin_addr);
		Host=gethostbyaddr((char*)&(data_net.sin_addr),4,AF_INET);
		
		if(Host->h_name != NULL)
		{
		write(log_att,Host->h_name,sizeof(char)*strlen(Host->h_name));	
		}else{
		write(log_att,p,sizeof(char)*strlen(p));//inserimento nome simbolico oppure indirizzo IP
		}
	
		write(log_att," Disconnesso\n",sizeof(char)*13);
		
		
					
		pthread_mutex_unlock(&sinc_log);


printf("Venditore diconnesso!!\n");
}



// Funzione gestione Oggetti ASTA con THREAD:
void *OBJECT_MAN() // MAN = Management.
{
	pthread_mutex_lock(&management);  //inizializzazione a 0
	pthread_mutex_lock(&esito);	 //inizializzazione a 0

	while (1)
	{	
		pthread_mutex_lock(&management);

			void lock_writer(); //funzione di sincronizzazione
			asta=add_object(asta,inserisci_asta,&esito_inserimento);  
			void unlock_writer(); //funzione di sincronizzazione

		pthread_mutex_unlock(&esito);

	}

}


// Funzione Connessione Acquirente con THREAD:
void *CONN_ACQ(void* porta)
{
  int accsd_A, sd_A;
  int val=1;
  struct sockaddr_in serv_ind, cliente;
  socklen_t lung;

  // Var. per i  thread	
  pthread_t tid;


      // CAST:
     int portaA = *((int*)porta);


     // Crea socket per Acquirente:
     if ( (sd_A = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
     {     
	perror("Errore nella creazione del Socket per l'Acquirente");
     	exit(-1);
     }

     // rende il socket riusabile
     setsockopt(sd_A,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

     // indirizzo ip
     // pulizia ind
     memset((void *)&serv_ind, 0, sizeof(serv_ind)); 
     


     // ind di tipo INET
     serv_ind.sin_family = AF_INET;  

     serv_ind.sin_port = htons(portaA);  
 
     // connessioni da ogni ip       
     serv_ind.sin_addr.s_addr = htonl(INADDR_ANY);    

 
     // bind
     if (bind(sd_A, (struct sockaddr *)&serv_ind, sizeof(serv_ind)) < 0) 
     {
     	perror("Errore nella bind");
     	exit(-1);
     }


     // listen
     if (listen(sd_A, BACKLOG) < 0 ) 
     {
      	perror("Errore nella Listen Venditore");
     	exit(-1);
     }

     printf ("\n\n\n THREAD Acquirente in ascolto sulla porta %d\n",portaA);
     

     //lung della giusta dimensione
     lung = sizeof(struct sockaddr_in);


	pthread_mutex_lock(&mutex_client_acq); //inizializzo il mutex per il passaggio al clinet della struttura client_acq!!!!

     // accetta connessione
     while (1) 

     {
	
       if ((accsd_A = accept(sd_A, (struct sockaddr *)&client_acq, &lung))<0) 
	{
	         perror("Errore nella accept");
	         exit(-1);
	}
        
       
	// Crea THREAD
    	
        if(pthread_create(&tid,NULL,acquirente,(void*) &accsd_A) != 0)
        {     
		perror("Errore nella creazione del THREAD");
     		exit(-1);
        }

       pthread_mutex_lock(&mutex_client_acq); //attendo il thred client che si memorizza le variabili client_acq

     }// Fine WHILE

}


// Funzione Connessione Venditore con THREAD:
void *CONN_VEND(void* porta) 
{
  int accsd_V, sd_V;
  int val=1;
  struct sockaddr_in serv_ind, cliente;
  socklen_t lung;

 // Var. per i  thread	
 pthread_t tid;
 
  
      // CAST:
     int portaV = *((int*)porta);

     // Crea socket per Venditore:
     if ( (sd_V = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
     {     
	perror("Errore nella creazione del Socket per il Venditore");
     	exit(-1);
     }
     
     // rende il socket riusabile
     setsockopt(sd_V,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

     // indirizzo ip
     // pulizia ind
     memset((void *)&serv_ind, 0, sizeof(serv_ind)); 
     

     // ind di tipo INET
     serv_ind.sin_family = AF_INET;  

     serv_ind.sin_port = htons(portaV);  
 
     // connessioni da ogni ip       
     serv_ind.sin_addr.s_addr = htonl(INADDR_ANY);    

 
     // bind
     if (bind(sd_V, (struct sockaddr *)&serv_ind, sizeof(serv_ind)) < 0) 
     {
     	perror("Errore nella bind");
     	exit(-1);
     }


     // listen
     if (listen(sd_V, BACKLOG) < 0 ) 
     {
      	perror("Errore nella Listen Venditore");
     	exit(-1);
     }

     printf ("\n\n\n THREAD Venditore in ascolto sulla porta %d\n",portaV);
     

     //lung della giusta dimensione
     lung = sizeof(struct sockaddr_in);

pthread_mutex_lock(&mutex_client_ven); //inizializzo il mutex per il passaggio al clinet della struttura client_ven!!!!
     // accetta connessione
	
     while (1) 
     {
       if ((accsd_V = accept(sd_V, (struct sockaddr *)&client_ven, &lung))<0) 
	{
	         perror("Errore nella accept");
	         exit(-1);
	}


	// Crea THREAD    
        if(pthread_create(&tid,NULL,venditore,(void*) &accsd_V) != 0)
        {     
		perror("Errore nella creazione del THREAD");
     		exit(-1);
        }
     	pthread_mutex_lock(&mutex_client_ven); //attendo il thred client che si memorizza le variabili client_acq
     }// Fine WHILE


}




// **************************************** M A I N *******************************************

int main(int argc, char *argv[])
{
     int fd,fdw,l,scritti,letti;
     
     
     char buffer[MAX],datil[MAX],indcli[128];
     
     pid_t pid;
     
     char stringa[MAX], stringa2[MAX];
     time_t    now;
     struct    tm     *tnow;   
    // struttura definita in &lt;time.h&gt;
     char tempo[24], tempo2[24];
     
     char msg[MAX];
     int msglun2=MAX;



     // Var. per i  thread	
     pthread_t tid1, tid2,tid3;
     int porta_acq, porta_vend;


// ******************************************************************************************

			
     if (argc > 1) 	//erre di parametro
     {
         printf("\nErrore\n");
         printf("Attivare con ./Server porta(1024) porta(1025)\n");
         exit(-1);
     }
     
     if (argc == 1)      // Assegnazione delle porte standard
     {
	//assegnazione porte standard
       printf("Sono state assegnate le porte standard\n acquirente 1024 \n venditore 1025\n");
       porta_acq=STDPORT_A;
       porta_vend=STDPORT_V;  
	
     }else		//assegnazione delle porte prese in input
	{
    		 // Porta Acquirente:
    		 porta_acq = atoi(argv[1]);
		// Porta Venditore:
    		 porta_vend = atoi(argv[2]);
	}

    // Apertura file di log
    log_att=open("./attivity_log_file", O_WRONLY | O_CREAT | O_APPEND);

    //creazione del thread che gestisce gli oggetti OBJECT_MANAGER
     if(pthread_create(&tid3,NULL,OBJECT_MAN,NULL) != 0)
     {     
	perror("Errore nella creazione del THREAD OBJECT_MAN");
     	exit(-1);
     }

     // Crea THREAD Acquirente:   
     if(pthread_create(&tid1,NULL,CONN_ACQ,(void*)&porta_acq) != 0)
     {     
	perror("Errore nella creazione del THREAD ACQUIRENTE");
     	exit(-1);
     }


     

     // Crea THREAD Venditore:   
     if(pthread_create(&tid2,NULL,CONN_VEND,(void*)&porta_vend) != 0)
     {     
	perror("Errore nella creazione del THREAD VENDITORE");
     	exit(-1);
     }

  
     
     
     
	//creazione dell'asta
	create_list(asta);


     // Creazione THREAD di attesa per far attendere il main:
     if(pthread_join(tid1,NULL) != 0)
     {     
	perror("Errore nella creazione del THREAD JOIN dell'ACQUIRENTE");
     	exit(-1);
     }
}
