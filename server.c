#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int main (void)
{
	int sock_descript, sock_cli_ser, size;
	struct sockaddr_in server, client;
	char* message;

	/* create socket */
	sock_descript=socket(AF_INET,SOCK_STREAM,0);
	if (sock_descript==-1)
	{
		printf ("Failed to create socket.\n");
		return 1;
	}

	/* set fields in sockaddr_in struct */
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(56565);

	/* bind socket */
	if (bind(sock_descript,(struct sockaddr *)&server, sizeof(server)) < 0)
	{
		printf ("Bind failed.\n");
		return 1;
	}

	printf ("Bind successful.\n");

	/* listen */
	listen (sock_descript,3);

	printf ("Ready for incoming connection.\n");
	size=sizeof (struct sockaddr_in);
	while (sock_cli_ser=accept(sock_descript, (struct sockaddr *)&client, (socklen_t *)&size))
	{
		printf ("Connection accepted.\n");

		/* hello client */
		message="Hello client.\n";
		write (sock_cli_ser, message, strlen(message));
	}

	return 0;
}