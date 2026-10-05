all: client.exe server.exe

server.o: src/server.c src/common.h
	gcc -c src/server.c

client.o: src/client.c src/common.h
	gcc -c src/client.c

common.o: src/common.c src/common.h
	gcc -c src/common.c

client_array.o: src/client_array.c src/client_array.h
	gcc -c src/client_array.c

rsa_algo.o: src/rsa_algo.c src/rsa_algo.h
	gcc -c src/rsa_algo.c

client.exe: client.o common.o client_array.o rsa_algo.o
	gcc client.o common.o client_array.o rsa_algo.o -o client.exe -lm

server.exe: server.o common.o client_array.o rsa_algo.o
	gcc server.o common.o client_array.o rsa_algo.o -o server.exe -lm

.PHONY: clean
clean:
	rm -f *.o *.exe

# -lm pour la bibliothèque <math.h>