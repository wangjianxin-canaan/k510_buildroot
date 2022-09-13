#export PATH="/home/wangjianxin/wjx/k510_buildroot/toolchain/nds64le-linux-glibc-v5d/bin:${PATH}"
CROSS_COMPILE := /home/wangjianxin/wjx/k510_buildroot/toolchain/nds64le-linux-glibc-v5d/bin/riscv64-linux-

CC	:= $(CROSS_COMPILE)gcc
C++	:= $(CROSS_COMPILE)g++
OBJDUMP	:= $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
AR	:= $(CROSS_COMPILE)ar
AS	:= $(CROSS_COMPILE)as
LD	:= $(CROSS_COMPILE)ld

#s_d  ----server device
#s_p  ---server  pc
#c_d  ---client device 
#c_p  ---client pc 
all: s_d  s_p  c_d c_p

#s_d  ----server device
s_d: udp_server.c
	${CC}  -o  $@  $^
	
#c_d  ---client device 	
c_d: udp_client.c
	${CC}  -o  $@  $^
	
	
s_p: udp_server.c
	gcc  -o  $@  $^
# client pc	
c_p: udp_client.c
	gcc  -o  $@  $^

	
clean:
	rm -rf s_d  s_p  c_d c_p
	rm -f *.o
	rm -f *.d
	rm -f $(OBJ)

