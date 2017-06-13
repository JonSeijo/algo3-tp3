#ifndef RESOLVER_LOCAL
#define RESOLVER_LOCAL

#include <iostream>
#include <vector>

#include "ResolverGreedyConstructiva.h"

using std::vector;

class ResolverLocal {

public:
    void copiarInput(ResolverGreedyConstructiva problema);
    vector<int> resolver(bool imprimirOutput, vector<int> inicial);

private:
    vector<vector<int> > grafo_lst; // Lista de adyacencia
    vector<vector<int> > grafo_ady; // Matriz de adyacencia
    int n;

    bool esClique(vector<int> &nodos);

    // Pre: esClique(clique)
    int frontera(vector<int> &clique);

    bool sonVecinos(int v1, int v2);
};

#endif
