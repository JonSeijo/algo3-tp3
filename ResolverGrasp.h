#ifndef RESOLVER_GRASP_CONSTRUCTIVA
#define RESOLVER_GRASP_CONSTRUCTIVA

#include <iostream>
#include <vector>
#include "ResolverGreedyVariante.h"
#include "ResolverLocal.h"

using std::vector;

class ResolverGrasp {

public:
    bool leerInput();
    vector<int> resolver(bool imprimirOutput);

private:
	// La mejor solucion hasta el momento
    vector<int> mejor;
    // Lista de adyacencia
    vector<vector<int> > grafo_lst;
     // Matriz de adyacencia
    vector<vector<int> > grafo_ady;
    ResolverGreedyVariante greedy;
    ResolverLocal local;
    // Pre: esClique(clique)
    int frontera(vector<int> &clique);

    // Dummy method para representar la funcion de corte del grasp
    bool valeLaPena(int max);
    int ultimoMax = -1;
    int repetidos = 0;
};

#endif
