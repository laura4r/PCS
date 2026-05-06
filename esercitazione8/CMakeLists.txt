cmake_minimum_required(VERSION 3.20)
project(esercitazione8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")


## Creo i target per gli eseguibili che effettueranno i test unitari
add_executable(test_add test_add.cpp)
add_test(NAME add COMMAND test_add)


at_executable(test_at test_at.cpp)
at_test(NAME at COMMAND test_at)

diff_executable(test_diff test_diff.cpp)
diff_test(NAME diff COMMAND test_diff)

edges_executable(test_edges test_edges.cpp)
edges_test(NAME edges COMMAND test_edges)

neigh_executable(test_neigh test_neigh.cpp)
neigh_test(NAME neigh COMMAND test_neigh)

nodes_executable(test_nodes test_nodes.cpp)
nodes_test(NAME nodes COMMAND test_nodes)

numb_executable(test_numb test_numb.cpp)
numb_test(NAME numb COMMAND test_numb)

enable_testing()