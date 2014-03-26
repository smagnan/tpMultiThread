//=============================================================
//	MAGNAN Samuel, SIVANANDAN Bruno
//	B3154
//	Tp MultiThread 2014
//=============================================================

//--------------------------------------------- includes système
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

//---------------------------------------- macros et definitions
#define FALSE 0
#define TRUE 1
#define MAX_FACTORS 64
#define MODE_PRIME TWO_THREADS_JOIN

//-------------------------------------------------------- enums
enum MODE {NO_THREAD,ONE_THREAD,TWO_THREADS_JOIN};

//------------------------------------------ structures et types
typedef struct primeFactors_s 			// Maillon d'une chaine
{
	uint64_t n;
	int size;
	uint64_t factors[MAX_FACTORS]; 
	struct primeFactors_s * next;
} primeFactors_t;

//------------------------------------ déclarations de fonctions
void print_prime_factors(uint64_t n);
int is_prime(uint64_t p);
void print_factors(uint64_t);
int get_prime_factors(uint64_t n, uint64_t * dest);

//-------------------------------------------- variables privées
static pthread_mutex_t mutex;			// Mutex de lecture de fichier
static FILE * file;				// Fichier de données
static primeFactors_t first_factors;	 	// Chaine

//-------------------------------------------- fonctions privées

//static void *task_a (void *p_data)
//{
//   	puts ("Hello world A");
//
//   	(void) p_data;
//   	pthread_exit( NULL);
//}
//
//static void *task_b (void *p_data)
//{
//   	puts ("Hello world B");
//
//   	(void) p_data;
//   	pthread_exit( NULL);
//}

static void *task_prime_factors (void *p_data)
{
	uint64_t value = *((uint64_t*)p_data);
	printf("%llu: ",(value));
        print_prime_factors(value);
        printf("\n");
   
   	(void) p_data;
   	pthread_exit( NULL);
}

static void *task_worker(void *p_data)
{
	file = fopen("numbers.txt","r");
	uint64_t value;
	pthread_mutex_lock(&mutex);
	while(fscanf(file,"%llu",&value)!= EOF)
	{
		 pthread_mutex_unlock(&mutex);
		 printf("%llu: ",value);
                 print_prime_factors(value);
                 printf("\n");
		 pthread_mutex_lock(&mutex);
	}
	pthread_mutex_unlock(&mutex);
}

/*void addFactors(primeFactors_t * pf)
{
	factorsMap=((factorsMap==NULL)?pf:);
	//TODO
	
}*/

//-------------------------------------------------- main
int main(int argc, char *argv[])
{
	int mode = MODE_PRIME;

	uint64_t value;
	uint64_t value2;

	int th1;
	int th2;

	pthread_t ta;
   	pthread_t tb;
   	pthread_t tc;
   	pthread_t td;

	pthread_mutex_init(&mutex,NULL);

	first_factors.next = NULL; 	// initialisation de first -> next
	first_factors.n = -1;		// permet de savoir si on dispose d'un 1er élément ou non (-1)

	//printf("test\n");

	/*primeFactors_t begin;
        begin.n = n;
        begin.size = 0
        begin.next = NULL;

	factorsMap = begin;*/

	file = fopen("numbers.txt","r");
	//printf("%p",file);
	//scanf("%llu",&value);
	//printf("%llu\n",value);

	/*while(fscanf(file,"%llu",&value)!= EOF)
	{	
		int break_val = 0;
		switch(mode)
		{
			case NO_THREAD:
				printf("%llu: ",value);
				print_prime_factors(value);
				printf("\n");
				break;
			case ONE_THREAD:
                                pthread_create (&tc, NULL, task_prime_factors, &value);
				pthread_join (tc,NULL);
				break;
			case TWO_THREADS_JOIN:
				pthread_create (&tc, NULL, task_prime_factors, &value);
				if(fscanf(file,"%llu",&value2)!= EOF)
				{
					pthread_create (&td, NULL, task_prime_factors, &value2);
				}
				else
				{	
					break_val = 1;	
					break;
				}
				pthread_join (tc,NULL);
				pthread_join (td,NULL);
			break;
		}
		if(break_val == 1)
		{
			break;
		}
	}*/

	print_factors(100000000);
		
	/*pthread_create (&ta, NULL, task_worker, (void*)1);
	pthread_create (&tb, NULL, task_worker, (void*)2);
	pthread_join (ta,NULL);
        pthread_join (tb,NULL);
	*/
	pthread_mutex_destroy(&mutex);

        return 0;
}

