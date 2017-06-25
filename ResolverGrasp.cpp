#include "ResolverGrasp.h"
#include <stdlib.h>

bool ResolverGrasp::leerInput() {
    // El input la lee el objeto 'greedy' por la stdin
    bool leyoCorrectamente = greedy.leerInput();
    local.copiarInput(greedy);
    this->grafo_lst = greedy.grafo_lst;
    this->grafo_ady = greedy.grafo_ady;
    return leyoCorrectamente;
}

// REPES podria ser un parametro
vector<int> ResolverGrasp::resolver(double alpha_in, bool imprimirOutput, bool minimoOutput) {

    double alpha = alpha_in;
    int repsGrasp = 50;

    vector<int> actual;
    int fronteraMax = 0;
    int fronteraNueva = 0;

    for (int repes = 0; repes < repsGrasp; repes++) {
        actual = greedy.resolver(alpha, false, false);
        vector<int> nueva = local.resolver(false, actual);

        fronteraNueva = frontera(nueva);
        if (fronteraNueva > fronteraMax) {
            mejor = nueva;
            fronteraMax = fronteraNueva;
        }
    }

    if (imprimirOutput) {
        std::cout << fronteraMax << " ";
        std::cout << mejor.size() << " ";
        for (int v : mejor) {
            std::cout << v + 1 << " ";
        }
        std::cout << "\n";
        std::cout <<"cantidad: " << repsGrasp << "\n";
    }

    if (minimoOutput) {
        std::cout << fronteraMax << ",";
        std::cout << mejor.size();
    }

    return mejor;
}

// Pre: esClique(clique)
// Da la cantidad de aristas que pertenecen a la frontera,
// O(n^2)
int ResolverGrasp::frontera(vector<int> &clique) {

    vector<bool> enClique(grafo_lst.size(), false);
    for (int v : clique) {
        enClique[v] = true;
    }

    int contador = 0;
    for (int v : clique) {
        for (int vecino : grafo_lst[v]) {
            if (!enClique[vecino]) {
                contador++;
            }
        }
    }
    return contador;
}
