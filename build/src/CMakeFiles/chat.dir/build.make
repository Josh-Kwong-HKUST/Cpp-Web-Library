# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joshk/WebServer-Library

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joshk/WebServer-Library/build

# Include any dependencies generated for this target.
include src/CMakeFiles/chat.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/chat.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/chat.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/chat.dir/flags.make

src/CMakeFiles/chat.dir/Acceptor.cpp.o: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/Acceptor.cpp.o: ../src/Acceptor.cpp
src/CMakeFiles/chat.dir/Acceptor.cpp.o: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/chat.dir/Acceptor.cpp.o"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/Acceptor.cpp.o -MF CMakeFiles/chat.dir/Acceptor.cpp.o.d -o CMakeFiles/chat.dir/Acceptor.cpp.o -c /home/joshk/WebServer-Library/src/Acceptor.cpp

src/CMakeFiles/chat.dir/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/Acceptor.cpp.i"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshk/WebServer-Library/src/Acceptor.cpp > CMakeFiles/chat.dir/Acceptor.cpp.i

src/CMakeFiles/chat.dir/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/Acceptor.cpp.s"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshk/WebServer-Library/src/Acceptor.cpp -o CMakeFiles/chat.dir/Acceptor.cpp.s

src/CMakeFiles/chat.dir/Buffer.cpp.o: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/Buffer.cpp.o: ../src/Buffer.cpp
src/CMakeFiles/chat.dir/Buffer.cpp.o: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/chat.dir/Buffer.cpp.o"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/Buffer.cpp.o -MF CMakeFiles/chat.dir/Buffer.cpp.o.d -o CMakeFiles/chat.dir/Buffer.cpp.o -c /home/joshk/WebServer-Library/src/Buffer.cpp

src/CMakeFiles/chat.dir/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/Buffer.cpp.i"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshk/WebServer-Library/src/Buffer.cpp > CMakeFiles/chat.dir/Buffer.cpp.i

src/CMakeFiles/chat.dir/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/Buffer.cpp.s"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshk/WebServer-Library/src/Buffer.cpp -o CMakeFiles/chat.dir/Buffer.cpp.s

src/CMakeFiles/chat.dir/Channel.cpp.o: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/Channel.cpp.o: ../src/Channel.cpp
src/CMakeFiles/chat.dir/Channel.cpp.o: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/chat.dir/Channel.cpp.o"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/Channel.cpp.o -MF CMakeFiles/chat.dir/Channel.cpp.o.d -o CMakeFiles/chat.dir/Channel.cpp.o -c /home/joshk/WebServer-Library/src/Channel.cpp

src/CMakeFiles/chat.dir/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/Channel.cpp.i"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshk/WebServer-Library/src/Channel.cpp > CMakeFiles/chat.dir/Channel.cpp.i

src/CMakeFiles/chat.dir/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/Channel.cpp.s"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshk/WebServer-Library/src/Channel.cpp -o CMakeFiles/chat.dir/Channel.cpp.s

src/CMakeFiles/chat.dir/Connection.cpp.o: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/Connection.cpp.o: ../src/Connection.cpp
src/CMakeFiles/chat.dir/Connection.cpp.o: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/chat.dir/Connection.cpp.o"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/Connection.cpp.o -MF CMakeFiles/chat.dir/Connection.cpp.o.d -o CMakeFiles/chat.dir/Connection.cpp.o -c /home/joshk/WebServer-Library/src/Connection.cpp

src/CMakeFiles/chat.dir/Connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/Connection.cpp.i"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshk/WebServer-Library/src/Connection.cpp > CMakeFiles/chat.dir/Connection.cpp.i

src/CMakeFiles/chat.dir/Connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/Connection.cpp.s"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshk/WebServer-Library/src/Connection.cpp -o CMakeFiles/chat.dir/Connection.cpp.s

src/CMakeFiles/chat.dir/Epoll.cpp.o: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/Epoll.cpp.o: ../src/Epoll.cpp
src/CMakeFiles/chat.dir/Epoll.cpp.o: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/chat.dir/Epoll.cpp.o"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/Epoll.cpp.o -MF CMakeFiles/chat.dir/Epoll.cpp.o.d -o CMakeFiles/chat.dir/Epoll.cpp.o -c /home/joshk/WebServer-Library/src/Epoll.cpp

