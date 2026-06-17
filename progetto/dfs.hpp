#pragma once
#include <map>
#include "weighted_graph.hpp"
#include "lifo.hpp"

weighted_graph dfs(weighted_graph& grafo, const int& sorgente, auto& contenitore)
{
    weighted_graph ret;
    std::map<int, bool> reached; // Mappa che tiene traccia dei nodi visitati

    for (int nodo : grafo.all_nodes()){  
        reached[nodo] = false;  // Inizializzo i nodi come non visitati
    }

    contenitore.put(sorgente);  // Inserisco la sorgente in uno stack

    // Finchè non ci sono nodi da esplorare, prendo il prossimo nodo
    while (!contenitore.empty()){
        int u = contenitore.get();
        if(!reached[u]){  
            reached[u] = true;  
        }

        // Esploro i vicini del nodo corrente
        for (int w : grafo.neighbours(u)){
        
            if (!reached[w]){  // Se non ho visitato w
                contenitore.put(w);  // lo aggiungo allo stack

                unidirected_edge<int> arco(u,w);  // Creo l'arco (u,v)
                double peso = grafo.peso_arco(arco);  // e recupero il peso

                ret.add_edge(u, w, peso);  // Aggiungo l'arco al grafo DFS

                reached[w] = true;  // e segno il nodo come visitato
            }
        }
    }
    return ret;
}