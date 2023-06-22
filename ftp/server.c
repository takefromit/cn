#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERV_TCP_PORT 5035
#define MAX 60

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, clength;
     struct sockaddr_in serv_addr, cli_addr;
     char str[MAX];

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(SERV_TCP_PORT);

     printf("\nBinded");
     bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
     printf("\nListening...");
     listen(sockfd, 5);

     clength = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clength);
     close(sockfd);

     read(newsockfd, str, MAX);
     str[MAX - 1] = '\0'; // Ensure string termination

     printf("\nClient message\nFile Name: %s\n", str);

     FILE *f1 = fopen(str, "r");
     if (f1 == NULL)
     {
          perror("File not found");
          exit(EXIT_FAILURE);
     }

     char buff[4096];
     size_t n;
     while ((n = fread(buff, sizeof(char), sizeof(buff), f1)) > 0)
     {
          if (write(newsockfd, buff, n) == -1)
          {
               perror("write");
               exit(EXIT_FAILURE);
          }
     }

     fclose(f1);
     printf("\nFile Transferred\n");

     return 0;
}

gcc server.c -o server
// ./server 8000