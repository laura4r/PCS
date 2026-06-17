/* algoritmo di De Pina: costruisco la base di cicli minimi di un grafo pesato G */

#pragma once
#include <vector>
#include <limits>
#include "dijkstra.hpp"

using namespace std;

/* S dot P in modulo 2, S, P vettori di booleani */
bool prodotto_scalare(vector<bool> S, vector<bool> P)
{
	int N=S.size(); /* N=lunghezza di S */
	int sum = 0;
	for (int i = 0 ; i < N ; i++ ) {
		sum = sum + (S[i] * P[i]);
	}
	int ret = sum % 2 ;
	return (ret == 1);
	/* risultato=0 se S,P hanno un numero pari di 1 in posizioni corrispondenti, 1 se il numero è dispari */
};

/* XOR: differenza simmetrica tra S,P vettori di booleani */
vector<bool> differenza_simmetrica(vector<bool> S, vector<bool> P)
{
	int N = S.size();
	vector<bool> ret(N);
	for (int i = 0; i < N ; i++) {
		if (S[i] == P[i]) {
			ret[i] = false ; /* =0 se S=P */
		}
		else {
			ret[i] = true ; /* =1 se S!=P */
		}
	}
	return ret;
};

int piu(int v) /* +v=2*v */
{
    return 2 * v;
};

int meno(int v) /* -v=2*v+1 */
{
    return 2 * v + 1;
};

vector<bool> cicli_minimi(weighted_graph grafo, vector<bool> Si) /* Si vettori booleani */
{
    weighted_graph G1; /* grafo ausiliario */
	for (unidirected_edge<int> arco : grafo.all_edges()) {
		int j = grafo.edge_number(arco) ; /* indice dell'arco */
        double w = grafo.peso_arco(arco) ; /* peso dell'arco */
        int u = arco.from() ; /* nodo di partenza */
        int v = arco.to() ; /* nodo di arrivo */
		/* costruisco il grafo ausiliario G1 per ogni Si */
		if (Si[j]) { /* se Si[j]=true=1 -> se l'arco è attivo in Si */
			G1.add_edge(piu(u) , meno(v) , w);
			G1.add_edge(meno(u) , piu(v) , w);
		}
		else {
			G1.add_edge(piu(u) , piu(v) , w);
            G1.add_edge(meno(u) , meno(v) , w);
        }
	}
	int m=(grafo.all_edges()).size(); /* numero degli archi */
	int best_size = numeric_limits<int>::max(); 
	vector<bool> best_cycle(m , false); /* per memorizzare il miglior ciclo trovato finora */
    for (int v : grafo.all_nodes()) {
        dijkstra_result result = dijkstra(G1 , piu(v)); /* cerco il cammino minimo da v+ a v- nel grafo ausiliario */
        auto pred = result.pred; /* predecessore */
        auto dist = result.dist; /* distanza */
        vector<int> cammino;
        int cur = meno(v); /* parto da -v */
		if (pred[cur] == cur && cur !=piu(v)) {
			continue; /* se non esiste un cammino da v+ a v-, vado al nodo successivo */
		}
		/* trasformo il cammino in un ciclo del grafo originale */
		/* ricostruisco il cammino */
        while (cur != piu(v)) {
            cammino.push_back(cur);
            cur=pred[cur];
        }
        cammino.push_back(piu(v));
		vector<bool> C_mu(m,false); /* vettore di incidenza */
		for (int i = 0; i < cammino.size() - 1 ; i++ ) {
			int u=cammino[i]/2; /* nodo di partenza originale */
			int v=cammino[i+1]/2; /* nodo di arrivo originale */
			unidirected_edge<int> arco(u,v);
			int id=grafo.edge_number(arco); /* numero dell'arco */
			C_mu[id] = C_mu[id] ^ true ; /* XOR così lo stesso arco non appare più volte */
		}
		/* conto i true == 1 -> conservo il C_mu con il numero più piccolo di elementi 1 che sarà il ciclo minimo */
		int h=0;
		for (int x:C_mu) {
			h = h + x ; /* h=numero archi nel ciclo */
		}
		if (h < best_size) {
			best_size = h;
			best_cycle = C_mu;
		}
	}
	return best_cycle; /* ciclo minimo */
};

vector<vector<bool>> de_pina(weighted_graph grafo, vector<vector<bool>>& S) {
    int k=(grafo.all_edges()).size()-(grafo.all_nodes()).size()+1; /* k=m-n+1, m archi, n nodi */
    vector<vector<bool>> B(k); /* base dei cicli k */
	vector<vector<bool>> S_new=S;
    for(int i=0;i<k;i++) {
        B[i]=cicli_minimi(grafo,S_new[i]); /* trovo il ciclo minimo che soddisfi S_new=S e lo aggiungo alla base */
		/* aggiorno S */
		for (int j=i+1;j<k;j++) {
			if (prodotto_scalare(B[i],S_new[j])) { /* se vale 1 */
				S_new[j]=differenza_simmetrica(S_new[j],S_new[i]); /* -> così gli S rimangono indipendenti */
			}
		}
	}
	S=S_new;
	return B;
}