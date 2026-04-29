#include <iostream>
#include <algorithm>
#include <vector>
#include "bubblesort.hpp"
#include "selectionsort.hpp"
#include "insertionsort.hpp"
#include "mergesort.hpp"
#include "quicksort.hpp"
#include "timecounter.h"
#include "randfiller.h"


int main(void){
    randfiller rf ;
    timecounter tc ;

    std::vector<std::vector<int>> vettori(100) ;

    for(int k = 1 ; k <= 100 ; k++) {

        for(int i = 0; i <= 99 ; i++){
            // riempio i vettori di dimensione k
            std::vector<int> v = vettori[i] ;
            v.resize(k) ;
            rf.fill(v, -50, 50) ;
            vettori[i] = v ;
        }

        tc.tic() ;
        for(int i = 0; i <= 99 ; i++){

            std::vector<int> v = vettori[i] ;

            std::vector<int> v_bubble = v ;
            std::vector<int> v_sel = v ;
            std::vector<int> v_ins = v ;
            std::vector<int> v_merge = v ;
            std::vector<int> v_quick = v ;

            bubblesort(v_bubble) ;

            insertionsort(v_ins) ;

            selectionsort(v_sel) ;

            mergesort(v_merge, 0, k - 1) ;

            quicksort(v_quick, 0, k - 1) ;

            std::sort(v.begin(), v.end()) ;

//        std::cout << "Dimensione " << k << "\n" ;
//        std::cout << "Bubble sort: " << tempo_bubble << "\n" ;
//        std::cout << "Insertion sort: " << tempo_ins << "\n" ;
//        std::cout << "Selection sort: " << tempo_sel << "\n" ;
//        std::cout << "Merge sort: " << tempo_merge << "\n" ;
//        std::cout << "Quick sort: " << tempo_quick << "\n" ;
//        std::cout << "Sort: " << tempo_sort << "\n" ;
//        std::cout << "\n" ;
        }

        double tempo = tc.toc() ;
        double media = tempo / 100 ;


        std::cout << "Dimensione: " << k << "\n" ;
        std::cout << "Tempo medio: " << media << "\n" ;
        std::cout << "\n" ;
    }
}