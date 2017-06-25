#ifndef RESOLVER_GREEDY_CONSTRUCTIVA
#define RESOLVER_GREEDY_CONSTRUCTIVA

#include <iostream>
#include <vector>

using std::vector;

class ResolverGreedyConstructiva {

public:
    bool leerInput();
    vector<int> resolver(bool imprimirOutput);

    // Lista de adyacencia para representar al grafo
    vector<vector<int> > grafo_lst;
    vector<vector<int> > grafo_ady;

    bool esClique(vector<int> &nodos);

    // Pre: esClique(clique)
    int frontera(vector<int> &clique);

    bool sonVecinos(int v1, int v2);
};

#endif
