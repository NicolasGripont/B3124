#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>


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
	printf("%ju : ",n);
	print_prime_factors_recursive(n);
	printf("\n");
}

int main(int argc, char **argv)
{
	FILE *fi;
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
		 char line[128];
		 while(fgets(line,sizeof(line), fi) != NULL) /* read a line */
		  {
			 print_prime_factors((uint64_t) atoll(line));/* write the line */
		  }
		  fclose (fi);
	 }

    return 0;
}
