#include <stdio.h>
#include "server.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

ServerInstance server_obj[MAX_CLIENT];

static int client_number = 0;

void create_server_instance(void)
{
	if ((server_obj[client_number].socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("\nConnection not available for this socket\n");
		exit(0);
	}
	else
	{
		printf("Socket connection established\n");
		server_obj[client_number].server_socket.sin_family = AF_INET;
		server_obj[client_number].server_socket.sin_port = htons(BASE_PORT + client_number);
		int inet = inet_aton("0.0.0.0", &server_obj[client_number].server_socket.sin_addr);
		int length = ADDR_LEN;
		printf("inet %d\n", inet);

		if (bind(server_obj[client_number].socketfd, (struct sockaddr *)&(server_obj[client_number].server_socket), ADDR_LEN) < 0)
		{
			perror("Bind failure\n");
			exit(0);
		}
		if (listen(server_obj[client_number].socketfd, 4) < 0)
		{
			perror("Listening ... \n");
			exit(EXIT_FAILURE);
		}

		if ((server_obj[client_number].acceptfd = accept(server_obj[client_number].socketfd, (struct sockaddr *)&server_obj[client_number].server_socket, (socklen_t *)&length)) < 0)
		{
			perror("Accept! \n");
			exit(0);
		}
	}
}

void signal_handler(int signal_number)
{
	if (signal_number == SIGTSTP)
	{
		printf("Exiting connections!\n");
		for (int i = 0; i < 5; i++)
		{
			close(server_obj[i].socketfd);
		}
	}
}
