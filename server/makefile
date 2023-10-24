clientPath = ./executable/client
serverPath = ./executable/server
link = g++ -o
compile = g++ -c
client:	ClientSocket.o Client.o
	 ${link} ${clientPath} ClientSocket.o Client.o

server:	ServerSocket.o server.o
	${link} ${serverPath} server ServerSocket.o server.o

clean:
	rm -rf *.o

ClientSocket.o:	ClientSocket.cpp
	${compile} ClientSocket.cpp

client.o:	client.cpp
	${compile} client.cpp

ServerSocket.o:	ServerSocket.cpp
	${compile} ServerSocket.cpp

server.o:	server.cpp
	${compile} server.cpp

