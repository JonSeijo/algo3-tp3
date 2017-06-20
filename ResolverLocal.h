#ifndef RESOLVER_LOCAL
#define RESOLVER_LOCAL

#include <iostream>
#include <vector>

#include "ResolverGreedyConstructiva.h"

using std::vector;

class ResolverLocal {

public:
    bool leerInput();
    void copiarInput(ResolverGreedyConstructiva problema);
    vector<int> resolver(bool imprimirOutput, vector<int> inicial);

    vector<int> busquedaLocal(vector<int> &inicial);
    vector<int> maximoPorSwap(vector<int> &inicial, vector<int> &complemento_inicial);
    vector<int> maximoPorAdd(vector<int> &inicial, vector<int> &complemento_inicial);
    vector<int> maximoPorSub(vector<int> &inicial, vector<int> &complemento_inicial);

private:
    vector<vector<int> > grafo_lst; // Lista de adyacencia
    vector<vector<int> > grafo_ady; // Matriz de adyacencia
    int n;

    bool esClique(vector<int> &nodos);

    int frontera(vector<int> &clique); // Pre: esClique(clique)

    bool sonVecinos(int v1, int v2);

    vector<int> complemento(vector<int> &nodos);
};

#endif
