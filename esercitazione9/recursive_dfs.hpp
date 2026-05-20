#pragma once
#include "unidirected_graph.hpp"


template <typename T>
unidirected_graph<T> recursive_dfs(unidirected_graph<T>& grafo , const T& sorgente) {
    unidirected_graph<T> albero ;
    std::set<T> visitati ;


    for(T nodo : grafo.all_nodes()){
        if(!visitati.contains(nodo)) {
            DFS(grafo, albero, nodo, visitati) ;
        }
    }

    return albero ;
}



template <typename T>
void DFS(unidirected_graph<T>& grafo, unidirected_graph<T>& albero, const T& nodo, std::set<T>& visitati) {
    visitati.insert(nodo) ;

    for(T vicino : grafo.neighbours(nodo)) {
        if(visitati.contains(vicino)){
            unidirected_edge<T> arco (nodo , vicino) ;
            albero.add_edge(arco) ;
        }
        else {
            DFS(grafo, albero, vicino, visitati) ;
        }
    }
}