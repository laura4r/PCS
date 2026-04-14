#include <iostream>
#include <algorithm>
#include <vector>
#include "bubblesort.hpp"
#include "insertionsort.hpp"
#include "selectionsort.hpp"
#include "timecounter.h"
#include "randfiller.h"


int main(void){
    randfiller rf ;
    timecounter tc ;

    for(int i = 2; i <= 13 ; i++) {
        int k = std::pow(2,i) ;
        std::vector<int> v ;
        v.resize(k) ;
        rf.fill(v, -50, 50) ;

        tc.tic() ;
        std::vector<int> v_bubble = bubblesort(v) ;
        double tempo_bubble = tc.toc() ;


        tc.tic() ;
        std::vector<int> v_ins = insertionsort(v) ;
        double tempo_ins = tc.toc() ;

        tc.tic() ;
        std::vector<int> v_sel = selectionsort(v) ;
        double tempo_sel = tc.toc() ;

        tc.tic() ;
        std::sort(v.begin(), v.end()) ;
        double tempo_sort = tc.toc() ;


        std::cout << "Dimensione: " << k << "\n" ;
        std::cout << "Bubble sort: " << tempo_bubble << "\n" ;
        std::cout << "Insertion sort: " << tempo_ins << "\n" ;
        std::cout << "Selection sort: " << tempo_sel << "\n" ;
        std::cout << "Sort: " << tempo_sort << "\n" ;
        std::cout << "\n" ;
    }
}