void print_factors(uint64_t n)
{
	uint64_t factors[MAX_FACTORS];
	
	int j,k;
	//TODO: mutex dans le coin?
	k = get_prime_factors(n,factors);
	
	printf("%llu :", n);
	
	for(j=0; j<k ; j++)
	{
		printf(" %llu",factors[j]);
	}
	printf("\n");
	
}

int get_prime_factors(uint64_t n, uint64_t * dest)
{
	primeFactors_t current = first_factors;
	while(current.next!=NULL) // On recherche dans ce que l'on a déjà trouvé 
	{
		if(current.n == n)
		{
			memcpy(dest,current.factors,sizeof(current.factors));//FIXME ??? ok ou non?
			return current.size; //size: taille du tabeau et donc nombre de facteurs 
		}
		current = *(current.next); // on travaille sur le suivant
	}
	// Si on arrive ici, c'est que l'on a parcouru toute la chaine sans trouver n
	// printf("[n not found in previous values]\n");
	primeFactors_t next;
	next.n = n;
	next.size = 0;
	uint64_t i = 0;
	uint64_t n_initVal = n;
	for(i = 2; i<n ; i++)// remplissage du tableau de factors
        {
                while(n%i==0)
                {
                        next.factors[next.size] = i;
			next.size++;
			n /=i;
                }

                if (n == 1 ||  i>=(uint64_t)sqrt(n_initVal))
                {
                        break; 
                }
        }
	next.next = NULL; // MAJ des pointeurs de maillons	
	current.next = &next;
	memcpy(dest,next.factors,sizeof(next.factors));
	
	return next.size;

	/*int i,j;
	for(i = 0; i<factorsMap[] ;i++)
	{
		for(j=0;j<tabPrimeFactors[i].length;j++)
		{
			if(valuesToFactorize[i]==n)
			{
				dest = tabPrimeFactors[i];
				return tabPrimeFactors[i].length;
			}
		}
	}*/
	// TODO
	/*
	uint64_t i = 0; // XXX à enlever
	uint64_t k;
	int pos = 0;
        uint64_t n_initVal = n;

	primeFactors_t primeFact;
	primeFact.n = n;
	primeFact.size = 0
	primeFact.next = NULL;
	
	for(k = 2; i<n ; k++)
        {
                while(n%k==0)
                {
                   	tabPrimeFactors[i][pos] = k;     
                        n /=k;
			pos++;
                }

                if (n == 1 ||  k>=(uint64_t)sqrt(n_initVal))
                {
                        break;
                }
        }

	dest = tabPrimeFactors[i];
        return tabPrimeFactors[i].length;*/
	return 0; //XXX à virer!!!

}
 

void print_prime_factors(uint64_t n)
{
	uint64_t i = 0;
	uint64_t n_initVal = n;
	
	// XXX NOTE: l'ajout de i<sqrt(n_initVal) permet d'obtenir un temps 
	// d'exécution beaucoup plus court pour les cas où le nombre possède 
	// un diviseur de très grande taille (>sqrt(n_initVal)
	// Cela évite l'appel à is_prime(params) -> calculs redondants 
	for(i = 2; i<n /*&& i<(uint64_t)sqrt(n_initVal)*/ /*i<4294967296*/; i++) // FIXME ?
	{	
		while(n%i==0)
		{
			printf("%llu ",i);
			n /=i;
		}

		if (n == 1 ||  i>=(uint64_t)sqrt(n_initVal)) 
		{
			//printf("--BREAK--[%llu]",i);
			break;
		}
	}
	//printf("OK");

	printf("%llu ",n);
}

int is_prime(uint64_t p)
{
	int i = 0;
	if(!(p%2))
	{
		return FALSE;
	}
	for(i=3;i<sqrt(p);i+=2)
	{
		if(!(p%i))
		{
			return FALSE;
		}
	}
	return TRUE;
}
