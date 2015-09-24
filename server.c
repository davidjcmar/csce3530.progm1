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
	int boolean=0;

	memset(host,'\0',256);
	memset(url,'\0',MESLEN-256);

	/* if message does not end in '/' */
	if (message[strlen(message)-2]!='/')
	{
		/* set last char to '/' temporarily */
		message[strlen(message)-1]='/';
		boolean=1; // set flag
	}
	/* pull host until '/' */
	for (i=0;message[i]!='/';i++)
		host[i]=message[i];

	message[strlen(message)-1]='\n';
	/* pull url until newline */
	for(j=0;message[i]!='\n';i++,j++)
		url[j]=message[i];

	/* set end of string char */
	url[strlen(url)-1]='\0';
	if (strlen(url)==0 && boolean==1)
		url[0]=='/';
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

	shutdown (sock_descript,2);
	shutdown (sock_cli_ser,2);
	return 0;
}