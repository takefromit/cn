#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

void main(){
  int client,y,x,k=5,m=1,p;
  char buffer[1024];
  struct sockaddr_in servAddr;
  socklen_t addrSize; //type definition for length and size values used by socket related parameters
 client=socket(PF_INET,SOCK_STREAM,0) ;
  servAddr.sin_family=AF_INET; //address family
  servAddr.sin_port=htons(5600); //port in network byte order
servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");//internet address
 memset(servAddr.sin_zero,'\0',sizeof servAddr.sin_zero); //clear the contigious memory blocks
y=connect(client,(struct sockaddr*)&servAddr,sizeof servAddr)  ; //connecting

  if(y==-1)
  {
    printf("Error in connection\n");
    exit(1);
  }
while(k!=0)
  {
    if(m<=5)
    {
      printf("Sending %d\n",m);
      
    }
  if(m%2==0)  //successful transmission for even packets
  {
    strcpy(buffer,"frame");
  }
    else{
      strcpy(buffer,"error"); //error for odd packets
      printf("Packet loss\n");
      for(p=1;p<=3;p++)
        {
          printf("Waiting for %d seconds\n",p); //delay of 3 sec for retransmisson
        }
      printf("Retransmitting...\n");
      strcpy(buffer,"frame");
      sleep(3);
    }
    int x= send(client,buffer,19,0);
  if(x==-1)  
  {
    printf("Errror in sending\n");
    exit(1);
  }
    else{
      printf("sent %d\n",m);
    }
  }
   int z=recv(client,buffer,1024,0) ; //recv function
  if(z==-1)
  {
    printf("Error in receiving data\n");
    exit(1);
  }
  k--;
  m++;
  if((strncmp(buffer,"ack",3)==0))
  {
    printf("Acknowledgement receivend for %d \n",m-1);
  }
  
  else{
    printf("ack not received\n");
  }
  close(client);
  
  
  
  
}