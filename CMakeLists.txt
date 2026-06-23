cmake_minimum_required(VERSION 4.2)
project(showip___winsock)

set(CMAKE_CXX_STANDARD 20)

add_executable(showip___winsock
        showip.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 -static-libgcc -static-libstdc++)
