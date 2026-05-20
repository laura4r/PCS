#pragma once
#include <stack>

template<typename T>
class lifo
{
    std::stack<T> pila ;
    public :
        lifo()
        : pila()
    {}

    /*Inserimento*/
    void put(const T& nuovo){
        pila.push(nuovo) ;
    }

    /*Rimozione*/
    T get(){
        T ret = pila.top() ;
        pila.pop() ;
        return ret ;
    }

    /*Vuoto?*/
    bool empty(){
        bool ret =  pila.empty() ;
        return ret ;
    }
} ;