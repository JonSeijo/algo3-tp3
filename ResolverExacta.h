#ifndef SOLUCION_EXACTA
#define SOLUCION_EXACTA

#include <iostream>
#include <vector>

using std::vector

class SolucionExacta {

public:
    bool leerInput(bool imprimirOutput);
    void resolver();

private:
    // Lista de adyacencia para representar al grafo
    vector<vector<int> > vecinos;

    bool esClique(vector<int> &nodos);

    // Pre: esClique(clique)
    int frontera(vector<int> &clique);
};

#endif