#pragma once
#include <set>
#include <map>
#include "unidirected_edge.hpp"

class weighted_graph
{
    std::set<int> nodi;
    // Ad ogni chiave (nodo) associo un valore (insieme di coppie arco-peso)
    std::map<int, std::set<std::pair<unidirected_edge<int>, double>>> archi;
public:
    /* Costruttore di default */
    weighted_graph() = default;
    
    /* Costruttore di copia */
    weighted_graph(const weighted_graph& other) = default;

    /* Restituisco i valori dei vicini */
    std::set<int> neighbours(const int nodo) const {
        std::set<int> ret;

        // Cerco gli archi che partono dal nodo
        if(archi.contains(nodo)){
            for (auto vicino : archi.at(nodo)){
                ret.insert((vicino.first).to()); // Inserisco il nodo di arrivo
            }
        }

        // Cerco gli archi che arrivano nel nodo
        for (int altro_n : nodi){
            if (!archi.contains(altro_n)){
                continue;
            }
            if (altro_n < nodo){  // Controllo i nodi precedenti
                for (auto arco : archi.at(altro_n)){
                    if ((arco.first).to() == nodo){
                        ret.insert(altro_n);
                        break;  // Trovato l'arco, passa al prossimo nodo
                    }
                }
            }
        }
        return ret;
    }

    /* Restituisco il peso di un arco dato */
    double peso_arco(const unidirected_edge<int>& arco) const {
        int inizio = arco.from();

        // Controllo se esistono archi che partono da "inizio"
        if (archi.contains(inizio)) {   
            for (auto arco_w : archi.at(inizio)){
                if (arco_w.first == arco){
                    double peso = arco_w.second;
                    return peso;
                }
            }    
        }
    }

    /* Aggiungo un arco pesato al grafo */
    weighted_graph add_edge(int nodo1, int nodo2, double peso) {
        unidirected_edge<int> arco (nodo1, nodo2); 
        std::pair<unidirected_edge<int>, double> arco_w {arco, peso};

        // Gestisco il nodo di partenza
        if (nodi.contains(arco.from())){
            if (archi.contains(arco.from())){
                archi[arco.from()].insert(arco_w); // Inserisco l'arco nell'insieme
            }
            else {
                archi[arco.from()] = {arco_w}; // Creo l'arco pesato
            }
        }
        else{
            nodi.insert(arco.from());
            archi[arco.from()] = {arco_w};
        }

        // Gestisco il nodo di arrivo
        if (!nodi.contains(arco.to())){
            nodi.insert(arco.to());
        }

        return *this; // Restituisco il grafo modificato
    }
    
    /* Restituisco l'insieme di tutti i nodi del grafo */
    std::set<int> all_nodes() const{
        return nodi;
    }

    /* Restituisco l'insieme di tutti gli archi (senza pesi) */
    std::set<unidirected_edge<int>> all_edges() const{
        std::set<unidirected_edge<int>> ret;
        for (const auto [nodo, adiacenti] : archi){
            for (auto [arco, peso] : adiacenti){
                ret.insert(arco);
            }
        }
        return ret;
    }

    /* Implementazione dell'operatore - di differenza */
    weighted_graph operator-(const weighted_graph& other) const {
        weighted_graph res;
        
        // Genero un nuovo grafo che contiene solo gli archi di grafo e non di "other"
        for (const auto& [nodo, adiacenti] : archi) {
            for (const auto& arco : adiacenti) {
                int vicino = (arco.first).to();
                double peso = arco.second;

                // Aggiungo gli archi che sono in grafo ma non in other
                if (!other.neighbours(nodo).contains(vicino)) {
                    res.add_edge(nodo, vicino, peso);
                }
            }
        }
    return res;
    }

    /* Restituisco la numerazione dell'arco secondo l'ordine lessicografico*/
    int edge_number(const unidirected_edge<int>& arco) const{
        int num = 0;

        // Conto gli archi dei nodi con etichetta più piccola del nodo di partenza
        for (const auto [nodo, adiacenti] : archi){
            if (nodo < arco.from()){
                num = num + adiacenti.size();
            }
        }
        int partenza = arco.from();

        // Conto gli archi dello stesso nodo di partenza che lo precedono
        for (auto altro_arco : archi.at(partenza)){
            if(altro_arco.first < arco){
                num = num + 1;
            }
        }
        return num;
    }

    /* Restituisco l'arco data la numerazione */
    unidirected_edge<int> edge_at(int num) const{
        for (const auto [nodo, adiacenti] : archi){
            for (auto arco_w : adiacenti){
                unidirected_edge<int> arco = arco_w.first;

                // Se l'indice calcolato coincide con quello cercato restituisce l'arco
                if (edge_number(arco) == num){
                    return arco;
                }
            }
        }
    }
};