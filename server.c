#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#define MESLEN 2048
#define PORTNUM 56565

/* parse url from client for GET request */
void parse_client (char* message, char* url, char* host)
{
	printf ("message length: %d\n",strlen(message));
	int i,j;
	memset(host,'\0',256);
	memset(url,'\0',MESLEN-256);
	if (message[strlen(message)-1]!='/')
		message[strlen(message)-1]='/';

	for (i=0;message[i]=='/';i++)
	{
		host[i]=message[i];
	}
	for(j=0;message[i]!='\0';i++,j++)
	{
		url[j]=message[i];
	}
}

int main (void)
{
	int sock_descript, sock_cli_ser, size;
	struct sockaddr_in server, client, proxy;
	char message[MESLEN], url[MESLEN-256], host[256];

	/* create socket to client */
	sock_descript=socket(AF_INET,SOCK_STREAM,0);
	if (sock_descript==-1)
	{
		printf ("Failed to create socket.\n");
		return 1;
	}

	/* set fields in sockaddr_in struct */
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(PORTNUM);

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
	sock_cli_ser=accept(sock_descript, (struct sockaddr *)&client, (socklen_t *)&size);
	if (sock_cli_ser < 0)
	{
		printf ("Connection not accepted.\n");
		return 1;
	}
	printf ("Connection accepted.\n");

	/* communicate with client */
	memset(message,'\0',MESLEN);
	strcpy (message,"Enter a URL for which you want a HTTP request: ");
	write (sock_cli_ser, message, strlen(message));
	memset(message,'\0',MESLEN);
	read (sock_cli_ser, message, MESLEN);
	printf ("message:%s\n", message); // testing
	parse_client (message, url, host);
	printf ("url: %s\thost: %s\n",url,host);
	/* create socket to inet */


	return 0;
}