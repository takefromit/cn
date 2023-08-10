#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct frame {
    int frame_kind; // ack=0, seq=1, fin=2
    int seq_no;
    int ack_no;
    char data[100];
} Frame;

int main() {
    int k, sock_dec;
    char buf[100];
    struct sockaddr_in server;

    sock_dec = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock_dec == -1) {
        printf("Error in socket creation\n");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);

    Frame f_send;
    int frame_id = 0;
    int len = sizeof(server);

    while (1) {
        printf("Enter the data: ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';
        strcpy(f_send.data, buf);
        f_send.frame_kind = 1;
        f_send.seq_no = frame_id;
        f_send.ack_no = 1;
        k = sendto(sock_dec, &f_send, sizeof(Frame), 0, (struct sockaddr*)&server, sizeof(server));
        printf("Frame Sent\n");

        Frame f_recv;
        k = recvfrom(sock_dec, &f_recv, sizeof(Frame), 0, (struct sockaddr*)&server, &len);
        if (k > 0 ){
            printf("Ack received\n");
        }
    }

    return 0;
}
