# 

all: client.exe server.exe

server.o: server.c common.h
	gcc -c server.c

client.o: client.c common.h
	gcc -c client.c

common.o: common.c common.h
	gcc -c common.c

client_array.o: client_array.c client_array.h
	gcc -c client_array.c

client.exe: client.o common.o client_array.o
	gcc -o client.exe client.o common.o client_array.o

server.exe: server.o common.o client_array.o
	gcc -o server.exe server.o common.o client_array.o

.PHONY: clean
clean:
	rm -f *.o maze.exe
