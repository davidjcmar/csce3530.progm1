#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
	int sock_descrip;
	struct sockaddr_in cse01_server;
	int test;
	char message[2048], cse01_resp[2048];

	sock_descrip=socket(AF_INET,SOCK_STREAM,0);

	if (sock_descrip==-1)
	{
		printf ("Failed to create socket\n");
		return 1;
	}

	printf ("SUCCESS\n");

	cse01_server.sin_addr.s_addr = inet_addr("129.120.151.94");
	cse01_server.sin_family = AF_INET;
	cse01_server.sin_port = htons(56565);

	if (test=connect(sock_descrip, (struct sockaddr *)&cse01_server, sizeof(cse01_server)) < 0)
	{
		printf ("connect error\n%d\n",test);

		return 1;
	}
	printf ("Connected\n");
	if (recv(sock_descrip, cse01_resp, 2048, 0) < 0)
	{
		printf ("Inbound message failed.\n");
		return 1;
	}
	printf ("%s\n",cse01_resp);
	fgets(message, sizeof(message), stdin);
	if (send(sock_descrip, message, sizeof(message), 0) < 0)
	{
		printf ("Outbound message failed.\n");
		return 1;
	}
	return 0;
}
