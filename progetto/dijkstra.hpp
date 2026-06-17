#pragma once
#include <set> /* usato come coda di priorità ordinata */
#include <unordered_map> /* associo chiave -> valore */
#include <limits> /* per +inf */
#include "weighted_graph.hpp"

/* risultato finale */
struct dijkstra_result {
    std::unordered_map<int,int> dist; /* dist[nodo]: nodo -> min distanza sorgente */
	std::unordered_map<int,int> pred; /* pred[nodo]: predecessore del nodo */
};

dijkstra_result dijkstra(weighted_graph& graph, int source) {
    dijkstra_result result;
    /* Inizializzo i nodi */
    for (int node:graph.all_nodes()) {
        result.dist[node]=std::numeric_limits<int>::max(); /* dist[nodo]=+inf */
		result.pred[node]=-1; /* pred[nodo]=-1 */
    }
	/* sorgente */
    result.dist[source]=0; 
	result.pred[source]=source;
	/* set ordinato, quindi il primo elemento sarà sempre quello con distanza minima: (distanza,nodo) */
	std::set<std::pair<int,int>> pq;
	pq.insert({0,source}); /* PQ.Enqueue() */
    while (!pq.empty()) {
        /* PQ.Dequeue() */
		auto current=*pq.begin(); /* nodo con distanza minima, quindi il primo elemento del set */
		pq.erase(pq.begin());
		int dist_u=current.first;
        int u=current.second;
		for (int v:graph.neighbours(u)) {
			unidirected_edge<int> arco(u,v);
            double peso=graph.peso_arco(arco);
			double new_dist=result.dist[u]+peso;
            if (new_dist<result.dist[v]) {
				/* se il nodo è gia nella coda, rimuovo la vecchia dist */
				if (result.dist[v] != std::numeric_limits<int>::max()) {
					pq.erase({result.dist[v],v});
				}
				result.dist[v]=new_dist;
				result.pred[v]=u;
				/* DecreaseKey: inserisco il nodo con la nuova priorità */
				pq.insert({new_dist,v});
            }
        }
    }
    return result;
}