cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(chatroom)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_subdirectory(./src)

set (mysql_lib mysqlclient)
add_executable(server ${CMAKE_CURRENT_SOURCE_DIR}/main/server.cpp)
target_link_libraries(server chat)
target_link_libraries(server ${mysql_lib})

add_executable(client ${CMAKE_CURRENT_SOURCE_DIR}/main/client.cpp)
target_link_libraries(client chat pthread)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)