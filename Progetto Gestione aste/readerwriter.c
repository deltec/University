/* Programma:    gestioneasta.c
* Autore:        Ferdiando Del Trionfo, Cerulli Francesco , Colella francesco
* Data:          16/07/2007
* Descr.:        funzioni che implementano il protocollo di sincronizzazione lettori/scrittori con priorita' scrittori
*
**************************************************************************************************/


pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2=PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t lettura=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t scrittura=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t unoallavolta=PTHREAD_MUTEX_INITIALIZER;
int numscrittori=0;  //contatore scrittori
int numlettori=0;  //contatore lettorii

//funzione che incrementa un lettore
void lock_reader()
{
	pthread_mutex_lock(&unoallavolta);
		pthread_mutex_lock(&lettura);
			pthread_mutex_lock(&mutex2);
				numlettori++;
				if(numlettori==1)
				{
					pthread_mutex_lock(&scrittura);
				}
			pthread_mutex_unlock(&mutex2);
		pthread_mutex_unlock(&lettura);
	pthread_mutex_unlock(&unoallavolta);
}


//funzione che decrementa un lettore
void unlock_reader()
{
	pthread_mutex_lock(&mutex2);
	numlettori--;
	if(numlettori==0)
	{
		pthread_mutex_unlock(&scrittura);
	}
	pthread_mutex_unlock(&mutex2);
	
}


//funzione che incrementa uno scrittore
void lock_writer()
{
	pthread_mutex_lock(&mutex1);
	numscrittori++;
	if(numscrittori==1)
	{
		pthread_mutex_lock(&lettura);
	}
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&scrittura);
	
}

//funzione che decrementa uno scrittore
void unlock_writer()
{
	pthread_mutex_unlock(&scrittura);
	pthread_mutex_lock(&mutex1);
	numscrittori--;
	if(numscrittori==0)
	{
		pthread_mutex_unlock(&lettura);
	}
	pthread_mutex_unlock(&mutex1);
	
}
