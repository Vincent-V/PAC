#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "oracle.h"

#define NOMBRE_DE_BLOCS 2 
#define SIZE_BLOCK  8


// les blocs à decrypter
unsigned char blocs_chiffres[NOMBRE_DE_BLOCS * SIZE_BLOCK] =     
  {
  0xC6, 0x8C, 0x64, 0x32, 0x82, 0x64, 0xA5, 0x12,
  0x78, 0x72, 0x9F, 0x8B, 0xA3, 0x70, 0x6A, 0x85
  };

// vecteur d'initialisation
unsigned char iv[SIZE_BLOCK] = {0x08, 0x04, 0x02, 0x01, 0x10, 0x20, 0x40, 0x80};

unsigned char clair[NOMBRE_DE_BLOCS * SIZE_BLOCK];

int main(void) 
{
  int i,num_bloc,octet_courant,reponse_oracle = 0 ;
  
  printf("Oracle situe sur %s\n",ORACLE);
  
  if (ouvre_oracle(ORACLE)) { 	/* contact avec l'oracle */
    return EXIT_FAILURE;   
  }
  
	for(num_bloc = 0; num_bloc < NOMBRE_DE_BLOCS; num_bloc++) {
		
		// ci-dessous le bloc chiffre choisi pour mener l'attaque
		unsigned char question[2*SIZE_BLOCK] = 
		  {
		    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
		  };


		/*printf("Bloc forge : ");
		affiche_bloc(question,SIZE_BLOCK);
		printf("\n") ;
		printf("Bloc chiffre : ");
		affiche_bloc(blocs_chiffres,SIZE_BLOCK);
		printf("\n") ;*/
		
		printf("\n");
		memmove(question+SIZE_BLOCK*sizeof(char),&blocs_chiffres[num_bloc*SIZE_BLOCK],SIZE_BLOCK*sizeof(char));
		
		for (octet_courant = SIZE_BLOCK - 1; octet_courant >= 0; octet_courant--) {
      printf("Calcul bloc : %d/%d octet : %d/%d\n",(num_bloc+1), NOMBRE_DE_BLOCS, (octet_courant+1), SIZE_BLOCK);

      for (i = 0; i < 256 && reponse_oracle != 1 ; i++) {
          question[octet_courant] = i ;
          //affiche_bloc(question, SIZE_BLOCK);
          reponse_oracle = interroge_oracle(question) ;
          //printf("| %d |\n", reponse_oracle);
      }

      char d = question[octet_courant] ^ (SIZE_BLOCK - octet_courant);
      
      if(num_bloc > 0) // Utilisation du bloc chiffré precedent
          clair[num_bloc * SIZE_BLOCK + octet_courant] = d ^ blocs_chiffres[octet_courant];
      else // Utilisation du vecteur d'initialisation car c'est le premier bloc
          clair[num_bloc * SIZE_BLOCK + octet_courant] = d ^ iv[octet_courant];

      if (octet_courant > 0) {
          for (i = octet_courant + 1; i < SIZE_BLOCK; i++) {
              question[i] = question[i] ^ (SIZE_BLOCK - octet_courant);
              question[i] = question[i] ^ (SIZE_BLOCK - (octet_courant - 1));
          }

          question[octet_courant] = d ^ (SIZE_BLOCK - (octet_courant - 1));
          reponse_oracle = 0;
      }
    } 
	 }

    printf("Message decrypte (hexa):\n ");
    for(i = 0; i < NOMBRE_DE_BLOCS * SIZE_BLOCK; i += 2) {
        printf("%X%X ", clair[i], clair[i+1]);
    }
    printf("\n");
    
    printf("Message decrypte:\n \"");
    for(i = 0; i < NOMBRE_DE_BLOCS * SIZE_BLOCK; i++) {
        printf("%c", clair[i]);
    }
    printf("\n");

  ferme_oracle(); /* cloture de la connexion */
  return EXIT_SUCCESS;
}
