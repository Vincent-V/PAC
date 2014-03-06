#include <stdio.h>
 
void affiche_bloc(unsigned char *bloc, int taille) {
  int i;
  
  for (i=0; i<taille; i++)
    printf("%02x",bloc[i]);
/*   printf("\n"); */
}
