#include <iostream>
#include "graph_visit.hpp"
#include "recursive_dfs.hpp"
#include "dijkstra.hpp"

int main(void){

    unidirected_edge<int> a1(1,2);
    unidirected_edge<int> a2(1,3);
    unidirected_edge<int> a3(2,4);
    unidirected_edge<int> a4(5,1);
    unidirected_edge<int> a5(4,5);

    unidirected_graph<int> grafo;
    grafo.add_edge(a1);
    grafo.add_edge(a2);
    grafo.add_edge(a3);
    grafo.add_edge(a4);
    grafo.add_edge(a5);

    fifo<int> q ;

    unidirected_graph<int> albero_bfs = graph_visit(grafo , 3 , q) ;
    std::cout << "BFS" << "\n" ;
    for(unidirected_edge<int> arco : albero_bfs.all_edges()){
        std::cout << arco << "\n" ;
    }

    std::cout << "\n" ;
    


    lifo<int> s ;
    unidirected_graph<int> albero_dfs = graph_visit(grafo , 3 , s) ;
    std::cout << "DFS" << "\n" ;
    for(unidirected_edge<int> arco : albero_dfs.all_edges()){
        std::cout << arco << "\n" ;
    }

    std::cout << "\n" ;

    unidirected_graph<int> albero_rec = recursive_dfs(grafo,3) ;
    std::cout << "DFS ricorsivo" << "\n" ;
    for(unidirected_edge<int> arco : albero_rec.all_edges()){
        std::cout << arco << "\n" ;
    }


    dijkstra_result d_res = dijkstra(grafo , 3) ;
    std::unordered_map<int,int> predecessori = d_res.pred ;
    std::unordered_map<int,int> distanze = d_res.dist ;

    std::cout << "Predecessori" << "\n" ;
    for(auto& [nodo , pred] : predecessori) {
        std::cout << "Nodo: " << nodo << ", predecessore: " << pred << "\n" ;
    }
    std::cout << "\n" ;

    std::cout << "Distanze" << "\n" ;
    for(auto& [nodo , dist] : distanze) {
        std::cout << "Nodo: " << nodo << ", distanza: " << dist << "\n" ;
    }


}