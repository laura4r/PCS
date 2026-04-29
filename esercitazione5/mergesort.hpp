#pragma once
#include <optional>
#include "merge.hpp"

template<typename T>
std::vector<T>

mergesort(std::vector<T>& vec, int sinistra, int destra)
{
    if(vec.size() == 0){
        return{} ;
    }
    
    if(sinistra < destra) {
        int centro = (sinistra + destra) / 2 ;
        mergesort(vec, sinistra, centro) ;
        mergesort(vec, centro + 1 , destra) ;
        merge(vec, sinistra, centro, destra) ;
    }
    return vec ;
}

