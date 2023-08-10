#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
int k,sock_dec;
struct sockaddr_in server;
char buf[100];


sock_dec=socket(AF_INET,SOCK_DGRAM,0);
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=3003;
if(sock_dec==-1)
{
printf("There is an error in socket creation\n");
}
printf("enter the msg\n");

fgets(buf,100,stdin);
k=sendto(sock_dec,buf,100,0,(struct sockaddr*)&server,sizeof(server));

if(k==-1)
{
printf("there is some error in sending\n");
}

close(sock_dec);
return 0;
}







