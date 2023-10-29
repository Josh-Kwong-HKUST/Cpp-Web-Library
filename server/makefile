serverExecPath = ./bin/server
clientExecPath = ./bin/client
includePath = ./include
srcPath = ./src
link = g++ -o
compile = g++ -c
debugFlag = -g -fsanitize=address,undefined

build:
	make client && make server && make clean

client:
	g++ ${srcPath}/client.cpp ${includePath}/Client.cpp  ${includePath}/Socket.cpp ${includePath}/Message.cpp -o ${clientExecPath} ${debugFlag}

server:
	g++ ${srcPath}/server.cpp ${includePath}/Server.cpp ${includePath}/Epoll.cpp ${includePath}/Client.cpp ${includePath}/Socket.cpp ${includePath}/Eventloop.cpp ${includePath}/Channel.cpp ${includePath}/Message.cpp -o ${serverExecPath} ${debugFlag}

clean:
	rm -rf *.o

# Client.o: ${includePath}Client.cpp
# 	${compile} ${includePath}Client.cpp

# client.o: Client.o Socket.o ${srcPath}client.cpp
# 	${compile} ${srcPath}client.cpp

# Server.o: Epoll.o Client.o Socket.o Eventloop.o Channel.o  ${includePath}Server.cpp
# 	${compile} ${includePath}Server.cpp

# Socket.o: ${includePath}Socket.cpp
# 	${compile} ${includePath}Socket.cpp

# server.o: Server.o ${srcPath}server.cpp
# 	${compile} ${srcPath}server.cpp

# Epoll.o: ${includePath}Epoll.cpp
# 	${compile} ${includePath}Epoll.cpp

# Message.o: ${includePath}Message.cpp
# 	${compile} ${includePath}Message.cpp

# Channel.o: ${includePath}Channel.cpp
# 	${compile} ${includePath}Channel.cpp

# Eventloop.o: ${includePath}Eventloop.cpp
# 	${compile} ${includePath}Eventloop.cpp