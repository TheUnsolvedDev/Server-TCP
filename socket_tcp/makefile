# the compiler: gcc for C program, define as g++ for C++
CC = gcc

CFLAGS  =  -lpthread

# the build target executable:
TARGET_server = server
TARGET_client = client

server: 
	$(CC) server.c server.h -o $(TARGET_server) $(CFLAGS) 

client: 
	$(CC) client.c client.h -o $(TARGET_client) $(CFLAGS)

clean:
	$(RM) $(TARGET_server) $(TARGET_client)