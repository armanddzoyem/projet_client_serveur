#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
	// creation de l'espace pour le mesage provenant du serveur
	char buffer[50] = {0};
	struct sockaddr_in servaddr = {0};
	//creation du socket serveur
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	//si la connexion echoue elle va affiche un message d'erreur
	if(sockfd == -1)
	{
		perror("faild to create socket");
		exit(EXIT_FAILURE);
	}
	// configuration du port 
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(12345);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int rc = bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	if(rc == -1)
	{
		perror("faild to bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	socklen_t len = 0;
	// reception du message de client
	int n = recvfrom(sockfd, (char *)buffer, 50, MSG_WAITALL, 0, &len);
	buffer[n] = '\n';
	printf("%s", buffer);
	close(sockfd);
	
	return 0;
}
