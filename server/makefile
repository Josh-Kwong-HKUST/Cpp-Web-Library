serverExecPath = ./bin/server
clientExecPath = ./bin/client
ClientSocketPath = ./include/ClientSocket.cpp
ServerSocketPath = ./include/ServerSocket.cpp
clientcppPath = ./src/client.cpp
servercppPath = ./src/server.cpp
link = g++ -o
compile = g++ -c
debugFlag = -g -fsanitize=address,undefined

client:	ClientSocket.o client.o
	${link} ${clientExecPath} ClientSocket.o client.o ${debugFlag} && make clean

server:	ServerSocket.o server.o
	${link} ${serverExecPath} ServerSocket.o server.o ${debugFlag} && make clean

clean:
	rm -rf *.o

ClientSocket.o:
	${compile} ${ClientSocketPath}

client.o:
	${compile} ${clientcppPath}

ServerSocket.o:
	${compile} ${ServerSocketPath}

server.o:
	${compile} ${servercppPath}

