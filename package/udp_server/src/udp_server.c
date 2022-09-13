

//socket udp 服务端
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#define LOCK_F "/run/udp_temp" 
void dump_buff(char * prompt,char *buff, int len)
{
    int i;
    char *p = buff;
    if(prompt)
        printf("%s :\n",prompt);

    for (i = 0; i < len; ++i)
    {
        if (i%16==0)
        {
            printf("\n%016lx: ",(unsigned long) p+i);
        }
        printf("%02x ",*(p+i));
    }

}


int main(int argc, char *argv[])
{
    //创建socket对象
    int print_lock_fd =0;
	struct flock f_lock;
	
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	unsigned long rec_pack_count=0;

    //创建网络通信对象
    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_port =htons(atoi(argv[1]));
    addr.sin_addr.s_addr=inet_addr("0.0.0.0");

	 open(LOCK_F, O_RDWR|O_CREAT);

	print_lock_fd = open(LOCK_F, O_RDWR|O_CREAT);
	if (print_lock_fd < 0)
	{
		return -1;
	}
	f_lock.l_whence = SEEK_SET;
	f_lock.l_start = 0;
	f_lock.l_len = 0;               /* 0表示整个文件加锁 */
	

    //绑定socket对象与通信链接
    int ret =bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(0>ret)
    {
        printf("bind addr.sin_port=%d %s %d \n",addr.sin_port, argv[1], atoi(argv[1]));
        return -1;

    }
	printf("addr.sin_port=%d %s %d\n", addr.sin_port, argv[1], atoi(argv[1]));
    struct sockaddr_in cli;
    socklen_t len=sizeof(cli);// 注意这个len
    

    while(1)
    {
        char buf[2048] ={0};
		int i=0;
		
		fd_set rfds;
		struct timeval tv;
		int retval;
		FD_ZERO(&rfds);
        FD_SET(sockfd, &rfds);
		retval = select(sockfd+1, &rfds, NULL, NULL, NULL );
		if(retval < 0)
		{
			continue;
		}

		
		
        retval = recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);//这里输入客户端的地址，已经长度的**地址**
        rec_pack_count ++;
		if(rec_pack_count % 3000 == 0)
		{
			int pid=getpid();
			f_lock.l_type = F_WRLCK;        /*选用写琐*/
			//    f_lock.l_type = F_RDLCK;      /*选用读琐*/ 
			fcntl(print_lock_fd, F_SETLKW, &f_lock);
			for(i=0;i<(pid%10);i++)printf(" ");
			printf("pid %d recv count =%ld  retval=%d buf=%lx %x %x %x %x \n", getpid(), rec_pack_count,retval, buf, buf[0],buf[1], buf[2],buf[3]);
			f_lock.l_type = F_UNLCK;
			fcntl(print_lock_fd, F_SETLKW, &f_lock);
		}
      
        for(i=0;i<retval; i++)
    	{
    		if(buf[i]!=buf[0])
			{
				f_lock.l_type = F_WRLCK;        /*选用写琐*/
				fcntl(print_lock_fd, F_SETLKW, &f_lock);
				printf("error pid=%d\n", getpid());
				dump_buff(NULL,buf, retval);
				system("killall a.out");
				f_lock.l_type = F_UNLCK;
				fcntl(print_lock_fd, F_SETLKW, &f_lock);
				break;
			}
    	}
        
    }
    close(sockfd);

}

