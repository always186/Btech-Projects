void setup() {
  // put your setup code here, to run once:
  system("telnetd -l /bin/sh");
  system("ifconfig eth0 172.16.1.55 netmask 255.255.0.0 up"); // IP address and netmask depends on your local network
}
void loop() {
  // put your main code here, to run repeatedly: 
}