src/CMakeFiles/chat.dir/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/Epoll.cpp.i"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshk/WebServer-Library/src/Epoll.cpp > CMakeFiles/chat.dir/Epoll.cpp.i

src/CMakeFiles/chat.dir/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/Epoll.cpp.s"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshk/WebServer-Library/src/Epoll.cpp -o CMakeFiles/chat.dir/Epoll.cpp.s

src/CMakeFiles/chat.dir/Eventloop.cpp.o: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/Eventloop.cpp.o: ../src/Eventloop.cpp
src/CMakeFiles/chat.dir/Eventloop.cpp.o: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/chat.dir/Eventloop.cpp.o"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/Eventloop.cpp.o -MF CMakeFiles/chat.dir/Eventloop.cpp.o.d -o CMakeFiles/chat.dir/Eventloop.cpp.o -c /home/joshk/WebServer-Library/src/Eventloop.cpp

src/CMakeFiles/chat.dir/Eventloop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/Eventloop.cpp.i"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshk/WebServer-Library/src/Eventloop.cpp > CMakeFiles/chat.dir/Eventloop.cpp.i

src/CMakeFiles/chat.dir/Eventloop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/Eventloop.cpp.s"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshk/WebServer-Library/src/Eventloop.cpp -o CMakeFiles/chat.dir/Eventloop.cpp.s

src/CMakeFiles/chat.dir/MysqlConnection.cpp.o: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/MysqlConnection.cpp.o: ../src/MysqlConnection.cpp
src/CMakeFiles/chat.dir/MysqlConnection.cpp.o: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/chat.dir/MysqlConnection.cpp.o"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/MysqlConnection.cpp.o -MF CMakeFiles/chat.dir/MysqlConnection.cpp.o.d -o CMakeFiles/chat.dir/MysqlConnection.cpp.o -c /home/joshk/WebServer-Library/src/MysqlConnection.cpp

src/CMakeFiles/chat.dir/MysqlConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/MysqlConnection.cpp.i"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshk/WebServer-Library/src/MysqlConnection.cpp > CMakeFiles/chat.dir/MysqlConnection.cpp.i

src/CMakeFiles/chat.dir/MysqlConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/MysqlConnection.cpp.s"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshk/WebServer-Library/src/MysqlConnection.cpp -o CMakeFiles/chat.dir/MysqlConnection.cpp.s

src/CMakeFiles/chat.dir/MysqlConnectionPool.cpp.o: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/MysqlConnectionPool.cpp.o: ../src/MysqlConnectionPool.cpp
src/CMakeFiles/chat.dir/MysqlConnectionPool.cpp.o: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/chat.dir/MysqlConnectionPool.cpp.o"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/MysqlConnectionPool.cpp.o -MF CMakeFiles/chat.dir/MysqlConnectionPool.cpp.o.d -o CMakeFiles/chat.dir/MysqlConnectionPool.cpp.o -c /home/joshk/WebServer-Library/src/MysqlConnectionPool.cpp

src/CMakeFiles/chat.dir/MysqlConnectionPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/MysqlConnectionPool.cpp.i"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshk/WebServer-Library/src/MysqlConnectionPool.cpp > CMakeFiles/chat.dir/MysqlConnectionPool.cpp.i

src/CMakeFiles/chat.dir/MysqlConnectionPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/MysqlConnectionPool.cpp.s"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshk/WebServer-Library/src/MysqlConnectionPool.cpp -o CMakeFiles/chat.dir/MysqlConnectionPool.cpp.s

src/CMakeFiles/chat.dir/Server.cpp.o: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/Server.cpp.o: ../src/Server.cpp
src/CMakeFiles/chat.dir/Server.cpp.o: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/chat.dir/Server.cpp.o"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/Server.cpp.o -MF CMakeFiles/chat.dir/Server.cpp.o.d -o CMakeFiles/chat.dir/Server.cpp.o -c /home/joshk/WebServer-Library/src/Server.cpp

