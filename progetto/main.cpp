#include <vector>
#include "dfs.hpp"
#include "sistema_lineare.hpp"
#include <Eigen/Dense>
#include <Eigen/SVD>

using namespace std ;
using namespace Eigen ;

int main(int argc, char* argv[]){
    
/*Lettura del file di input*/

    string fileName = argv[1] ;          // Lettura input da terminale (nome del file)

    pair<vector<dati> , vector<dati>> componenti = read_netlist(fileName) ;       // lettura del file di input

/*Costruzione del grafo*/

    auto generatori = componenti.first ;
    auto resistenze = componenti.second ;

    weighted_graph circuito ;

    for(auto generatore : generatori) {
        circuito.add_edge(generatore.nodo1 , generatore.nodo2 , generatore.peso) ;
    }

    for(auto resistenza : resistenze) {
        circuito.add_edge(resistenza.nodo1 , resistenza.nodo2 , resistenza.peso) ;
    }

/*Creazione albero di ricoprimento*/

    int sorgente = generatori[0].nodo1 ;         // scelto arbitrariamente
    lifo<int> contenitore ;

    weighted_graph albero = dfs(circuito , sorgente , contenitore) ;

/*Creazione del coalbero*/

    weighted_graph coalbero = circuito - albero ;


/*Ricerca delle maglie (i.e. dei cicli minimi)*/

    //Costruzione dell'input di De Pina

    const int m = (circuito.all_edges()).size() ;
    const int k = m - (circuito.all_nodes()).size() + 1 ;

    vector<vector<bool>> S(k , vector<bool>(m , false)) ;
    
    int indice = 0;
    for (unidirected_edge<int> arco : circuito.all_edges()){
        int j = circuito.edge_number(arco);
        if ((coalbero.all_edges()).contains(arco)){
            if (indice < k){
                S[indice][j] = true;
                indice ++;
                }
            }
        }


    vector<vector<bool>> base_cicli = de_pina(circuito , S) ;


/*Costruzione del sistema lineare*/
    MatrixXd B = crea_B(resistenze , base_cicli , circuito) ;
    MatrixXd R = crea_R(resistenze) ;

    VectorXd v = crea_v(generatori , base_cicli , circuito) ;

/*Risoluzione del sistema lineare*/
    VectorXd I = sistema_lineare(B , R , v) ;

/*Calcolo delle tensioni*/
    VectorXd v_R = calcolo_tens(R , B , I) ;

/*Output*/
    for(int i = 0 ; i < resistenze.size() ; i++) {
        cout << resistenze[i].nome << ": V = " << v_R(i) << "volts, I = " << (v_R[i])/(resistenze[i].peso) << " amps." << "\n" ;
    }
    return 1;
}