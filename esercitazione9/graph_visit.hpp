#pragma once
#include <map>
#include "unidirected_graph.hpp"
#include "lifo.hpp"
#include "fifo.hpp"

template <typename T>
unidirected_graph<T> graph_visit(unidirected_graph<T>& grafo , const T& sorgente , auto contenitore){
    unidirected_graph<T> ret ;
    
    std::map<T , bool> reached ;


    for(T nodo : grafo.all_nodes()){
        reached.insert({nodo , 0}) ;
    }

    contenitore.put(sorgente) ;
    while(! contenitore.empty()){
        T u = contenitore.get() ;
        if(! reached[u]){
            reached[u] = 1 ;
            
            for(T w : grafo.neighbours(u)){
                if(! reached[w]){
                    contenitore.put(w) ;
                }
                else {
                    unidirected_edge<T> arco(u,w) ;
                    ret.add_edge(arco) ;
                }
            }
        }
    }
    return ret ;
}