#include <iostream>
#include "unidirected_graph.hpp"

using namespace std;

int main(void)
{
    unidirected_edge<int> a1(1,2);
    unidirected_edge<int> a2(1,3);
    unidirected_edge<int> a3(2,4);
    unidirected_edge<int> a4(5,1);
    unidirected_edge<int> a5(4,5);

    

    unidirected_graph<int> grafo;
    grafo.add_edge(a1);
    grafo.add_edge(a2);
    grafo.add_edge(a3);
    grafo.add_edge(a4);
    grafo.add_edge(a5); 

    

    cout << "Numerazione a3: " << grafo.edge_number(a3) << "\n";
    
    
    return EXIT_SUCCESS ;

}