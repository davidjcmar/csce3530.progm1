#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
	int sock_descrip;
	struct sockaddr_in cse01_server;

	sock_descrip=socket(AF_INET,SOCK_STREAM,0);
	if (sock_descrip==-1)
	{
		printf ("Failed to create socket.\n");
		return 1;
	}

	cse01_server.sin_family=AF_INET;
	cse01_server.sin_addr.s_addr=INADDR_ANY;
	cse01_server.sin_port=htons(8888);

	if (bind(sock_descrip,(struct sockaddr *)&cse01_server, sizeof(cse01_server)) < 0)
	{
		printerr ("Bind failed\n");
		return 1;
	}

	printf ("Bind complete\n");

return 0;
}