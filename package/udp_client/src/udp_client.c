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

int main()
{
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in saddr;
 	memset(&saddr,0,sizeof(saddr));
 	saddr.sin_family = AF_INET;
 	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("10.100.232.133");

	char buff[1024];
	
	for(int i=0; i<2000; i++)
	{
		memset(buff, (i*2)&0xfe, 1024);
		sendto(sockfd, buff, 1024, 0, (struct sockaddr*)&saddr, sizeof(saddr));
		// usleep(1*1000);
	}

	close(sockfd);
	exit(0);
}
