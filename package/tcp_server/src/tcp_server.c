#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  

#include <stdio.h>
#define __USE_GNU
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define  PORT 1234  
#define  BACKLOG 1  

int main()  
{  
	cpu_set_t mask;
	//Set CPU affinity.
	CPU_ZERO(&mask);
	CPU_SET(0, &mask);
	if(sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1)
	{
		exit(EXIT_FAILURE);
	}
		 
	int  listenfd, connectfd;  
	struct  sockaddr_in server;  
	struct  sockaddr_in client;  
	socklen_t  addrlen;  
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
	{  
	perror("Creating  socket failed.");  
	exit(1);  
	}  
	int opt =SO_REUSEADDR;  
	setsockopt(listenfd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));  
	bzero(&server,sizeof(server));  
	server.sin_family=AF_INET;  
	server.sin_port=htons(PORT);  
	server.sin_addr.s_addr= htonl (INADDR_ANY);  
	if(bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1) {  
		perror("Binderror.");  
		exit(1);  
	}     
	if(listen(listenfd,BACKLOG)== -1){  /* calls listen() */  
		perror("listen()error\n");  
		exit(1);  
	}  
	addrlen =sizeof(client);  
	if((connectfd = accept(listenfd,(struct sockaddr*)&client,&addrlen))==-1) {  
		perror("accept()error\n");  
		exit(1);  
	}  
	printf("Yougot a connection from cient's ip is %s, prot is %d\n",inet_ntoa(client.sin_addr),htons(client.sin_port));  
	uint8_t buffer[1000];
	printf("buffer = 0x%lx \n", buffer);
	memset(buffer, 0xa4, 1000);
	// for(uint32_t j=0; j<1000; j++)
	// {
	// 	buffer[j] = j&0xff;
	// }
	for(int i=0; i<100; i++)
	{
		send(connectfd, buffer, 1000, 0);
		usleep(40*1000);
	}
	  
	close(connectfd);  
	close(listenfd);  
	return 0;  
} 