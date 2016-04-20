
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define MAX_FACTORS 64
#define MAX_STOCKAGE 1000


typedef struct stockage 
{
	uint64_t nombre;
	uint64_t* facteurs;
	int nbFacteurs;
} stockage;

pthread_mutex_t mutex_file = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_ecran = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_tableau = PTHREAD_MUTEX_INITIALIZER;
stockage stock[MAX_STOCKAGE];
int nbStockage = 0;


int get_prime_factors(uint64_t n, uint64_t* dest, int nbfactors, uint64_t debut)
{
	uint64_t sq = sqrt(n)+1;
	uint64_t i;
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
stockage* find_factors(uint64_t n)
{
    int i;
    for(i = 0; i < nbStockage; i++)
    {
        if(stock[i].nombre == n)
        {
            return &stock[i];
        }
    }
    return NULL;
}

void free_stockage()
{
    int i;
    for(i = 0; i < nbStockage; i++)
    {
        free(stock[i].facteurs);
    }
}

void print_prime_factors(uint64_t n)
{
    stockage *s;
    uint64_t *f;
	int j,k;

    while(pthread_mutex_trylock(&mutex_tableau) == EBUSY);
    s = find_factors(n);
    if(s == NULL)
    {
        pthread_mutex_unlock(&mutex_tableau);
        f = (uint64_t *) malloc(sizeof(uint64_t)*MAX_FACTORS);
        if(f == NULL)
        {
            perror(NULL);
            free_stockage();
            exit(errno);
        }

        k = get_prime_factors(n,f,0, 2);
		if(nbStockage < MAX_STOCKAGE)
        {
			while(pthread_mutex_trylock(&mutex_tableau) == EBUSY);
			
			stock[nbStockage].facteurs = f;
			stock[nbStockage].nombre = n;
			stock[nbStockage].nbFacteurs = k;
			nbStockage++;
			pthread_mutex_unlock(&mutex_tableau);
		}
    }
    else
    {
        k = s->nbFacteurs;
        f = s->facteurs;
        pthread_mutex_unlock(&mutex_tableau);
    }

	
	while(pthread_mutex_trylock(&mutex_ecran) == EBUSY);

	printf("%ju: ",n);
	
	for(j=0; j<k; j++)
	{
        printf("%ju ",f[j]);
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
    free_stockage();

    return 0;
}
