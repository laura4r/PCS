#pragma once
#include <optional>


template<typename T>
std::vector<T> merge(std::vector<T>& vec, int sinistra, int centro, int destra)
{
    int n1 = centro - sinistra + 1 ;
    int n2 = destra - centro ;
    // creo vettori L[1,...,n1+1] e R[1,...,n2+1]
    std::vector<T> L(n1) ;
    std::vector<T> R(n2) ;

    for(int i = 0 ; i < n1 ; i++) {
        L[i] = vec[sinistra + i] ;
    }

    for(int j = 0 ; j < n2 ; j++) {
        R[j] = vec[centro + j + 1] ;
    }
    int i = 0 ;
    int j = 0 ;

    for(int k = sinistra ; k < destra + 1; k++){
        if(i < L.size() && j < R.size()){
            if(L[i] <= R[j]){
                vec[k] = L[i] ;
                i += 1 ;
            }
            else{
                vec[k] = R[j] ;
                j += 1 ;
            }
        }
        else if(i == L.size()){
            vec[k] = R[j] ;
            j += 1 ;
        }
        else if(j == R.size()){
            vec[k] = L[i] ;
            i += 1 ;
        }
        else {
            break ;
        }
    }

    return vec ;
}