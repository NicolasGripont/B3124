#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define MAX_FACTORS 64

pthread_mutex_t mutex_file = PTHREAD_MUTEX_INITIALIZER;

int get_prime_factors(uint64_t n, uint64_t* dest, int nbfactors)
{
	uint64_t sq = sqrt(n)+1;
	uint64_t i;
	for ( i = 2; i < sq; i++ )
	{
		if (n%i == 0)
		{
			dest[nbfactors++] = i;
			nbfactors = get_prime_factors((uint64_t)n/i,dest,nbfactors);
			return nbfactors;
		}
	}
	dest[nbfactors++] = n;
	return nbfactors;
}

void print_prime_factors(uint64_t n)
{
	uint64_t factors[MAX_FACTORS];
	int j,k;
	
	k = get_prime_factors(n,factors,0);
		

	printf("%ju: ",n);
	
	for(j=0; j<k; j++)
	{
		printf("%ju ",factors[j]);
	}
	printf("\n");
	
}

void* lecture_fichier(void * file)
{
	FILE *fi = (FILE *) file;
	char line[128];
	char *test;
	while(pthread_mutex_trylock(&mutex_file) == EBUSY);
	test = fgets(line,sizeof(line), fi);
	pthread_mutex_unlock(&mutex_file);
	
	while( test != NULL)
	{
		print_prime_factors((uint64_t) atoll(line));
		
		while(pthread_mutex_trylock(&mutex_file) == EBUSY);
		test = fgets(line,sizeof(line), fi);
		pthread_mutex_unlock(&mutex_file);
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
