#ifndef RESOLVER_GREEDY_GRASP
#define RESOLVER_GREEDY_GRASP

#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

using std::vector;
using std::pair;

const int INFINITO = INT_MAX;

class ResolverGreedyGrasp {

public:
    bool leerInput();
    vector<int> resolver(double alpha, bool imprimirOutput=false, bool minimoOutput=false);

    // Lista de adyacencia para representar al grafo
    vector<vector<int> > grafo_lst;
    vector<vector<int> > grafo_ady;

    bool esClique(vector<int> &nodos);

    // Pre: esClique(clique)
    int frontera(vector<int> &clique);

    bool sonVecinos(int v1, int v2);

private:
    bool DEBUG_MODE;
};

#endif
