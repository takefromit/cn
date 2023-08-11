#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERV_TCP_PORT 5035
#define MAX 60

int main(int argc, char *argv[])
{
     int sock_dec, temp_sock_dec,k;
     struct sockaddr_in server, client;
     char buf[MAX],name[MAX];

     sock_dec= socket(AF_INET, SOCK_STREAM, 0);
     server.sin_family = AF_INET;
     server.sin_addr.s_addr = INADDR_ANY;
     server.sin_port = 3003;
     client.sin_family = AF_INET;
     client.sin_addr.s_addr = INADDR_ANY;
     client.sin_port = 3003;

     // printf("\nBinded");
     k=bind(sock_dec, (struct sockaddr *)&server, sizeof(server));
     if(k==-1)
     {
          printf("Error: Failed to bind");
     }
     printf("\nListening...");
     k=listen(sock_dec, 5);
     if(k==-1)
     {
          printf("Error: Failed to listening");
     }
     int len = sizeof(client);
     temp_sock_dec = accept(sock_dec, (struct sockaddr *)&client, &len);
     close(sock_dec);
      if(temp_sock_dec == -1)
      {
          printf("Error: Failed to accept");
      }
     k=recv(temp_sock_dec,name,MAX,0);
     if(k==-1)
     {
          printf("Error: Failed to receive");
     }
     name[k]='\0';

     printf("\nClient message\nFile Name: %s\n", name);

     FILE *f1 = fopen(name, "r");
     if (f1 == NULL)
     {
         k=send(temp_sock_dec,"error",5,0);
         close(temp_sock_dec);
     }
     else{
        while(fgets(buf,MAX,f1))
        {
          k=send(temp_sock_dec,buf,MAX,0);
          if(k==-1)
          {
               printf("Error in sending");
          }
        }
     }
     send(temp_sock_dec,"completed",10,0);
     fclose(f1);
     printf("\nFile Transferred\n");
     return 0;
}

//gcc server.c -o server
// ./server 8000
