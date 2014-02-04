/*------------------------------------------------------
	Auteur   :	Philippe MATHIEU
	Date     :	15/01/95
	Objectif :
                                                          
Detecter la longueur de la cle d'un fichier crypte avec 
la methode du Xor
(Voir le pgm crypxor.c pour le cryptage)
                                                      
-------------------------------------------------------*/



#include<stdio.h>
#include<stdlib.h>

FILE *entree;
unsigned char tableau[10001]; /* pour ranger de 1 à 10000 caracteres */
int total[256];     /* pour les compter */
int indmax;	/* nb de caracteres du tableau */
int longmax;   /* lg max de la cle : nb maxi de decalages testes */



/* ----------------------------------------------------------------
 on lit le fichier en entree dans le tableau jusqu'a 10000 cars maxi
 si c'est possible 
*/
void lecture_fichier()
{int i;
int c;
	i=0;
	c=getc(entree);
	while (i<=10000 && c != EOF)
	{
		tableau[++i]=c;
		c=getc(entree);
	}
	indmax= i;
}

/* ----------------------------------------------------------------
initialise le tableau de cumul des presences de carcateres pour
qu'il puisse ensuite etre utilise pour compter les frequences de cars
*/
void init_total()
{int i;
	for (i=0; i<=255; i++)
		total[i]=0;
}


/* ----------------------------------------------------------------
recherche le car le plus represente dans le tableau et renvoie 
le nombre de representants  
*/

int rech_car_max()
{int max,car,i;
	max=0; car=0;
	for (i=0;i<=255;i++)
		if (total[i]>max)
		{	car=i;
			max=total[i];
		}
	return max;
}


/* ----------------------------------------------------------------
Analyse le fichier pour tous les decalages possibles en commencant a 1 
renvoie la longueur de la cle qui est obtenue par le decalage donnant
le poucentage de frequence de caracteres le plus evele pour tous les 
decalages effectues
*/

int longueur_cle()
{int decal, j, carmax, decal_max;
double pc, pc_max;

	pc_max=0;	/* poucentage le plus evele pour tous les decalages effectues */
	decal_max=0;    /* decalage ayant donne ce pourcentage */

	for (decal=1 ; (decal <= longmax)  && (decal <= indmax/2) ; decal++)
	{	init_total();
		for (j=1; j<=indmax-decal ; j++) 
		{
			total[tableau[j] ^ tableau[j+decal]]++;
		}
		carmax=rech_car_max();
		pc=(double)(carmax*100)/(double)(indmax-decal);

		if (pc>pc_max)
		{	pc_max=pc;
			decal_max=decal;
		}
/*
		printf("decalage de %3d , ", decal);
		printf(" %4d caracteres traites , ", indmax-decal);
		printf(" %4d cars identiques ", carmax);
		printf(" %2.2lf\% \n",pc);
*/
		printf("%3d \t %2.2lf\n", decal,pc);

	}
	return decal_max;
}


                                                      


/* ---------------------------------------------------------------- */

void main(int argc, char *argv[])
{int taille_cle;

	if (argc!=3)
	{	printf("arg 1 : nom du fichier à traiter \n");
		printf("arg 2 : long maxi du decalage (de la cle) à tester \n");
		exit(1);
	}

	if ((entree=fopen(argv[1] ,"rb")) == NULL)
	{	printf("probleme de fichier \n");
		exit(1);
	}
	sscanf(argv[2],"%d",&longmax);

	lecture_fichier();
	taille_cle = longueur_cle();
/*	printf("La cle est de longueur %d \n",taille_cle);  */

}











