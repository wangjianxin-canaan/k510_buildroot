

cd /app/dsp_app_new/
./dsp_app simd_umul8_demo.bin
cd /app/udp_client

ifconfig eth0 192.168.0.2
arp -s 192.168.0.1  00:19:56:6F:87:D2


ip="192.168.0.1"
sleep 0.5
while  ! $(ifconfig eth0 | grep RUNNING >/dev/null)  ;do sleep 1; done;
ifconfig 
arp -a ;
sleep 0.2


echo "{"

./udp.out  ${ip} 12345  &
./udp.out  ${ip} 12346  &
./udp.out  ${ip} 12347  &
./udp.out  ${ip} 12348  &
./udp.out  ${ip} 12349  &
./udp.out  ${ip} 12350  &
./udp.out  ${ip} 12351  &
./udp.out  ${ip} 12352  &
./udp.out  ${ip} 12353  &
