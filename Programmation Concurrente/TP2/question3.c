#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

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

void *print_prime_factors(void* n)
{
	uint64_t nb = (uint64_t)n;
	printf("%ju : ",nb);
	print_prime_factors_recursive(nb);
	printf("\n");
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	FILE *fi;
	uint64_t nb1;
	uint64_t nb2;
	
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
		char line1[128];
		char line2[128];
		while(fgets(line1,sizeof(line1), fi) != NULL)
		{
			nb1 = (uint64_t) atoll(line1);
			nb2 = -1;
			if(fgets(line2,sizeof(line2), fi) != NULL)
			{
				nb2 = (uint64_t) atoll(line2);
			}
			
			crdu = pthread_create(&tid1, NULL, print_prime_factors,(void*)nb1);
			if(crdu != 0)
			{
				perror(NULL);
				exit(errno);
			}
			if( nb2 != -1)
			{
				crdu = pthread_create(&tid2, NULL, print_prime_factors,(void*)nb2);
				if(crdu != 0)
				{
					perror(NULL);
					exit(errno);
				}
				pthread_join(tid2,NULL);
			}
			pthread_join(tid1,NULL);
			
			
		}
		fclose (fi);
	 }

    return 0;
}
