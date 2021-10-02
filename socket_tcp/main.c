#include <stdio.h>
#include "server.h"
// #include "client.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

int main()
{
	int i = 1;
	while (i--)
	{
		signal(SIGTSTP, signal_handler);
		create_server_instance();
	}
	return 0;
}