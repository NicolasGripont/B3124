#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
void print_prime_factors_recursive(uint64_t n)
{
	/*uint64_t i,j;
	uint64_t rest = n;
	uint64_t *premiers;
	uint64_t nbPremiers = 1;
	uint64_t sq = sqrt(n)+1;
	uint64_t middle = n/2;
	int result;
	
	
	premiers = (uint64_t*) malloc(sizeof(uint64_t)*middle);
	if(premiers == NULL)
	{
		perror("Erreur malloc");
		exit(-1);
	}
	
	premiers[0] = 2;

	
	printf("%ju : ", n);
	
	while(rest%2 == 0)
	{
		rest = rest/2;
		printf("2 ");
	}

	
	for(i = 3; i < middle && rest != 1; i+=2)
	{
		result = 1;
		uint64_t sqP = (uint64_t) sqrt(i);
		for(j = 0; j < nbPremiers  && premiers[j] < sqP+1 ; j++)
		{
			if(i%premiers[j] == 0)
			{
				result = 0;
				break;
			}
		}
		if(result == 1)
		{
			premiers[nbPremiers] = i;
			nbPremiers ++;
			while(rest%i == 0)
			{
				rest = rest/i;
				printf("%ju ",i);
			}
		}
	} 
	
	if(n == rest)
	{
		printf("%ju",n);
	}
	printf("\n");
	free(premiers);*/
	
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
	printf("%ju : ",n);
	print_prime_factors_recursive(n);
	printf("\n");
}

int main(void)
{
    print_prime_factors(77); // expected result:   77: 7 11
    print_prime_factors(84); // expected result:   84: 2 2 3 7

    // expected result:   429496729675917: 3 18229 7853726291
    //pb quand facteur 1 premier trop grand -> optimiser recherche nb premiers
    print_prime_factors(429496729675917);

	
	
    return 0;
}
