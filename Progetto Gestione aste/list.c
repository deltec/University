/* File:          Liste.c
* Autore:        Ferdiando Del Trionfo, Cerulli Francesco , Colella francesco
* Data:          16/07/2007
* Descr.:        Insieme di funzioni che gestiscono liste di oggetti
*
**************************************************************************************************/


struct offerte {
	int prezzo;
	char * nome_offerente;
	struct offerte* next; 

//inserire chi ha fatto l'offerta
};


struct oggetto {
char *nome_oggetto;
char *descrizione;
int prezzo;
time_t scadenza;
char * nome_venditore;
struct oggetto* next;
struct oggetto* pred;
struct offerte* off; //stack offerte
pthread_mutex_t *mutex;
int id;
};

int ci_sono_offerte (struct oggetto * object)
{
	if(object->off != NULL)
	return 1;
	else
	return 0;
}
int fai_offerta(int prezzo,struct oggetto *object,char * nome_offerente)
{
	// sincronizzazione dell'offerta
int esito;
pthread_mutex_lock(object->mutex);
	if( (ci_sono_offerte(object)) && (object->off->prezzo < prezzo))
	{	
		struct offerte *o;
		o=(struct offerte*)malloc(sizeof(struct offerte)); 
		o->prezzo=prezzo;	
		o->nome_offerente=nome_offerente;
		o->next=object->off;
		object->off=o;
		esito=1; //offerta effettuata con successo
	}else if (!(ci_sono_offerte(object)) && (object->prezzo < prezzo) )
	{
		struct offerte *o;
		o=(struct offerte*)malloc(sizeof(struct offerte)); 
		o->prezzo=prezzo;
		o->nome_offerente=nome_offerente;	
		object->off=o;
		esito=1; //offerta effettuata con successo
	}else esito=0; //offerta nn effettuata	
pthread_mutex_unlock(object->mutex);	
return esito;
}

//ritorna 1 se la lista e' vuota 0 altrimenti
int is_empty(struct oggetto *list)
{
	if(list==NULL)
	return 1;
	else
	return 0;
}
void scorri(struct oggetto* lista)
{
	if(lista!=NULL)
	{
		printf("id %d ->",lista->id);
		scorri(lista->next);	
	}
}
//seleziona nella lista l'ultimo oggetto che ha data di scadenza minore del tempo time!!!! ritorna il suo puntatore
//ritorna NULL se la lista e' vouta oppure ha scadenza minore di tutti
struct oggetto *search_time(struct oggetto *list,time_t time)
{
	struct oggetto * temp;
	if(is_empty(list))
	{
		return NULL;		
	}
	else{
		if(list->next==NULL)
		{
 		
			if((difftime(list->scadenza,time))<0)	
			{
				
			return list;
			}
			else{
				
				return list->pred;
			    }
		}

		else //if(list->next!= NULL)
		{
			
			if((difftime(list->scadenza,time))<0)
			{
			
			temp=search_time(list->next,time);	
			return temp;
			}
			else{
				return list->pred;
				
			}
		}

	}		
	
}
//dealloca tutta la lista delle offerte
delete_all_list(struct offerte* off)
{

	if(off!=NULL)
        {
	  delete_all_list(off->next);
	  free((void*) off);	
        }	
}

struct oggetto *create_list()
{
  return NULL;
}

struct oggetto *create_object(char *nome_oggetto,char *descrizione,int prezzo , time_t chiusura , char *venditore,int id)
{
  struct oggetto *ogg;
  ogg=(struct oggetto *)malloc(sizeof(struct oggetto));
  ogg->nome_oggetto=nome_oggetto;
  ogg->descrizione=descrizione;
  ogg->prezzo=prezzo;
  ogg->scadenza=chiusura;
  ogg->nome_venditore=venditore;
  ogg->mutex=malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(ogg->mutex,NULL);
  ogg->off=NULL;
  ogg->next=NULL;
  ogg->pred=NULL;
  ogg->id=id;
  return ogg;
}
//prende in inoput l'oggetto da cancellare e il puntatore alla testa della lista
struct oggetto *delete_object(struct oggetto *list,struct oggetto *ogg) //ritorna la nuova testa della lista
{
   struct oggetto * tempred,*temnext;
   tempred=ogg->pred;
   temnext=ogg->next;
//caso che object ultimo oggetto
   if(temnext==NULL && tempred==NULL)
   {
	//Deaccloca tutto;
	
	free((void*)ogg->nome_oggetto);
	free((void*)ogg->descrizione);
	free((void*)ogg->nome_venditore);
	pthread_mutex_destroy(ogg->mutex);
	delete_all_list(ogg->off);  //implementarla!!!!	
        free((void*)ogg);
	return NULL;
   }
//caso che object sia l'ultimo
   else if(temnext==NULL)
   {
        tempred->next=NULL;
        free((void*)ogg->nome_oggetto);
	free((void*)ogg->descrizione);
	free((void*)ogg->nome_venditore);
	pthread_mutex_destroy(ogg->mutex);
	delete_all_list(ogg->off);  //implementarla!!!!		
	free((void*)ogg);
	return list;
   }

   
   //caso che object sia il primo
   else if(tempred==NULL)
   {

        temnext->pred=NULL;
	free((void*)ogg->nome_oggetto);
	free((void*)ogg->descrizione);
	free((void*)ogg->nome_venditore);
	pthread_mutex_destroy(ogg->mutex);
	delete_all_list(ogg->off);  //implementarla!!!!		
	free((void*)ogg);
	return temnext;
   
   }
	else {
	
       tempred->next=temnext;
       temnext->pred=tempred;
  
	free((void*)ogg->nome_oggetto);
	free((void*)ogg->descrizione);
	free((void*)ogg->nome_venditore);
	pthread_mutex_destroy(ogg->mutex);
	delete_all_list(ogg->off);  //implementarla!!!!		
	free((void*)ogg);
	return list;
	}
}
//aggiunge un oggetto nella lista in ordine di data prende come input la lista e l'oggetto da inserire
//ritorna la nuova testa della lista
struct oggetto *add_object(struct oggetto* list,struct oggetto *object,int *esito)
{
	struct oggetto * temp;
	*esito=0;
	if(is_empty(list)) //lista vuota
	{
	*esito=1;
	return object;

        }
		
	temp=search_time(list,object->scadenza);
	
	if(temp==NULL)
	{
		*esito=1;
		object->next=list;   //ok
   		return object;
	}	

	
		object->next=temp->next;
		object->pred=temp;
		
		if(temp->next!=NULL)
		(temp->next)->pred=object;
		temp->next=object;

		if(temp->pred != NULL)
		{
		*esito=1;
		return list;
		}
		else
		{
		*esito=1;
		return temp;		
		}

}
