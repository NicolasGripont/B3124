#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define MAX_FACTORS 64
#define NB_THREAD 4

pthread_mutex_t mutex_file = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_ecran = PTHREAD_MUTEX_INITIALIZER;

int get_prime_factors(uint64_t n, uint64_t* dest, int nbfactors, uint64_t debut)
{
	
	if (debut < 7)
	{
		while (n%2 == 0 && n!=0)
		{
			n = n/2;
			dest[nbfactors++] = 2;
		}
		while (n%3 == 0 && n!=0)
		{
			n = n/3;
			dest[nbfactors++] = 3;
		}
		
		while (n%5 == 0 && n!=0)
		{
			n = n/5;
			dest[nbfactors++] = 5;
		}
		debut = 7;
	}
	uint64_t sq = sqrt(n)+1;
	uint64_t i;
	int increment = 2;
	if ((debut+1)%3 == 0)
	{
		increment = 4;
	}
	
	for ( i = debut; i < sq; i+=increment )
	{
		if (n%i == 0)
		{
			dest[nbfactors++] = i;
			nbfactors = get_prime_factors((uint64_t)n/i,dest,nbfactors, i);
			return nbfactors;
		}
		increment = increment%4 + 2;
	}
	dest[nbfactors++] = n;
	return nbfactors;
}


void print_prime_factors(uint64_t n)
{
	uint64_t factors[MAX_FACTORS];
	int j,k;
	
	k = get_prime_factors(n,factors,0, 2);
		
	while(pthread_mutex_trylock(&mutex_ecran) == EBUSY);

	printf("%ju: ",n);
	
	for(j=0; j<k; j++)
	{
		if(factors[j]<2)
		printf("%ju ",factors[j]);
	}
	printf("\n");
	
	pthread_mutex_unlock(&mutex_ecran);
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
	
	pthread_t tid[NB_THREAD];
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
		/*crdu = pthread_create(&tid1, NULL, lecture_fichier,fi);
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
		}*/
		int k;
		for (k=0; k<NB_THREAD; k++)
		{
			crdu = pthread_create(&tid[k], NULL, lecture_fichier,fi);
			if(crdu != 0)
			{
				perror(NULL);
				exit(errno);
			}
		}
		
		for (k=0; k<NB_THREAD; k++)
		{
			pthread_join(tid[k],NULL);
		}

		fclose (fi);
	 }

    return 0;
}
