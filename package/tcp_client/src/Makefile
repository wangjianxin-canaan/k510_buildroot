CROSS_COMPILE := riscv64-linux-

CC	:= $(CROSS_COMPILE)gcc
C++	:= $(CROSS_COMPILE)g++
OBJDUMP	:= $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
AR	:= $(CROSS_COMPILE)ar
AS	:= $(CROSS_COMPILE)as
LD	:= $(CROSS_COMPILE)ld

OBJ ?= tcp_client

$(OBJ): tcp_client.c
	$(C++) $(CFLAGS) $^ -L ./ -Wl,-Bdynamic -g -o $@
	
clean:
	rm -f *.o
	rm -f *.d
	rm -f $(OBJ)

