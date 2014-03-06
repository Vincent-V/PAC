/* xor.c                                       */
/* auteur : Eric Wegrzynowski                      */
/* denière révision   : 28/03/2002                 */ 
/* Usage 
   xor <fichier_input1> <fichier_input2> <fichier_output>  */

#include<stdio.h>

#define data_size 1
#define buf_size 1


int usage(char *progname) {
  fprintf(stderr,"Usage : %s <fichier1> <fichier2> <fichier3>\n",progname);
  fprintf(stderr,"<fichier1> et <fichier2>: fichiers à xorer\n");
  fprintf(stderr,"<fichier1> doit être de taille <= à <fichier2>\n");
  fprintf(stderr,"<fichier3> : fichier résultat\n");
  exit(1);
}

int main(int argc, char *argv[])
{
  FILE *fi1,*fi2,*fo;
  char buf1[buf_size];
  char buf2[buf_size];
  int lu1,lu2;

  if (argc!=4) usage(argv[0]) ;


  if (((fi1=fopen(argv[1],"rb"))!=NULL)
    &&((fi2=fopen(argv[2],"rb"))!=NULL)) {
    if ((fo=fopen(argv[3],"wb"))!=NULL) {
      lu1 = fread(buf1,data_size,buf_size,fi1);
      lu2 = fread(buf2,data_size,buf_size,fi2);
      while (lu1 > 0) {
	buf1[0] ^= buf2[0];
	fwrite(buf1,data_size,buf_size,fo);
	lu1 = fread(buf1,data_size,buf_size,fi1);
	lu2 = fread(buf2,data_size,buf_size,fi2);
      }
      fclose(fo);
    }
    fclose(fi1);
    fclose(fi2);
  }
  else exit(2);
  
  exit(0);
}



