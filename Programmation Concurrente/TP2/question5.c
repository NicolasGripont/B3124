#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void print_prime_factors_recursive(uint64_t n)
{
	uint64_t sq = sqrt(n)+1;
	uint64_t i;
	for ( i = 2; i < sq; i++ )
	{
		if (n%i == 0)
		{
			printf("%ju ",i);
			print_prime_factors_recursive((uint64_t)n/i);
			return;
		}
	}
	printf("%ju ",n);
}

void print_prime_factors(uint64_t n)
{
	uint64_t nb = (uint64_t)n;
	printf("%ju : ",nb);
	print_prime_factors_recursive(nb);
	printf("\n");
	
}

void* lecture_fichier(void * file)
{
	FILE *fi = (FILE *) file;
	char line[128];
	char *test;
	while(pthread_mutex_trylock(&mutex) == EBUSY);
	test = fgets(line,sizeof(line), fi);
	pthread_mutex_unlock(&mutex);
	
	while( test != NULL)
	{
		print_prime_factors((uint64_t) atoll(line));
		
		while(pthread_mutex_trylock(&mutex) == EBUSY);
		test = fgets(line,sizeof(line), fi);
		pthread_mutex_unlock(&mutex);
	}
	
	
	pthread_exit(NULL);
}



int main(int argc, char **argv)
{
	FILE *fi;
	
	pthread_t tid1, tid2;
	int crdu;
	
	if(argc < 2)
	{
		fi = fopen("question2.txt","r");
	}
	else 
	{
		fi = fopen(argv[1],"r");
	}
	
    if(fi == NULL)
    {
		perror("Erreur ouverture fichier");
		exit(-1);
	}
	else
	{
		crdu = pthread_create(&tid1, NULL, lecture_fichier,fi);
		if(crdu != 0)
		{
			perror(NULL);
			exit(errno);
		}

		crdu = pthread_create(&tid2, NULL, lecture_fichier,fi);
		if(crdu != 0)
		{
			perror(NULL);
			exit(errno);
		}
		pthread_join(tid2,NULL);
		pthread_join(tid1,NULL);

		fclose (fi);
	 }

    return 0;
}
