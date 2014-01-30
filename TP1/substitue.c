/*------------------------------------------------------
	Auteurs  :      Eric WEGRZYNOWSKI
	Date     :	01/01/06
	Objectif :

programme de substitution des lettres d'un fichier.
C'est la technique de  chiffrement la plus simple.
-------------------------------------------------------*/


/* Usage : substitue {+|-}c <arg1> <arg2> <arg3>   */
/* +c pour chiffrer, -c pour déchiffrer            */
/* <arg1> : nom du fichier à (dé)chiffrer          */
/* <arg2> : nom du fichier (dé)chiffré             */
/* <arg3> : nom du fichier de  substitution        */
/* ce dernier fichier contient tous les entiers    */
/* de 0 à 255 une et une seule fois. Le i-ème      */
/* entier du fichier est le code du caractère      */
/* substitué au carctère de code i                 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define data_size 1
#define buf_size 1

FILE *entree, *sortie, *subs;

int table[256]; /* table de substitution */



void init_table(char *option) {
  int i, val;
 
  for (i=0;i<256;i++) {
    fscanf(subs,"%d",&val);
    if (strcmp(option,"+c") == 0)
      table[i]=val;
    else 
      table[val]=i;
    }
}

void traite_fichier(void) {
  int lu;
  unsigned char buf[buf_size];
  
  lu = fread(buf,data_size,buf_size,entree);   
  while (lu > 0){
    buf[0] = (unsigned char) table[(unsigned int) buf[0]];
    fwrite(buf,data_size,buf_size,sortie);
    lu = fread(buf,data_size,buf_size,entree);   
  }
}

int usage(char *progname){
  fprintf(stderr,"Usage : %s {+c|-c} <arg1> <arg2> [<arg3>]\n",progname);
  fprintf(stderr,"option  +c pour chiffrer, -c pour déchiffrer\n");
  fprintf(stderr,"<arg1> : nom du  fichier à (dé)chiffrer\n");
  fprintf(stderr,"<arg2> : nom du fichier (dé)chiffré\n");
  fprintf(stderr,"<arg3>  : nom du fichier contenant la substitution\n");
  exit(1);
}

int main(int argc, char *argv[])
{	
  if (argc!=5) usage(argv[0]);

  if ((entree=fopen(argv[2] ,"rb")) == NULL) {	
    fprintf(stderr,"fichier %s inexistant\n",argv[2]);
    exit(1);
  }

  sortie=fopen(argv[3] ,"wb");

  if ((subs=fopen(argv[4] ,"r")) == NULL) {
    fprintf(stderr,"fichier %s inexistant\n",argv[4]);
    exit(1);
  }
    
  init_table(argv[1]);
  
  fclose(subs);
 
  traite_fichier();

  fclose(entree);
  fclose(sortie);
  exit(0);
}
