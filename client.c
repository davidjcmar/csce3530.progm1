#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main (void)
{
	int sock_descrip;
	struct sockaddr_in cse01_server;
	int test;

	sock_descrip=socket(AF_INET,SOCK_STREAM,0);

	if (sock_descrip==-1)
	{
		printf ("Failed to create socket\n");
		return 1;
	}

	printf ("SUCCESS\n");

	cse01_server.sin_addr.s_addr = inet_addr("192.168.1.255");
	cse01_server.sin_family = AF_INET;
	cse01_server.sin_port = htons(38);

	if (test=connect(sock_descrip, (struct sockaddr *)&cse01_server, sizeof(cse01_server)) < 0)
	{
		printf ("connect error\n%d\n",test);

		return 1;
	}
	printf ("Connected\n");

	return 0;
}