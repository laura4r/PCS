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

    

    unidirected_graph<int> altro_grafo;
    unidirected_edge<int> a6(1,4);
    unidirected_edge<int> a7(2,5);
    unidirected_edge<int> a8(3,4);
    altro_grafo.add_edge(a2);
    altro_grafo.add_edge(a6);
    altro_grafo.add_edge(a7);
    altro_grafo.add_edge(a8);

    unidirected_graph<int> differenza = grafo - altro_grafo;
    set<unidirected_edge<int>> archi = differenza.all_edges();
    cout << "Differenza: " ;
    for (unidirected_edge<int> arco : archi){
        cout << arco << " ";
    }
    cout << "\n";
    
    return EXIT_SUCCESS ;

}