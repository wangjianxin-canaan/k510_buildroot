#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <errno.h>


#define  MAX_BUFFER_SIZE  1024


int main(int argc, char* argv[])
{

    if (argc < 3)
    {
	    printf("use help:%s ip port\n",argv[0]);
	    return -1;
    }	    
    char*pIP = argv[1];
    char*pPort = argv[2];
    //printf("ip:%s,port:%s\n",pIP,pPort);

    struct sockaddr_in addr;
    int sock;

    addr.sin_family     = AF_INET;
    addr.sin_port       = htons(atoi(pPort));
    addr.sin_addr.s_addr = inet_addr(pIP);

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
	   printf("=======socket create error errno %x :%s \n", errno, strerror(errno));
	   return -1;
    }	
	//printf("sock =%x\n", sock);
	


	char sBuffer[MAX_BUFFER_SIZE] = {0};
	static int ncount = 0;
	int nRet = 0;
	for(int i =0;i < 1000;i++)
	{
		memset(sBuffer,(i%100)&0xfe,MAX_BUFFER_SIZE);
		nRet = sendto(sock, sBuffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
		if (nRet < 0)
		{
			printf("sendto error.  nRet %x errno %x : %s\n", nRet, errno, strerror(errno));
			close(sock);
			return -1;
		}
		usleep(1000*10);
	}
	printf("process end \n");

    return 0;
}

