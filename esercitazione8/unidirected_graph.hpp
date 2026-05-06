#pragma once
#include <set>
#include <map>
#include "unidirected_edge.hpp"


template <typename T>
class unidirected_graph {
    std::set<T> nodi ;
    std::map<T , std::set<unidirected_edge<T>>> archi ;

    public:
        /*Costruttore di default*/
        unidirected_graph()
            :nodi({}) , archi({})
        {}

        /*Costruttore di copia*/
        unidirected_graph(const unidirected_graph& other)
        {}

        /*Restituisco i vicini*/
        std::set<T> neighbours(const T nodo){
            std::set<T> ret ;
            for(unidirected_edge<T> vicino : archi.at(nodo)) {
                ret.insert( vicino.to() ) ;
            }
            
            for(T altro_n : nodi){
                if(altro_n < nodo && archi.at(altro_n).contains(unidirected_edge<T>(altro_n , nodo))){
                    ret.insert(altro_n) ;
                }
            }
            return ret ;
        }


        /*Aggiungo archi*/
        unidirected_graph add_edge(const unidirected_edge<T>& arco){
            T partenza = arco.from() ;
            if (nodi.contains(partenza)){
                archi[partenza].insert(arco) ;
            }
            else{
                nodi.insert(partenza) ;
                archi[partenza] = {arco} ;
            }
            if(! nodi.contains(arco.to())) {
                nodi.insert(arco.to()) ;
            }

            return *this ;
        }

        /*Restituisco tutti gli archi*/
        std::set<unidirected_edge<T>> all_edges() const {
            std::set<unidirected_edge<T>> ret ;
            for(const auto [nodo,adiacenti] : archi){
                for(unidirected_edge<T> arco : adiacenti) {
                    ret.insert(arco) ;
                }
            }
            return ret ;
        }

        /*Restituisco tutti i nodi*/
        std::set<T> all_nodes() const {
            return nodi ;
        }

        /*Restituisco la numerazione dell'arco*/
        int edge_number(const unidirected_edge<T>& arco) const {
            int num = 0 ;
            T partenza = arco.from() ;
            for(const auto [nodo,adiacenti] : archi){
                if(nodo < partenza){
                    num += adiacenti.size();
                }
            }

            for(unidirected_edge<T> altro_arco : archi.at(partenza)) {
                if(altro_arco < arco){
                    num++ ;
                }
            }
            return num ;
        }

        /*Restituisco arco data numerazione*/
        unidirected_edge<T> edge_at(const int num) const {
            for(const auto [nodo,adiacenti] : archi){
                for(unidirected_edge<T> arco : adiacenti){
                    if(edge_number(arco) == num){
                        return arco ;
                    }
                }
            }
        }

        /*Differenza*/
        unidirected_graph operator-(const unidirected_graph& other) const {
            unidirected_graph result;

            for (const auto& [nodo, adiacenti] : archi) {
                for (const auto& arco : adiacenti) {
                    if (!other.all_edges().contains(arco)) {
                        result.add_edge(arco);
                    }
                }
            }

            return result;
        }
} ;