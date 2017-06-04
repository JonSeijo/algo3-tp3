#include "ResolverExacta.h"

bool ResolverExacta::leerInput() {
    // Lee el input por stdin y guarda el grafo como lista de adyacencia
    //     --> QUIZA convenga tenerlo como *matriz* de adyacencia, ver

    int n, m;
    std::cin >> n >> m;

    this->grafo.clear();
    this->grafo.resize(n, vector<int>(0));

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

void ResolverExacta::resolver(bool imprimirOutput) {

    /*
    La idea es la siguiente:

    solucion = Vacio
    maxFrontera = -1

    Para todo subconjunto S de nodos:
        si (esClique(S)):
            si (frontera(S) > maxFrontera):
                maxFrontera = frontera
                solucion = S

    */

    // @jonno
    // Voy a generar todos los subconjuntos usando numeros binarios. 1 representa que el elemento esta.
    // Seguro hay formas mas elegantes pero es la forma que conozco, cambiarla si se quiere.
    // Esto ASUME que n < 32 (pues uso ints)

    int n = grafo.size();

    vector<int> solucion;
    int fronteraMax = -1;

    for (int i = 0; i < (1 << n); i++) {

        vector<int> conjNodos;

        for (int j = 0; j < n; j++) {
            // Si el bit j esta encendido, considero que el nodo j existe
            if ((i & (1 << j)) != 0) {
                conjNodos.push_back(j);
            }
        }

        if (esClique(conjNodos)) {
            int fronteraActual = frontera(conjNodos);
            if (fronteraActual > fronteraMax) {
                fronteraMax = fronteraActual;
                solucion = conjNodos;
            }
        }
    }


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
bool ResolverExacta::esClique(vector<int> &nodos) {
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
int ResolverExacta::frontera(vector<int> &clique) {

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
