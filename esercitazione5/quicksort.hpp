#pragma once
#include <optional>
#include <algorithm>
#include <vector>
#include "partizione.hpp"
#include "insertionsort.hpp"

template<typename T>
std::vector<T>

quicksort(std::vector<T>& vec, int sinistra, int destra)
{
    if(vec.size() == 0){
        return{} ;
    }

    const int soglia = 110 ;
        if(sinistra < destra) {
            int centro = partizione(vec, sinistra, destra) ;

            if(centro - 1 - sinistra <= soglia){
                insertionsort(vec) ;
            }
            else{
                quicksort(vec, sinistra, centro - 1 ) ;
            }
            if(destra - centro <= soglia){
                insertionsort(vec) ;
            }
            else{
                quicksort(vec, centro + 1 , destra ) ;
            }
        }
    return vec ;
}

