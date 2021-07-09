cmake_minimum_required(VERSION 3.19)
project(scop C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -lGL)

add_executable(scop main.c)