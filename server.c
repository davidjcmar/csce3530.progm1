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
//	printf ("message length: %d\n",strlen(message));
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

	message[strlen(message)-1]='\n'; // set last char to check against
	
	/* pull url until newline */
	for(j=0;message[i]!='\n';i++,j++)
		url[j]=message[i];

	/* set end of string char */
//	printf ("url strlen: %d\n",strlen(url));
	if (strlen(url)==0)
		url[0]='/';
	else
		url[strlen(url)]='\0';

}

/* construct HTTP request */
void request (char* message, char* url, char* host)
{
	memset(message,'\0',MESLEN);

	strcpy(message,"GET ");
	strcat(message,url);
	strcat(message," HTTP/1.1\r\n");
	strcat(message,"Host: ");
	strcat(message,host);
	strcat(message,"\r\n\r\n");
}
/* main function */
int main (void)
{
	int sock_descript, sock_cli_ser, sock_inet, size;
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
//	printf ("message:%s\n", message); // testing
	parse_client (message, url, host);
//	printf ("url: %s\thost: %s\n",url,host);
	

	/* create socket to inet */
	sock_inet=socket(AF_INET,SOCK_STREAM,0);
	if (sock_inet==-1)
	{
		printf ("Failed to create socket.\n");
		return 1;
	}
	/* set fields in sockaddr_in struct */
	proxy.sin_family=AF_INET;
	proxy.sin_addr.s_addr=INADDR_ANY;
	proxy.sin_port=htons(PORTNUM+1);
	/* bind socket */
	if (bind(sock_inet,(struct sockaddr*)&proxy, sizeof(proxy)) < 0)
	{
		printf ("Bind failed.\n");
		return 1;
	}

	request(message,url,host);
	write (sock_inet, message, strlen(message));
	read (sock_inet, message, MESLEN);
	printf ("new_message::: %s", message);
	shutdown (sock_inet,2);
	shutdown (sock_descript,2);
	shutdown (sock_cli_ser,2);
	return 0;
}