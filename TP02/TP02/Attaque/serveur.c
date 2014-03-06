#include<stdio.h>
#include<stdlib.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include <openssl/evp.h>

#include "tools.h"

#define PORT 2001
#define TailleFileDAttente 5

#define SIZE_BLOCK  8 
#define SIZE_KEY  8
#define TRUE 1
#define FALSE 0




int main(void){

  unsigned char encore = TRUE	;
  unsigned char rep = FALSE ;

  unsigned char key[SIZE_KEY] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  unsigned char iv[SIZE_BLOCK] = {0x08, 0x04, 0x02, 0x01, 0x10, 0x20, 0x40, 0x80};

  int pid,fpid = 0 ;
  int sockd = socket(PF_INET,SOCK_STREAM,0) ;

  if(sockd==-1){
    perror("Erreur lors de la cr\\'eation d'une socket\n") ;
    return -1 ;
  }

  struct sockaddr_in service ;  /* pour coder l'adresse du service */ 

  service.sin_family = AF_INET ; /* c'est la seule famille qui existe
				    pour l'instant */

  service.sin_port = htons(PORT) ; /* Apr\`es avoir v\'erifi\'e dans le
				      fichier /etc/services que ce
				      num\'ero est libre */ 

  service.sin_addr.s_addr =  htonl(INADDR_ANY) ; /* cette macro permet
			                 de dire que le num\'ero IP de
			                 la socket partenaire est
			                 quelconque */

  int res = bind(sockd, (struct sockaddr *) &service, sizeof(service)) ; 

  if(res<0){
    perror("Erreur lors de l'adressage de la prise") ;
    close(sockd) ;
    return -1 ;
  } 
  
  /* pour ne pas cr\'eer des zombies */
  signal(SIGCHLD, SIG_IGN) ;

  /* Initialisation du contexte du serveur */
  EVP_CIPHER_CTX ctx;
  EVP_DecryptInit(&ctx, EVP_des_cbc(),key,iv);

  listen(sockd,TailleFileDAttente) ;
  
  while(1) {
    struct sockaddr_in partenaire ;
    int addrlen = sizeof(service); 
    
     int newsocketd = accept(sockd,(struct sockaddr *) &partenaire, &addrlen) ;
    
    if(newsocketd==-1){
      perror("Erreur lors de l'acceptation de la connexion");
      close(newsocketd) ;
      close(sockd) ;
      return -1 ;
    }
    fpid = fork() ; 

    if(!fpid) {
      
      /* pid = getpid(); */

      /* Pr\'evenir le client que l'on attend son message */
      unsigned char ConnexionEtablie = TRUE ;
      sendto(newsocketd, &ConnexionEtablie, 1, 0, (struct sockaddr *) &partenaire, addrlen);

      /* Attendre 2 blocs */
      unsigned char chiffre[2*SIZE_BLOCK];
      int chiffresize= 2*SIZE_BLOCK ;
      unsigned char clair[2*SIZE_BLOCK];
      int clairsize= 2*SIZE_BLOCK ;
           
      recvfrom(newsocketd,&encore,sizeof(char), 0, 
	       (struct sockaddr *) &partenaire,  &addrlen); 

      while (encore) {
	recvfrom(newsocketd,chiffre,2*SIZE_BLOCK*sizeof(char), 0, 
		 (struct sockaddr *) &partenaire,  &addrlen); 

	affiche_bloc(chiffre,2*SIZE_BLOCK);printf(" | %d | ",chiffresize);
	
	EVP_DecryptUpdate(&ctx, clair, &clairsize, chiffre, chiffresize);  
	
	affiche_bloc(clair,2*SIZE_BLOCK);

	if (EVP_DecryptFinal(&ctx, clair, &clairsize)) 
	  rep = TRUE ;
	else 
	  rep = FALSE ;
	  
    	printf("| %d |\n",rep) ;
	
	sendto(newsocketd, &rep, 1, 0, (struct sockaddr *) &partenaire, addrlen);
	recvfrom(newsocketd,&encore,sizeof(char), 0, 
		 (struct sockaddr *) &partenaire,  &addrlen); 
      }

      close(newsocketd) ;
      close(sockd) ;

      return 0 ;
    }
    close(newsocketd) ;
  }	  
  
  close(sockd) ;
  return 0 ;
}


