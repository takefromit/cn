#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char buf[100];
    char revbuf[100];
    int k, sock_dec;
    struct sockaddr_in client;

    sock_dec = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(3003);

    if (sock_dec == -1) {
        printf("Error in socket creation\n");
        return 1;
    }

    k = connect(sock_dec, (struct sockaddr*)&client, sizeof(client));

    if (k == -1) {
        printf("Connection failed\n");
        return 1;
    }

    printf("Enter the string: ");
    fgets(buf, 100, stdin);

    k = send(sock_dec, buf, 100, 0);
    if (k == -1) {
        printf("Sending failed\n");
        return 1;
    }

    k = recv(sock_dec, revbuf, 100, 0);
    if (k == -1) {
        printf("Error in receiving the response\n");
        return 1;
    }

    printf("%s", revbuf);
    close(sock_dec);
    return 0;
}
