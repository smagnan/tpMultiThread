#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

void print_prime_factors(uint64_t n);

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

int main(int argc, char *argv[])
{
	FILE * file;
	uint64_t value;

	int th1;
	int th2;

	pthread_t ta;
   pthread_t tb;

   puts ("main init");

   th1 = pthread_create (&ta, NULL, task_a, (void*)1);
   th2 = pthread_create (&tb, NULL, task_b, (void*)2);

	//printf("test\n");

	file = fopen("values","r");
	//printf("%p",file);
	//scanf("%llu",&value);
	//printf("%llu\n",value);

	while(fscanf(file,"%llu",&value)!= EOF)
	{
		printf("%d: ",value);
		print_prime_factors(value);
		printf("\n");
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

	for(i = 2; i<n ; i++)
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

	printf("%d ",n);
}
