#pragma once
#include "de_pina.hpp"
#include "read_netlist.hpp"
#include "gradiente_coniugato.hpp"
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <map>
#include <vector>
#include <utility>

using namespace std ;
using namespace Eigen ;     // alleggerimento codice

// FUNZIONE AUSILIARIA: Ricostruisce il cammino del ciclo e ne determina l'orientamento.
// Ritorna una mappa che, per ogni coppia ordinata di nodi (u, v) attraversati, assegna 1 se la maglia va da u a v, e -1 se va da v a u.
std::map<std::pair<int, int>, int> orienta_maglia(const std::vector<bool>& maglia, const weighted_graph& grafo) {    // passaggio by const reference
    std::map<int, std::vector<int>> cycle_adj;
    
    // ricostr della lista di adiacenza ristretta solo ai rami della maglia corrente
    for (int k = 0; k < maglia.size(); ++k) {
        if (maglia[k]) {
            unidirected_edge<int> e = grafo.edge_at(k);
            cycle_adj[e.from()].push_back(e.to());
            cycle_adj[e.to()].push_back(e.from());
        }
    }

    std::map<std::pair<int, int>, int> edge_dir;
    if (cycle_adj.empty()) return edge_dir;

    //scelta nodo di partenza e iniziamo a percorrere il ciclo
    int start = cycle_adj.begin() -> first;
    int curr = start;
    int next = cycle_adj[curr][0]; // Scegliamo arbitrariamente il primo vicino come direzione positiva

    while (true) {
        // Registriamo il verso: la maglia si muove da 'curr' a 'next'
        edge_dir[{curr, next}] = 1;
        edge_dir[{next, curr}] = -1;

        if (next == start) break; // Ciclo completato

        // Avanziamo al nodo successivo
        int prev = curr;
        curr = next;
        
        // Scegliamo il vicino che non sia il nodo da cui siamo appena venuti
        if (cycle_adj[curr][0] != prev) {
            next = cycle_adj[curr][0];
        } else {
            next = cycle_adj[curr][1];
        }
    }
    return edge_dir;
}

/* Costruzione matrice di incidenza */
Eigen::MatrixXd crea_B(auto resistenze , auto base_cicli , weighted_graph grafo) {    // passaggio by value
    int m = resistenze.size() ;    // numero di resistori
    int n = base_cicli.size() ;    // numero di maglie

    MatrixXd B = MatrixXd::Zero(m , n) ; 

    for(int j = 0 ; j < n ; j++) {
        vector<bool> maglia = base_cicli[j] ;
        
        // Calcoliamo l'orientamento dei rami per la maglia j-esima con la funzione ausiliaria
        std::map<std::pair<int, int>, int> direzione_maglia = orienta_maglia(maglia, grafo);

        for(int i = 0 ; i < m ; i++) {
            int nodo1 = resistenze[i].nodo1 ;
            int nodo2 = resistenze[i].nodo2 ;

            unidirected_edge<int> arco (nodo1 , nodo2) ;
            int k = grafo.edge_number(arco) ;

            if(maglia[k]){
                // Usiamo l'orientamento dinamico della maglia:
                // Se la maglia percorre il ramo da nodo1 a nodo2, restituisce 1.
                // Se lo percorre al contrario (da nodo2 a nodo1), restituisce -1.
                B(i,j) = direzione_maglia[{nodo1, nodo2}];
            }
        }
    }
    return B ;
} ;


MatrixXd crea_R(auto resistenze) {    // passaggio by value
    int m = resistenze.size() ;
    MatrixXd R = MatrixXd::Zero(m,m) ;

    for(int i = 0 ; i < m ; i++) {
        R(i,i) = resistenze[i].peso ;
    }
    return R ;
} ;


VectorXd crea_v(auto generatori , auto base_cicli, weighted_graph grafo) {    // passaggio by value
    int n_maglie = base_cicli.size() ;
    VectorXd v = VectorXd::Zero(n_maglie) ;

    for(int j = 0 ; j < n_maglie ; j++) {
        vector<bool> maglia = base_cicli[j] ;           // vettore di booleani che determina se ciascuna maglia contiene o meno un arco
        
        // Calcoliamo l'orientamento degli archi per la maglia j-esima
        std::map<std::pair<int, int>, int> direzione_maglia = orienta_maglia(maglia, grafo);

        double somma_generatori = 0.0;
        for (int g = 0; g < generatori.size(); g++){
            int n1 = generatori[g].nodo1;
            int n2 = generatori[g].nodo2;

            unidirected_edge<int> arco_generatore(n1, n2);
            int k = grafo.edge_number(arco_generatore);

            if (maglia[k]){
                // Se il verso di percorrenza della maglia concorda con l'orientamento del generatore (da n1 a n2),
                // direzione_maglia[{n1, n2}] sarà 1, quindi sottraiamo il potenziale
                // Se discorda, sarà -1, quindi sommiamo il potenziale
                somma_generatori -= direzione_maglia[{n1, n2}] * generatori[g].peso;
            }
        }
        v(j) = somma_generatori;
    }
    return v ;
} ;

// costruzione dei dati del sistema lineare + risoluzione
VectorXd sistema_lineare(auto B , auto R , auto v) {     // passaggio by value
    MatrixXd A = B.transpose() * R * B ;
    int n = A.rows();

    const double res_tol = 1.0e-12 ;

    VectorXd I = grad_c(A , v , res_tol , n) ;

    return I ;
} ;

// calcolo dei dati di output
VectorXd calcolo_tens(auto R , auto B , auto I) {      // passaggio by value
    VectorXd v_R = R * B * I ;
    return v_R ;
}