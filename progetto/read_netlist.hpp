#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

/* Creo una struttura che rappresenta un elemento della netlist */
struct dati{
    string nome;
    double peso;
    int nodo1;  
    int nodo2;
};

pair<vector<dati>, vector<dati>> read_netlist(string netlist)
{
    ifstream ifs(netlist);
    vector<dati> generatori;
    vector<dati> resistenze;

    if (ifs.is_open()){ 
        string nome;
        double peso;
        int nodo1;
        int nodo2;

        // Leggo il file riga per riga: ogni riga è un componente
        while (!ifs.eof()){
            // Leggo i dati del componente
            if(! (ifs >> nome >> peso >> nodo1 >> nodo2)){
                continue;
            }

            if (nome.starts_with("V")){  // Se inizia con "V" è un generatore
                dati arco = {nome, peso, nodo1, nodo2};
                generatori.push_back(arco);
            }
            else if (nome.starts_with("R")){  // Se inizia con "R" è una resistenza
                dati arco = {nome, peso, nodo1, nodo2};
                resistenze.push_back(arco);
            }
            else {  // Se non è riconosciuto, lo ignoro
                continue;
            }
        }
    }
    else{
        cerr << "Errore: impossibile aprire il file!\n";
    }

    // Restituisco separatamente generatori e resistenze
    pair<vector<dati>,vector<dati>> ret{generatori, resistenze};
    return ret;
}