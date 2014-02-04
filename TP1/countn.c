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
	printf("1\n");
  if ((fi=fopen(argv[2],"rb"))!=NULL) {
		i = 0;
		lu = fread(buf,data_size,buf_size,fi);
		while (lu > 0) {
			if (buf[0] > 0)
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
printf("2\n");
	for (i = 0; i < 256; i++){
		int j;
		for (j = 0; j < n; j++){
		if (tab[i+ (j*256)] != 0){
			printf("[%3d] : %d\t", i, tab[i+ (j*256)]);
		}
		else{
			printf("[%3d] :   \t", i);
		}
		
}
printf("\n");
	}
	printf("\n");
  exit(0);
}

