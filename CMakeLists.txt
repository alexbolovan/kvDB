cmake_minimum_required(VERSION 3.31)
project(KvDB)

set(CMAKE_CXX_STANDARD 20)

add_executable(KvDB main.cpp
        dal.h
        dal.cpp
        page.h
        page.cpp
        freelist.h
        freelist.cpp)
