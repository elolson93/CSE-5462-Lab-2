/* client.c using TCP */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

/* client program called with host name where server is run */
main(int argc, char *argv[])
{
	/* Validate input args */
	if(argc != 4) 
	{
		printf("Error: Include host in arguments, port, and local file to transfer in arguments.\n");
		exit(1);
	}

	int sock;                     /* initial socket descriptor */
	int rval;                     /* returned value from a read */
	int num_bytes;		      /* number of bytes of file to be sent */
	char num_bytes_str[4];	      /* number of bytes to string */
	int num_read;		      /* bytes read from file stream */
	struct sockaddr_in sin_addr;  /* structure for socket name setup */
	char * file_name = argv[3];   /* file name */
	char buf[512] = {0};          /* bytes to send to server */
	struct hostent *hp;	      /* host */
	int port = atoi(argv[2]);     /*port number from args */
  
	/* initialize socket connection in unix domain */
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("error openting datagram socket");
		exit(1);
	}

	/* get host */
	hp = gethostbyname(argv[1]);
	if(hp == 0) 
	{
    		fprintf(stderr, "%s: unknown host\n", argv[1]);
    		exit(2);
  	}

  	/* construct name of socket to send to */
  	bcopy((void *)hp->h_addr, (void *)&sin_addr.sin_addr, hp->h_length);
  	sin_addr.sin_family = AF_INET;
  	sin_addr.sin_port = htons(port); /* fixed by adding htons() */
  
  	/* establish connection with server */
  	if(connect(sock, (struct sockaddr *)&sin_addr, sizeof(struct sockaddr_in)) < 0) 
	{
    		close(sock);
    		perror("error connecting stream socket");
    		exit(1);
  	}
  
  	/* Open file for transfer */
  	FILE *fp = fopen(file_name,"r");
  	if(fp==NULL) 
	{
    		perror("File opern error");
    		exit(1);  
  	}

  	/* Read number of bytes in file, rewind file to start index */  
	fseek(fp, 0L, SEEK_END);
	num_bytes = ftell(fp);
	rewind(fp);
        
	/* convert number of bytes to string to send */
	sprintf(num_bytes_str, "%d", num_bytes);
	
	/* Send file size in 4 bytes */
	send(sock, num_bytes_str, 4, 0);

	/* Send file name in 20 bytes */
	send(sock, file_name, 20, 0); 

	while(1)
	{
	  	/* Read file in chunks of 512 bytes */
		num_read = fread(buf,1,512,fp);

		/* If read was success, send data. */
		if(num_read > 0)
		{
			printf("Sending \n");
		   	send(sock, buf, num_read, 0);
		}

		/* Handle end of file or read error */
		if (num_read < 512)
		{
		  	if (feof(fp)) 
		  	{
		  		break;
		  	}
		  	else if (ferror(fp))
		  	{
				perror("Error reading\n");
				exit(1);
		  	}
		}
	}
	
	return(0); 
}
