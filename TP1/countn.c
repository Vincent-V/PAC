#include<stdio.h>
#include<stdlib.h>

#define data_size 1
#define buf_size 1


int main(int argc, char *argv[])
{
  FILE *fi;
  char *cp;
  unsigned *tab;
	char buf[buf_size];
  int lu;
	int i, tab_size,n;
	n = atoi(argv[1]);
	tab_size = 256 * n;
	tab = malloc(tab_size * sizeof(int));

	for (i = 0; i < tab_size; i++){
		tab[i] = 0;
	}

  if ((fi=fopen(argv[2],"rb"))!=NULL) {
		i = 0;
		lu = fread(buf,data_size,buf_size,fi);
		while (lu > 0) {
			tab[buf[0] + (i%n)*256 ] = tab[buf[0] + (i%n)*256 ] + 1;
			i++;
			lu = fread(buf,data_size,buf_size,fi);
		}	
		fclose(fi);
  }
  else{
	printf("erreur\n");
	 exit(2);
  
}
	for (i = 0; i < tab_size; i++){
		if (tab[i] != 0){
			printf("[%c] : %d", i%256, tab[i]);
		}
		if(i % 256 == 0){
			printf("\n");
		}
	}
	printf("\n");
  exit(0);
}

