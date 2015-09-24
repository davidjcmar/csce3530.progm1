#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
	int sock_descrip, sock_cse02, sock_inet, c;
	struct sockaddr_in cse01_server,cse01_client, cse02_client;
	char* message, cse02_resp[2048];

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

	if ((sock_cse02=accept(sock_descrip,(struct sockaddr *)&cse02_client, (socklen_t *)&c)) < 0)
	{
		printf ("Connection not accepted.\n");
		return 1;
	}

	printf ("Connection accepted.\n");
	message="Enter a URL for an HTTP request.\n";
	printf ("MESSAGE\n");
	if (send(sock_descrip, message, strlen(message), 0) < 0)
	{
		printf ("Outbound message failed.\n");
		return 1;
	}

	if (recv(sock_descrip, cse02_resp, 2048, 0) < 0)
	{
		printf ("Client response failed.\n");
		return 1;
	}
	printf ("%s\n", cse02_resp);
	
return 0;
}
