#include<stdio.h>  
#include <stdlib.h>  
#include<unistd.h>  
#include<string.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<netdb.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  

// #include <stdio.h>
// #define __USE_GNU
// #include <stdio.h>
// #include <sched.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <pthread.h>

#define  PORT 1234  
#define  MAXDATASIZE 1000  
#define IP "10.100.232.29"
int count = 0;
int main(int argc, char *argv[])  
{  
	int  sockfd, num;  
	uint8_t  buf[MAXDATASIZE];  
	struct hostent *he;  
	struct sockaddr_in server;  

	if((sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1){  
		printf("socket()error\n");  
		exit(1);  
	}
	
	bzero(&server,sizeof(server));  
	server.sin_family= AF_INET;  
	server.sin_port = htons(PORT);  
	server.sin_addr.s_addr=inet_addr(IP);
	
	if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))==-1){  
		printf("connect()error\n");  
		exit(1);  
	}
	memset(buf, 0x00, MAXDATASIZE);

	while(count < 1000*100)
	{
		if((num=recv(sockfd, buf, MAXDATASIZE, 0)) == -1){  
			printf("recv() error\n");  
			exit(1);  
		}
		
		for(uint32_t j=0; j<num; j++)
		{
			if(buf[j] != 0xa4)
			{
				if(j%16 == 0) printf("count:%d, j:%d \n", count, j);
				printf("0x%x ", buf[j]);
			}
		}
		count += num;
	}
	close(sockfd);  
	return 0;  
} 