cmake_minimum_required(VERSION 3.20)
project(esercitazione2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE CXX FLAGS "${CMAKE CXX FLAGS} -Wall -Wshadow -Werror=vla")

add_executable(es_array es_array.cpp)
add_executable(es_algo algo.cpp)