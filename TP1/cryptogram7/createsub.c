#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
	FILE *fo;

	int i, a, b;
	char buf[1];
	char bufL[1];
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	bufL[0] = '\n';
	if ((fo=fopen(argv[3],"wb"))==NULL) 
		return -1;
	for (i = 0; i < 256; i++){
		buf[0] = (char)((((i*a) + b) % 256));
		fwrite(buf,1,1,fo);
		fwrite(bufL,1,1,fo);
	}
}
