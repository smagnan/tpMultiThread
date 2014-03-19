#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

#define FALSE 0
#define TRUE 1
#define MODE_PRIME TWO_THREADS_JOIN

enum MODE {NO_THREAD,ONE_THREAD,TWO_THREADS_JOIN};

void print_prime_factors(uint64_t n);
int is_prime(uint64_t p);

static void *task_a (void *p_data)
{
   	puts ("Hello world A");

   	(void) p_data;
   	pthread_exit( NULL);
}

static void *task_b (void *p_data)
{
   	puts ("Hello world B");

   	(void) p_data;
   	pthread_exit( NULL);
}

static void *task_prime_factors (void *p_data)
{
	uint64_t value = *((int*)p_data);
	printf("%llu: ",(value));
        print_prime_factors(value);
        printf("\n");
   
   	(void) p_data;
   	pthread_exit( NULL);
}

int main(int argc, char *argv[])
{
	int mode = MODE_PRIME;

	FILE * file;
	uint64_t value;

	int th1;
	int th2;

	pthread_t ta;
   	pthread_t tb;
   	pthread_t tc;
   	pthread_t td;

   	//puts ("main init");

   	th1 = pthread_create (&ta, NULL, task_a, (void*)1);
   	th2 = pthread_create (&tb, NULL, task_b, (void*)2);

	//printf("test\n");

	file = fopen("numbers.txt","r");
	//printf("%p",file);
	//scanf("%llu",&value);
	//printf("%llu\n",value);

	while(fscanf(file,"%llu",&value)!= EOF)
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
				if(fscanf(file,"%llu",&value)!= EOF)
				{
					pthread_create (&td, NULL, task_prime_factors, &value);
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
	}
	/*fscanf(file,"%llu",&value);
	printf("%d: ",value);
	print_prime_factors(value);
	printf("\n");*/

    return 0;
}

void print_prime_factors(uint64_t n)
{
	int i = 0;
	int n_initVal = n;
	
	// XXX NOTE: l'ajout de i<sqrt(n_initVal) permet d'obtenir un temps 
	// d'exécution beaucoup plus court pour les cas où le nombre possède 
	// un diviseur de très grande taille (>sqrt(n_initVal)
	// Cela évite l'appel à is_prime(params) -> calculs redondants 
	//printf("SQRT: %llf",sqrtl((long double)n_initVal));
	for(i = 2; i<n && /*i<sqrt(n_initVal)*/ i<4294967296; i++) // FIXME problème pour n_initVal trop grand (64b par exemple ...) en attendant remplaçable par sqrt(2^64) = 2^32 ... pour être surs
	{
		while(n%i==0)
		{
			printf("%d ",i);
			n /=i;
		}

		if (n == 1)
		{
			break;
		}
	}

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
