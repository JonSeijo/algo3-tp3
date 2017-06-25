#ifndef RESOLVER_EXACTA
#define RESOLVER_EXACTA

#include <iostream>
#include <vector>
#include <list>

using std::vector;
using std::list;

class ResolverExacta {

public:
    bool leerInput();
    void resolver(bool imprimirOutput);

private:
    // Lista de adyacencia para representar al grafo
    vector<list<int> > grafo;
    int n;
    int fronteraMax;
    list<int> solucion;

    void generarSubconjuntos(list<int> &conjNodos, int act);
    bool esClique(list<int> &nodos);
    // Pre: esClique(clique)
    int frontera(list<int> &clique);
    bool sonVecinos(int v1, int v2);
};

#endif
