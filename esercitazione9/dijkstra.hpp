#pragma once
#include "unidirected_graph.hpp"
#include <set>
#include <unordered_map>
#include <limits>


struct dijkstra_result {
    std::unordered_map<int,int> dist ;
    std::unordered_map<int,int> pred ;
} ;




dijkstra_result dijkstra(unidirected_graph<int>& grafo , int sorgente) {
    dijkstra_result ret ;

    for(int nodo : grafo.all_nodes()){
        ret.dist[nodo] = std::numeric_limits<int>::max() ;
        ret.pred[nodo] = -1 ;
    }

    ret.dist[sorgente] = 0 ;
    ret.pred[sorgente] = sorgente ;

    std::set<std::pair<int,int>> pq ;    /* Insieme ordinato che svolge il ruolo della coda con priorità*/
    pq.insert({0 , sorgente}) ;
    while(! pq.empty()) {
        auto current = *pq.begin() ;
        pq.erase(pq.begin()) ;      /*Queste due righe sono il dequeue*/
        int dist_u = current.first ;
        int u = current.second ;

        for(int vicino : grafo.neighbours(u)) {
            int new_dist = ret.dist[u] + 1 ;     /*Aggiornamento della distanza -> 1 è il peso dell'arco (u,v)*/

            if(new_dist < ret.dist[vicino]) {     
                if(ret.dist[vicino] != std::numeric_limits<int>::max()) {       /*Voglio la distanza minima dalla sorgente*/
                    pq.erase({ret.dist[vicino] , vicino}) ;                     
                }
                ret.dist[vicino] = new_dist ;
                ret.pred[vicino] = u ;
                pq.insert({new_dist , vicino}) ;                 /*Termino l'inizializzazione di pq inserendo i vicini di u*/
            }
        }
    }
    return ret ;
}