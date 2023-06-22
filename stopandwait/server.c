#include <stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

void main(){
  int server,x,newSock,k=5,m=1,p;
  char buffer[1024];
  struct sockaddr_in servAddr;
  struct sockaddr_storage store; //accomodate all supported protocol specific address structure
  socklen_t addrSize;

  //socket creation
  server=socket(PF_INET,SOCK_STREAM,0);
  servAddr.sin_family=AF_INET; //address family
  servAddr.sin_port=htons(5600);//port in network byte order
  servAddr.sin_addr.s_addr=inet_addr("127.0.0.1"); //internet address
  memset(servAddr.sin_zero,"\0",sizeof servAddr.sin_zero);//clear the contigious memory blocks
  bind(server,(struct sockaddr*)&servAddr,sizeof(servAddr));//binding
  if(listen(server,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");
  newSock=accept(server,(struct sockaddr*)&store,&addrSize); //to accept connection

  if(newSock==-1)
  {
    printf("Error in creating socket\n");
    exit(1);
  }
  while(k!=0) //demo for 5 packets
    {
      int y=recv(newSock,buffer,1024,0); //recv function
      if(y==-1)
      {
        printf("Error in receiving\n");
        exit(1);
      }
      if(strncmp(buffer,"frame",5)==0) //comparing received frame
        printf("Received %d successfully\n",m);
      else{
        printf("Frame %d not received \n",m);
      }
      // this is to set that only for even packet the ack is to be send if odd not set simply to set
      if(m%2==0)
      {
        strcpy(buffer,"ack"); //successful ack for even packets
        
      }
      else{
        strcpy(buffer,"kca"); //error for odd packets
        printf("Ack lost\n");

        for(p=1;p<=3;p++)
          {
            printf("Waiting for %d seconds\n",p); //delay of 3 sec for retransmission
          }
        printf("Retransmitting ack..\n");
        strcpy(buffer,"ack");
        sleep(3); //sleep for 3 sec
      }
      printf("Sending ack %d..\n",m);
      int z=send(newSock,buffer,19,0);//send function
      if(z==-1)
      {
        printf("Error in sending\n");
        exit(1);
      }
      k--;
      m++;
      
    }
  close(newSock); //socket close
  
}
