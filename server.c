#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
	int sock_descrip;

	sock_descrip=socket(AF_INET,SOCK_STREAM,0);

	if (sock_descrip==-1)
	{
		printf ("Failed to create socket\n");
		return 1;
	}
}