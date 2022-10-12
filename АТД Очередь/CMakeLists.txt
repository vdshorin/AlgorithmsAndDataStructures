cmake_minimum_required(VERSION 3.13)
project(Algoritms_Lab1)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_HEADERS
        ELType.h
        SerialQueue.h
        ConnectedQueue.h
        )
set(PROJECT_SOURCES
        main.cpp
        )

#add_executable(Algoritms_Lab1 main.cpp )
add_executable(untitled1 ${PROJECT_SOURCES} ${PROJECT_HEADERS})