#include<stdio.h>
#include<stdlib.h>

#define data_size 1
#define buf_size 1

#define tab_size 256


int main(int argc, char *argv[])
{
  FILE *fi;
  char *cp;
  unsigned tab[tab_size];
	char buf[buf_size];
  int lu;
	int i;
	for (i = 0; i < 256; i++){
		tab[i] = 0;
	}

  if ((fi=fopen(argv[1],"rb"))!=NULL) {

		lu = fread(buf,data_size,buf_size,fi);
		 while (lu > 0) {
			tab[buf[0]] = tab[buf[0]] + 1;
			lu = fread(buf,data_size,buf_size,fi);

		}	

		fclose(fi);
  }
  else{
	printf("erreur\n");
	 exit(2);
  
}
	for (i = 0; i < 256; i++){
		if (tab[i] != 0){
		printf("[%3d (%c)] : %d\n", i,i, tab[i]);
		}
	}
  exit(0);
}

