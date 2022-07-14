#!!
setenv ipaddr 10.100.232.9 ; setenv serverip 10.100.230.4; setenv bootargs "console=ttyS0,115200n8 debug loglevel=7";tftp 0x600000 bootm-bbl.img;tftp 0x2000000 k.dtb;bootm 0x600000 - 0x2000000

make linux-rebuild && make riscv-pk-k510-rebuild


make skeleton-rebuild skeleton-custom-rebuild

