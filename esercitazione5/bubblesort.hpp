#pragma once
#include <optional>
#include <algorithm>

template<typename T>
std::vector<T>

bubblesort(std::vector<T>& vec)
{
    if(vec.size() == 0){
        return{} ;
    }
    int n = vec.size() ;
    for(int i = 0; i < n - 1 ; i++ ){
        for(int j = n-1 ; j > i ; j--){
            if(vec[j] < vec[j-1]) {
                std::swap(vec[j] , vec[j - 1]) ;
            }
        }
    }
    return vec ;

}