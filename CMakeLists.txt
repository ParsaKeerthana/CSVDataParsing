cmake_minimum_required(VERSION 3.27)
project(Trial)

set(CMAKE_CXX_STANDARD 17)

add_executable(Trial main.cpp
        Parse.cpp
        Parse.h
        AirNowRecord.cpp
        AirNowRecord.h)
