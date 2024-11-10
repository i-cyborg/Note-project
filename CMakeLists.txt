cmake_minimum_required(VERSION 3.29)
project(note)

set(CMAKE_CXX_STANDARD 20)

add_executable(note main.cpp
        Note.cpp
        Note.h
        Collection.cpp
        Collection.h
        Observer.cpp
        Observer.h)
