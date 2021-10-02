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
struct sockaddr_in client;
socklen_t length;
int nsd, sd, httpsd, port = BASE_PORT;
static int client_number = 0;
int thread_count = 0, yes = 1, listen_data = 0xffff;

void *thread_func(void *thread_number)
{
	char message[400];
	int dat, tid, thread_no;

#ifdef SYS_gettid
	tid = syscall(SYS_gettid);
#endif
	thread_no = *(int *)thread_number - 1;
	printf("child created pid=%d thread_no=%d\n", tid, thread_no);

	//printf("Got connection from client:%s\n",inet_ntoa((*((struct sockaddr *)client)).sin_addr));
	while (1)
	{

		if ((dat = recv(server_obj[thread_no].acceptfd, message, 400, 0)) == -1)
		{
			perror("recv");
			server_close();
			exit(1);
		}

		message[dat] = '\0';

		printf("Data received Client %d : %s\n", thread_no, message);
		fflush(stdin);
		gets(message);
		send(server_obj[thread_no].acceptfd, message, 400, 0);
		fflush(stdin);
	}
	pthread_exit(0);
}

void create_server_instance(void)
{
	if ((server_obj[client_number].socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("\nConnection not available for this socket\n");
		exit(1);
	}

	printf("Socket connection established\n");

	server_obj[thread_count].server_socket.sin_port = htons(port++);
	server_obj[thread_count].server_socket.sin_family = AF_INET;

	int inet = inet_aton("0.0.0.0", &server_obj[client_number].server_socket.sin_addr);
	int length = ADDR_LEN;
	printf("inet value: %d\n", inet);

	if (inet == 0)
	{
		printf("Error !!\n");
	}

	if (bind(server_obj[client_number].socketfd, (struct sockaddr *)&(server_obj[client_number].server_socket), ADDR_LEN) < 0)
	{
		perror("Bind failure\n");
		exit(1);
	}
	else
	{
		printf("Binded \n");
	}

	listen_data = listen(server_obj[thread_count].socketfd, 1);
	if (listen == -1)
	{
		perror("Listening ... \n");
		exit(1);
	}

	if ((server_obj[thread_count].acceptfd = accept(server_obj[client_number].socketfd, (struct sockaddr *)&server_obj[client_number].server_socket, (socklen_t *)&length)) == -1)
	{
		perror("Accept! \n");
		exit(1);
	}
	else if (thread_count < MAX_CLIENT)
	{
		pthread_create(&server_obj[thread_count].thread, NULL, thread_func, &thread_count);
		thread_count++;
	}
}

void server_close(void)
{
	while (thread_count--)
	{
		pthread_join((pthread_t *)&server_obj[thread_count].thread, NULL);
		close(server_obj[thread_count].socketfd);
		close(server_obj[thread_count].acceptfd);
	}
}

void signal_handler(int signal_number)
{
	if (signal_number == SIGTSTP)
	{
		printf("Exiting connections!\n");
		server_close();
	}
}

int main(int argc, char *argv[])
{
	while (thread_count < MAX_CLIENT)
	{

		if (signal(SIGTSTP, signal_handler) == SIG_ERR)
			printf("unable to catch signal");
		create_server_instance();
	}

	server_close();

	return 0;
}