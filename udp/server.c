#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
char buf[100];
int sock_dec;
int k;
struct sockaddr_in server,client;
sock_dec=socket(AF_INET,SOCK_DGRAM,0);

if(sock_dec==-1){
printf("Error in socket creation");
}
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=3003;
client.sin_family=AF_INET;
client.sin_addr.s_addr=INADDR_ANY;
client.sin_port=3003;

k=bind(sock_dec,(struct sockaddr*)&server,sizeof(server));

if(k==-1)
{
printf("Error in binding\n");
}
int len=sizeof(server);
k=recvfrom(sock_dec,buf,100,0,(struct sockaddr*)&server,&len);
if(k==-1)
{
printf("Error in receiving the data\n");
}
printf("the message %s",buf);
close(sock_dec);
}








 
 
 
