#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct frame {
    int frame_kind; // ack:0, seq=:1, fin:2
    int sq_no;
    int ack_no;
    char data[100];
} Frame;

int main() {
    int k, sock_dec;
    struct sockaddr_in server;

    sock_dec = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_dec == -1) {
        printf("Error in socket creation\n");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port =3003;

    if (bind(sock_dec, (struct sockaddr*)&server, sizeof(server)) == -1) {
        printf("Error in binding\n");
        return 1;
    }

    Frame f_recv;
    Frame f_send;
    int frame_id = 0;
    int len = sizeof(server);

    while (1) {
        k = recvfrom(sock_dec, &f_recv, sizeof(Frame), 0, (struct sockaddr*)&server, &len);
        if (k > 0 && f_recv.frame_kind == 1 && f_recv.sq_no == frame_id) {
            printf("Frame received data: %s\n", f_recv.data);
            // memset(&f_send, 0, sizeof(f_send));
            f_send.sq_no = frame_id;
            f_send.frame_kind = 0;
            f_send.ack_no = frame_id == 0 ? 1 : 0;
            k = sendto(sock_dec, &f_send, sizeof(Frame), 0, (struct sockaddr*)&server, len);
            printf("Ack sent\n");
        }
    }

    return 0;
}
