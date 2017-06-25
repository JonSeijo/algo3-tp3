#include "ResolverExacta.h"

// Lee el input por stdin y guarda el grafo como lista de adyacencia
// Consideramos que el nodo inicial es 0 para simplificar implementacion.
bool ResolverExacta::leerInput() {
    int n, m;
    std::cin >> n >> m;

    this->n = n;
    this->grafo.clear();
    this->grafo.resize(n, list<int>(0));

    for (int i = 0; i < m; i++) {
        int v1, v2;
        std::cin >> v1 >> v2;

        v1--;
        v2--;

        this->grafo[v1].push_back(v2);
        this->grafo[v2].push_back(v1);
    }

    return true;
}

void ResolverExacta::generarSubconjuntos(list<int> &conjNodos, int act) {

    if (act == this->n) {
        // Si es clique veo si la frontera es maxima
        if (esClique(conjNodos)) {
            int fronteraActual = frontera(conjNodos);
            if (fronteraActual > this->fronteraMax) {
                this->fronteraMax = fronteraActual;
                this->solucion = conjNodos;
            }
        }
        return;
    }

    // No agrego act al conjunto
    generarSubconjuntos(conjNodos, act + 1);

    // Agrego act al conjunto
    conjNodos.push_back(act);
    generarSubconjuntos(conjNodos, act + 1);
    conjNodos.pop_back();
}

void ResolverExacta::resolver(bool imprimirOutput=false) {

    this->solucion.clear();
    this->solucion.resize(0);
    this->fronteraMax = -1;

    /*
    La idea principal es la siguiente:

    solucion = Vacio
    maxFrontera = -1

    Para todo subconjunto S de nodos:
        si (esClique(S)):
            si (frontera(S) > maxFrontera):
                maxFrontera = frontera
                solucion = S

    */

    std::list<int> listaVacia; // Temporal para generar los subconjuntos
    this->generarSubconjuntos(listaVacia, 0);

    if (imprimirOutput) {
        // Recordar que a cada nodo hacerle un +1
        std::cout << fronteraMax << " ";
        std::cout << solucion.size() << " ";
        for (int v : solucion) {
            std::cout << v + 1 << " ";
        }
        std::cout << "\n";
    }
}

// Dice si los nodos forman un grafo completo
// O(n^2)*O(sonVecinos)
bool ResolverExacta::esClique(list<int> &nodos) {
    // Quiero ver si todos los nodos son todos vecinos entre si
    for (int v1 : nodos) {
        for (int v2 : nodos) {
            if (v1 != v2 && !sonVecinos(v1, v2)) {
                return false;
            }

        }
    }
    return true;
}

// Pre: esClique(clique)
// Da la cantidad de aristas que pertenecen a la frontera,
// O(n^2)
int ResolverExacta::frontera(list<int> &clique) {

    vector<bool> enClique(grafo.size(), false);
    for (int v : clique) {
        enClique[v] = true;
    }

    int contador = 0;
    for (int v : clique) {
        for (int vecino : grafo[v]) {
            if (!enClique[vecino]) {
                contador++;
            }
        }
    }
    return contador;
}

bool ResolverExacta::sonVecinos(int v1, int v2) {
    // Optimizacion: recorrer los vecinos del que tiene menor cantidad
    if (grafo[v2].size() < grafo[v1].size()) {
        int tmp = v2;
        v2 = v1;
        v1 = tmp;
    }

    for (int w : grafo[v1]) {
        if (w == v2) {
            return true;
        }
    }
    return false;
}
