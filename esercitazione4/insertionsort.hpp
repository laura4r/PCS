#pragma once
#include <optional>

template<typename T>
std::vector<T>

insertionsort(std::vector<T>& vec)
{
    if(vec.size() == 0){
        return{} ;
    }
    int n = vec.size() ;
    for(int j = 1 ; j < n ; j++) {
        T value = vec[j] ;
        int i = j - 1 ;
        while(i >= 0 && vec[i] > value) {
            vec[i+1] = vec[i] ;
            i = i - 1 ;
        }
        vec[i + 1] = value ;
    }
    return vec ;

}