src/CMakeFiles/chat.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/Server.cpp.i"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshk/WebServer-Library/src/Server.cpp > CMakeFiles/chat.dir/Server.cpp.i

src/CMakeFiles/chat.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/Server.cpp.s"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshk/WebServer-Library/src/Server.cpp -o CMakeFiles/chat.dir/Server.cpp.s

src/CMakeFiles/chat.dir/Socket.cpp.o: src/CMakeFiles/chat.dir/flags.make
src/CMakeFiles/chat.dir/Socket.cpp.o: ../src/Socket.cpp
src/CMakeFiles/chat.dir/Socket.cpp.o: src/CMakeFiles/chat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/CMakeFiles/chat.dir/Socket.cpp.o"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/chat.dir/Socket.cpp.o -MF CMakeFiles/chat.dir/Socket.cpp.o.d -o CMakeFiles/chat.dir/Socket.cpp.o -c /home/joshk/WebServer-Library/src/Socket.cpp

src/CMakeFiles/chat.dir/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat.dir/Socket.cpp.i"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joshk/WebServer-Library/src/Socket.cpp > CMakeFiles/chat.dir/Socket.cpp.i

src/CMakeFiles/chat.dir/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat.dir/Socket.cpp.s"
	cd /home/joshk/WebServer-Library/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joshk/WebServer-Library/src/Socket.cpp -o CMakeFiles/chat.dir/Socket.cpp.s

# Object files for target chat
chat_OBJECTS = \
"CMakeFiles/chat.dir/Acceptor.cpp.o" \
"CMakeFiles/chat.dir/Buffer.cpp.o" \
"CMakeFiles/chat.dir/Channel.cpp.o" \
"CMakeFiles/chat.dir/Connection.cpp.o" \
"CMakeFiles/chat.dir/Epoll.cpp.o" \
"CMakeFiles/chat.dir/Eventloop.cpp.o" \
"CMakeFiles/chat.dir/MysqlConnection.cpp.o" \
"CMakeFiles/chat.dir/MysqlConnectionPool.cpp.o" \
"CMakeFiles/chat.dir/Server.cpp.o" \
"CMakeFiles/chat.dir/Socket.cpp.o"

# External object files for target chat
chat_EXTERNAL_OBJECTS =

src/libchat.so: src/CMakeFiles/chat.dir/Acceptor.cpp.o
src/libchat.so: src/CMakeFiles/chat.dir/Buffer.cpp.o
src/libchat.so: src/CMakeFiles/chat.dir/Channel.cpp.o
src/libchat.so: src/CMakeFiles/chat.dir/Connection.cpp.o
src/libchat.so: src/CMakeFiles/chat.dir/Epoll.cpp.o
src/libchat.so: src/CMakeFiles/chat.dir/Eventloop.cpp.o
src/libchat.so: src/CMakeFiles/chat.dir/MysqlConnection.cpp.o
src/libchat.so: src/CMakeFiles/chat.dir/MysqlConnectionPool.cpp.o
src/libchat.so: src/CMakeFiles/chat.dir/Server.cpp.o
src/libchat.so: src/CMakeFiles/chat.dir/Socket.cpp.o
src/libchat.so: src/CMakeFiles/chat.dir/build.make
src/libchat.so: src/CMakeFiles/chat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joshk/WebServer-Library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX shared library libchat.so"
	cd /home/joshk/WebServer-Library/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/chat.dir/build: src/libchat.so
.PHONY : src/CMakeFiles/chat.dir/build

src/CMakeFiles/chat.dir/clean:
	cd /home/joshk/WebServer-Library/build/src && $(CMAKE_COMMAND) -P CMakeFiles/chat.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/chat.dir/clean

src/CMakeFiles/chat.dir/depend:
	cd /home/joshk/WebServer-Library/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joshk/WebServer-Library /home/joshk/WebServer-Library/src /home/joshk/WebServer-Library/build /home/joshk/WebServer-Library/build/src /home/joshk/WebServer-Library/build/src/CMakeFiles/chat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/chat.dir/depend
