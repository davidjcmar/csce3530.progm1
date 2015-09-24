#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#define MESLEN 2048
#define PORTNUM 56565

int main (void)
{
	int sock_descrip;
	struct sockaddr_in server;
	char message[MESLEN];

	/* create socket */
	sock_descrip=socket(AF_INET,SOCK_STREAM,0);
	if (sock_descrip==-1)
	{
		printf ("Failed to create socket.\n");
		return 1;
	}

	server.sin_addr.s_addr = inet_addr("129.120.151.94");
	server.sin_family = AF_INET;
	server.sin_port = htons(PORTNUM);

	if (connect(sock_descrip, (struct sockaddr*)&server, sizeof (server)) < 0)
	{
		printf ("Connection failed.\n");
		return 1;
	}

	printf ("Connected.\n");
	memset(message,'\0',MESLEN);
	/* receive hello */
	if (read(sock_descrip, message, MESLEN) == -1)
	{
		printf ("Failed to receive message from server.\n");
		return 1;
	}
	printf ("%s\n", message);
	memset(message,'\0',MESLEN);
	fgets (message, MESLEN, stdin);
	write (sock_descrip, message, strlen(message));
	if (read(sock_descrip, message,MESLEN) == -1)
	{
		printf ("Failed to receive message from server.\n");
	}
	printf ("wieners\n");
	shutdown (sock_descrip,2);
	return 0;
}