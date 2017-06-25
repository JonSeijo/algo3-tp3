#ifndef RESOLVER_GREEDY_VARIANTE
#define RESOLVER_GREEDY_VARIANTE

#include <iostream>
#include <vector>

using std::vector;

class ResolverGreedyVariante {

public:
    bool leerInput();
    vector<int> resolver(int inicial,bool imprimirOutput=false);

    // Lista de adyacencia para representar al grafo
    vector<vector<int> > grafo_lst;
    vector<vector<int> > grafo_ady;

    bool esClique(vector<int> &nodos);

    // Pre: esClique(clique)
    int frontera(vector<int> &clique);

    bool sonVecinos(int v1, int v2);
};

#endif
