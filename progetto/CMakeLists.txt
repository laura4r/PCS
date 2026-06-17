cmake_minimum_required(VERSION 3.20)
project(Progetto_finale)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE CXX FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

include_directories(/usr/include/eigen3)

set(SOURCES main.cpp)
add_executable(progetto_finale ${SOURCES})