#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int main (void)
{
	int sock_descrip, sock_new, c;
	struct sockaddr_in cse01_server, client;

	sock_descrip=socket(AF_INET,SOCK_STREAM,0);
	if (sock_descrip==-1)
	{
		printf ("Failed to create socket.\n");
		return 1;
	}

	cse01_server.sin_family=AF_INET;
	cse01_server.sin_addr.s_addr=INADDR_ANY;
	cse01_server.sin_port=htons(56565);

	if (bind(sock_descrip,(struct sockaddr *)&cse01_server, sizeof(cse01_server)) < 0)
	{
		printf ("Bind failed\n");
		return 1;
	}

	printf ("Bind complete\n");

	listen (sock_descrip, 5);

	printf ("Waiting for connections: \n");
	c=sizeof(struct sockaddr_in);

	if ((sock_new=accept(sock_descrip,(struct sockaddr *)&client, (socklen_t *)&c)) < 0)
	{
		printf ("%d\n",sock_new);
		printf ("Connection not accepted.\n");
		return 1;
	}

	printf ("Connection accepted.\n");
	
return 0;
}
