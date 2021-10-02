#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENT 10
#define BASE_PORT 5000
#define ADDR_LEN sizeof(struct sockaddr_in)

typedef struct
{
	int socketfd; // socket descriptor
	int acceptfd; // binding connection value 0 or 1
	pthread_t thread;
	struct sockaddr_in server_socket; // socket address IPaddress:PortNumber

} ServerInstance;

void create_server_instance(void);
void *thread_func(void *thread_number);
void signal_handler(int signal_number);
void server_close(void);
