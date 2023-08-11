#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char buf[100];
    int k, sock_dec, temp_sock_dec;
    struct sockaddr_in server, client;

    char revbuf[100];

    sock_dec = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_dec == -1) {
        printf("Error in socket creation\n");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(3003);

    k = bind(sock_dec, (struct sockaddr*)&server, sizeof(server));
    if (k == -1) {
        printf("Error in binding\n");
        return 1;
    }

    k = listen(sock_dec, 5);
    if (k == -1) {
        printf("Error in listening\n");
        return 1;
    }
int len=sizeof(client);
    temp_sock_dec = accept(sock_dec,(struct sockaddr*)&client,&len);
    if (temp_sock_dec == -1) {
        printf("Error in accepting\n");
        return 1;
    }

    k = recv(temp_sock_dec, buf, 100, 0);
    if (k == -1) {
        printf("Error in receiving data\n");
        return 1;
    }
    printf("buf: %s", buf);

    int flag = 0;
    for (int i = 0; i < strlen(buf); i++) {
        if (buf[i] != buf[strlen(buf) - i - 1]) {
            flag = 1;
        }
    }

    if (flag) {
        k = send(temp_sock_dec, "No", 2, 0);
    } else {
        k = send(temp_sock_dec, "Yes", 3, 0);
    }

    if (k == -1) {
        printf("Error in sending\n");
    }
    close(temp_sock_dec);
    return 0;
}
