cmake_minimum_required(VERSION 3.20)
project(esercitazione1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(esercitazione1_esempio print_args.cpp)
add_executable(esercitazione1_esercizio medieT.cpp)