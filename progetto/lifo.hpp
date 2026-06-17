#pragma once
#include <stack>

template<typename T>
class lifo
{
    std::stack<T> pila;
public:
    /* Costruttore di default */
    lifo()
        : pila()
    {}

    /* Inserisco elemento nel contenitore (in cima) */
    void put(const T nuovo){
        pila.push(nuovo);
    }

    /* Rimuovo elemento dal contenitore (dalla cima) */
    T get(){
        T ret = pila.top();
        pila.pop();
        return ret;
    }

    /* Determino se il contenitore è vuoto */
    bool empty(){
        bool ret = pila.empty();
        return ret;
    }
};