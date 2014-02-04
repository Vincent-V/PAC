#include<stdio.h>
#include<stdlib.h>
#include<string.h>


FILE *sortie;

int usage(char *progname){
  fprintf(stderr,"Usage : %s <arg1>\n",progname);
  fprintf(stderr,"<arg1> : nom du  fichier à créer avec 256 entiers\n");
  exit(1);
}

int main(int argc, char *argv[])
{	
	int i;
  if (argc!=2) usage(argv[0]);

  sortie=fopen(argv[1] ,"wb");
    
  for (i=0;i<256;i++) {
    fprintf(sortie,"%d\n",(i+68)%256);
  }

  fclose(sortie);
  exit(0);
}
