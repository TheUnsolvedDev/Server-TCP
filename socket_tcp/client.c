#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include "client.h"

int n, client_socket_dp, length, port = 0;
struct sockaddr_in server;

void create_client_instance(int port)
{
    char msg[40];

    if ((client_socket_dp = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    server.sin_family = PF_INET;
    server.sin_port = htons(port++);
    server.sin_addr.s_addr = inet_addr("192.168.29.111");

    if (connect(client_socket_dp, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("connect");
        printf("%d\n", errno);
        exit(1);
    }

    while (1)
    {
        printf("Enter the message you want to send to server\n");
        fflush(stdin);
        fgets(msg, 400, stdin);
        send(client_socket_dp, msg, 400, 0);
        printf("Waiting for message from server..............\n");
        fflush(stdin);
        n = recv(client_socket_dp, msg, 400, 0);
        msg[n] = '\0';

        printf("Message received from server is:%s\n", msg);
    }
    close(client_socket_dp);
}

int main(int argc, char *argv[])
{
    int port = atoi(argv[1]);
    create_client_instance(port);
    return 0;
}
