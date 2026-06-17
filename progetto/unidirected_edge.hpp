#include <iostream>
#pragma once

using namespace std;

template<typename T>
class unidirected_edge
{
    T node_start; // nodo di partenza
    T node_finish; // nodo di arrivo
public:
    /* Costruttore di default */
    unidirected_edge()
        : node_start(T{0}),node_finish(T{0})
    {}

    /* Costruttore user-defined */
    unidirected_edge(const T& n_start, const T& n_finish)
        : node_start(n_start), node_finish(n_finish)
    {
        /* Il nodo di partenza deve essere sempre più piccolo del nodo di arrivo */
        if (n_start > n_finish){
            T scambia = n_start;
            node_start = n_finish;
            node_finish = scambia;
        }
        else{
            node_start = n_start;
            node_finish = n_finish;
        }
    }

    /* Restituisco i valori di node_start e node_finish */
    T from() const {return node_start;}
    T to() const {return node_finish;}

    /* Implementazione dell'operatore < */
    // Ordino gli archi con l'ordine lessicografico
    bool operator< (const unidirected_edge& other) const{
        if (node_start == other.from()){
            return (node_finish < other.to());
        }
        else{
            return (node_start < other.from());
        }
    }

    /* Implementazione dell'operatore == */
    bool operator== (const unidirected_edge& other) const{
        return(node_start == other.from() && node_finish == other.to());
    }
};

/* Implementazione dell'operatore << per stampare l'oggetto */
template<typename T>
ostream& operator<<(ostream& os, const unidirected_edge<T>& e)
{
    os << e.from() << "," << e.to();
    return os;
}