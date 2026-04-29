#pragma once

#include<optional>

template<typename T>
bool
is_sorted(const std::vector<T>& vec){
    if(vec.size() == 0) {
        return 1 ;
    }
    bool sorted = 1;
    int n = vec.size() ;
    for(int i = 0 ; i < n - 1 ; i++) {
        sorted *= (vec[i] <= vec[i + 1]) ;
    }
    return sorted ;
}