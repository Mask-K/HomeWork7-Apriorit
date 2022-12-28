cmake_minimum_required(VERSION 3.22)
project(Homework7)

set(CMAKE_CXX_STANDARD 20)

add_executable(Homework7 main.cpp MyGuard.h Deletors.h MySmartPtrs.h)

target_link_libraries(Homework7 -lws2_32 -lwsock32)
