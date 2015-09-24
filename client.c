#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>

int main (void)
{
	int sock_descrip;
	struct sockaddr_in server;
	char* message;

	/* create socket */
	sock_descrip=socket(AF_INET,SOCK_STREAM,0);
	if (sock_descrip==-1)
	{
		printf ("Failed to create socket.\n");
		return 1;
	}

	server.sin_addr.s_addr = inet_addr("129.120.151.94");
	server.sin_family = AF_INET;
	server.sin_port = htons(56565);

	if (connect(sock_descrip, (struct sockaddr*)&server, sizeof (server)) < 0)
	{
		printf ("Connection failed.\n");
		return 1;
	}

	printf ("Connected.\n");

	/* receive hello */
	if (read(sock_descrip, message, 2000) == -1)
	{
		printf ("Failed to receive hello from server.\n");
		return 1;
	}
	printf ("%s\n", message);
	return 0;
}