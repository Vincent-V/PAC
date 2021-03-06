#include<stdio.h>
#include<stdlib.h>

#define data_size 1
#define buf_size 1


int usage(char *progname) {
  fprintf(stderr,"Usage : %s <a> <b> <fichier1> <fichier2>\n",progname);
  fprintf(stderr,"<a> : valeur de a^(-1)\n");
  fprintf(stderr,"<a> : valeur de b\n");
  fprintf(stderr,"<fichier1> : nom du  fichier à (dé)chiffrer\n");
  fprintf(stderr,"<fichier2> : nom du fichier (dé)chiffré\n");
  exit(1);
}

int main(int argc, char *argv[])
{
  FILE *fi,*fo;
  unsigned char buf[buf_size];
  int lu, a, b;
	int i = 0;
  if (argc!=5) usage(argv[0]) ;

  a = atoi(argv[1]);
  b = atoi(argv[2]);
  if ((fi=fopen(argv[3],"rb"))!=NULL) {
    if ((fo=fopen(argv[4],"wb"))!=NULL) {
      lu = fread(buf,data_size,buf_size,fi);
      while (lu > 0) {
				i++;

				buf[0] = ((buf[0]-b) * a )% 256;
				fwrite(buf,data_size,buf_size,fo);
				lu = fread(buf,data_size,buf_size,fi);
      }
      fclose(fo);
    }
    fclose(fi);
  }
  else exit(2);
  exit(0);
}


