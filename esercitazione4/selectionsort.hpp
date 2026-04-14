#pragma once
#include <optional>

template<typename T>
std::vector<T>

selectionsort(std::vector<T>& vec)
{
    if(vec.size() == 0){
        return{} ;
    }
    int n = vec.size() ;
    for(int i = 0 ; i < n-1 ; i ++) {
        int min_index = i ;
        for(int j = i + 1 ; j < n ; j++) {
            if(vec[j] < vec[min_index]) {
                min_index = j ;
            }
        }
        T scambia = vec[i] ;
        vec[i] = vec[min_index] ;
        vec[min_index] = scambia ;
    }
    return vec ;

}