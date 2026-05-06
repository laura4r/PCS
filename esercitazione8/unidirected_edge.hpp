#pragma once
#include <utility>


template <typename T>
class unidirected_edge
{
    T node_start ;
    T node_finish ;

    public:
        /*Costruttore di default*/

        unidirected_edge()
            : node_start(T{0}) , node_finish(T{0})

        {}

        /*Costruttore user-defined*/
        unidirected_edge(const T& n_start , const T& n_finish)
        
        {
            if(n_start > n_finish){
                T scambia = n_start ;
                node_start = n_finish ;
                node_finish = scambia ;
            }
            else {
                node_start = n_start ;
                node_finish = n_finish ;
            }
        }


        /*Restituisco i nodi*/
        T from() const {return node_start ;}
        T to() const {return node_finish ;}


        /*Implementazione ordinamento*/
        bool operator<(const unidirected_edge& other) const {
            if(node_start == other.from()){
                return (node_finish < other.to());
            }
            else{
                return (node_start < other.from()) ;
            }
        }

        /*Implementazione uguaglianza*/
        bool operator== (const unidirected_edge& other) const{
            return(node_start == other.from() && node_finish == other.to()) ;
        }
} ;

template <typename T>
std::ostream& operator<<(std::ostream& os, const unidirected_edge<T> e){
    os << e.from() << "," << e.to() ;
    return os ;
} ;