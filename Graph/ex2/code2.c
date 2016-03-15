#include <stdio.h>
#include <stdlib.h>

int** cout;

void creeCout(int nbSommets){
    int coutMin = 10;
    int coutMax = 40;
    int i, j, iseed, it;
    iseed = 1;
    cout = (int**) malloc(nbSommets*sizeof(int*));
    for (i=0; i<nbSommets; i++){
        cout[i] = (int*) malloc(nbSommets*sizeof(int));
        for (j=0; j<nbSommets; j++){
            if (i == j) cout[i][j] = coutMax+1;
            else {
                it = 16807 * (iseed % 127773) - 2836 * (iseed / 127773);
                if (it > 0)	iseed = it;
                else iseed = 2147483647 + it;
                cout[i][j] = coutMin + iseed % (coutMax-coutMin+1);
            }
        }
    }
}

void permut(int vus[], int nbVus, int nonVus[], int nbNonVus, int longueur){
    /*
    Variable globale :
     - pour tout couple de sommets (i,j), cout[i][j] = cout pour aller de i vers j
    Entree :
     - nonVus[0..nbNonVus-1] = sommets non visites
     - vus[0..nbVus-1] = sommets visites
    Precondition :
     - nbVus > 0 et Vus[0] = 0 (on commence toujours par le sommet 0)
     - longueur = somme des couts des arcs du chemin <vus[0], vus[1], ..., vus[nbVus-1]>
    Postcondition : affiche les longueurs de tous les circuits commençant par vus[0..nbVus-1] et se terminant par les sommets de nonVus[0..nbNonVus-1] (dans tous les ordres possibles), suivis de 0
     */
    // INSEREZ VOTRE CODE ICI !

	int i;

	if(nbNonVus == 0)
	{
		longueur += cout[vus[nbVus-1]][vus[0]];
		printf("%d\n",longueur);
	}
	else
	{
		for(i=0; i<nbNonVus; i++)
		{
			longueur += cout[vus[nbVus-1]][nonVus[i]];
			vus[nbVus] = nonVus[i];
			nbVus++;
			nbNonVus--;
			nonVus[i] = nonVus[nbNonVus];

			permut(vus,nbVus,nonVus,nbNonVus,longueur);

			nonVus[nbNonVus] = nonVus[i];
			nbNonVus++;
			nbVus--;
			nonVus[i] = vus[nbVus];
			longueur -= cout[vus[nbVus-1]][nonVus[i]];
		}
	}
}

int main(){
    int nbSommets, i;
    scanf("%d",&nbSommets);
    int vus[nbSommets];
    int nonVus[nbSommets-1];
    creeCout(nbSommets);
    for (i=0; i<nbSommets-1; i++)
        nonVus[i] = i+1;
    vus[0] = 0;
    permut(vus,1,nonVus,nbSommets-1,0);
    return 0;
}
