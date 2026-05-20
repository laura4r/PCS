#pragma once
#include <queue>

template<typename T>
class fifo
{
    std::queue<T> coda ;

    public:
    /*Costruttore di default*/

    fifo()
        : coda()
    {}

    /*Inserimento*/
    void put(const T& nuovo){
        coda.push(nuovo) ;
    }

    /*Rimozione*/
    T get(){
        T ret = coda.front() ;
        coda.pop() ;
        return ret ;
    }

    /*Vuoto?*/
    bool empty(){
        bool ret =  coda.empty() ;
        return ret ;
    }
    
} ;