#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define STUDENT_ID_LAST_4_DIGITS 2197
#define PORT1 10000 + STUDENT_ID_LAST_4_DIGITS
#define PORT2 20000 + STUDENT_ID_LAST_4_DIGITS

int main() {
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;
    char client_message[2000];

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT1);

    //Bind
    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc, 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    //Receive a message from client
    while((recv(client_sock, client_message, 2000, 0)) > 0) {
        printf("Client message : %s\n", client_message);
        write(client_sock, client_message, strlen(client_message));
    }

    if(recv(client_sock, client_message, 2000, 0) == 0) {
        puts("Client disconnected");
    }
    else {
        perror("recv failed");
    }

    return 0;
}
