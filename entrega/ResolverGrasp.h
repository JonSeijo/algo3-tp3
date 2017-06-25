#ifndef RESOLVER_GRASP
#define RESOLVER_GRASP

#include <iostream>
#include <vector>
#include "ResolverGreedyGrasp.h"
#include "ResolverLocal.h"

using std::vector;

class ResolverGrasp {

public:
    bool leerInput();
    vector<int> resolver(double alpha, bool imprimirOutput, bool minimoOutput=false);

private:
	// La mejor solucion hasta el momento
    vector<int> mejor;
    // Lista de adyacencia
    vector<vector<int> > grafo_lst;
     // Matriz de adyacencia
    vector<vector<int> > grafo_ady;
    ResolverGreedyGrasp greedy;
    ResolverLocal local;
    // Pre: esClique(clique)
    int frontera(vector<int> &clique);

    int ultimoMax = -1;
    int repetidos = 0;
};

#endif
