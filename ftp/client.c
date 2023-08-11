#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define SERV_TCP_PORT 5035
#define MAX 60
int main()
{
   int sock_dec,k;
   struct sockaddr_in server;
   // struct hostent *server;
   char send[MAX], recvline[MAX], s[MAX], name[MAX];
   sock_dec = socket(AF_INET, SOCK_STREAM, 0);
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = 3003;
   k=connect(sock_dec, (struct sockaddr *)&server, sizeof(server));
   if(k==-1)
   {
      printf("Error in connection creation");
   }

   printf("\nEnter the source file name : \n");
   // scanf("%s", send);
   scanf("%s", name);
   write(sock_dec, name, MAX);
   while ((k = read(sock_dec, recvline, MAX)) != 0)
   {
      printf("%s", recvline);
   }
   close(sock_dec);
   return 0;
}

// gcc client.c -o client
// ./client 8000
