cmake_minimum_required(VERSION 3.29)
project(CTCO02___Introsort C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CTCO02___Introsort
    introsort.c
    introsort.h
    main.c)
