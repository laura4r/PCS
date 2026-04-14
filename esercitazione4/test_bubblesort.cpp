#include <iostream>
#include <vector>
#include <cstdlib>
#include "sorted.hpp"
#include "bubblesort.hpp"
#include "randfiller.h"

int main(void) {
    randfiller rf ;
    for(int i = 0 ; i < 100 ; i++) {
        int n = rand() % 100 + 1 ;
        std::vector<int> vi ;
        vi.resize(n) ;

        rf.fill(vi, -50, 50) ;

        vi = bubblesort(vi) ;

        if(is_sorted(vi)){
            continue ;
        }
        else {
            return EXIT_FAILURE ;
        }
    }
    std::vector<std::string> vs = {"Ciao", "bello" , "SOLE", "Laura", "benedetta", "LUNA" , "PCS" , "buongiorno", "buonanotte", "pecore"} ;
    vs = bubblesort(vs) ;
    if(! is_sorted(vs)) {
        return EXIT_FAILURE ;
    }

    return EXIT_SUCCESS ;
}