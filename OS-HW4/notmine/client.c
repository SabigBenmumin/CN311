#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFFSIZE 1024
#define STUDENT_ID_LAST_4_DIGITS 2197
#define PORT1 10000 + STUDENT_ID_LAST_4_DIGITS
#define PORT2 20000 + STUDENT_ID_LAST_4_DIGITS

void send_recv(int sock, char *send_data, int port){
    char revc_data[BUFFSIZE];
    send(sock, send_data, strlen(send_data), 0);
    int len = recv(sock, revc_data, BUFFSIZE, 0);
    revc_data[len] = '\0';
    printf("received: %s\n", revc_data);
}

int main(int argc, char *argv[]){

    if(argc < 4) {
        printf("usage: %s <server> <data1> <data2> ... <dataN>\n",argv[0]);
        exit(1);
    }

    int client_sock;
    struct sockaddr_in server_addr;

    char name[BUFFSIZE], birthday[9];
    strcpy(name, argv[1]);
    strcat(name, " ");
    strcat(name, argv[2]);
    strcpy(birthday, argv[3]);

    //connect server on PORT1
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT1);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(server_addr.sin_zero), '\0', 8);
    connect(client_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    send_recv(client_sock, name ,PORT1);
    close(client_sock);

    //connect server on PORT2
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_port = htons(PORT2);
    connect(client_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    send_recv(client_sock, birthday, PORT2);
    send(client_sock, "Bye", strlen("Bye") + 1, 0);
    close(client_sock);

    return 0;
}