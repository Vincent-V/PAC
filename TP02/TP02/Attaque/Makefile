CC = gcc
LIBRARY = -lssl -lcrypto


.PHONY: all clean

all: attaque serveur 

tools.o: tools.c tools.h
	$(CC) -c tools.c

serveur: tools.o serveur.c
	$(CC) -o serveur tools.o serveur.c $(LIBRARY)


oracle.o: oracle.c oracle.h
	$(CC) -c oracle.c 

attaque:  oracle.o tools.o attaque.c
	$(CC) -o attaque oracle.o tools.o attaque.c 
clean:
	rm -f attaque serveur *.o  *~

