#ifndef RESOLVER_EXACTA
#define RESOLVER_EXACTA

#include <iostream>
#include <vector>

using std::vector;

class ResolverExacta {

public:
    bool leerInput();
    void resolver(bool imprimirOutput);

private:
    // Lista de adyacencia para representar al grafo
    vector<vector<int> > grafo;

    bool esClique(vector<int> &nodos);

    // Pre: esClique(clique)
    int frontera(vector<int> &clique);

    bool sonVecinos(int v1, int v2);
};

#endif