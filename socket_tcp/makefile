# the compiler: gcc for C program, define as g++ for C++
CC = gcc

CFLAGS  =  -lpthread

# the build target executable:
TARGET = output

all: $(TARGET)

$(TARGET): 
	$(CC) *.c *.h -o $(TARGET) $(CFLAGS) 

clean:
	$(RM) $(TARGET)