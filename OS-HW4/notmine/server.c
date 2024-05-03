#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.net>
#include <netdb.h>

#define BUFFSIZE 1024
#define STUDENT_ID_LAST_4_DIGITS 2197
#define PORT1 10000 + STUDENT_ID_LAST_4_DIGITS
#define PORT2 20000 + STUDENT_ID_LAST_4_DIGITS

void p_client(int client_sock, int port){
    char buffer[BUFFSIZE];
    int len = recv(client_sock, buffer, BUFFSIZE, 0);
    buffer[len] = '\0';
    if(port == PORT1){
        printf("Received from client: %s\n", buffer);
        strcpy(buffer, "Server received");
        send(client_sock, buffer, trlen(buffer), 0);
    }else{
        int ps_year, be_year;
        ps_year = atoi(buffer + 4);
        be_year = ps_year - 543;
        sprintf(buffer, "%d", be_year);
        send(client_sock, buffer, strlen(buffer), 0);
        recv(client_sock, buffer, BUFFSIZE, 0);
        printf("Client says: %s\n", buffer);
    }
    close(client_sock);
}

int main(){
    int server_fd, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size = sizeof(stru)

    //sock1
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT1);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), '\0', 8);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    listen(server_fd, 1);

    printf("Server listening on port %d...\n", port1);
    client_sock = accept(server_fd, (struct sockaddr *)&client_addr, &sin_size);
    p_client(client_sock, PORT1);

    //sock2
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_port = htons(PORT2);

    close(server_fd);

    return 0;
}