#include "ResolverExacta.h"

bool ResolverExacta::leerInput() {
    // Lee el input por stdin y guarda el grafo como lista de adyacencia
    //     --> QUIZA convenga tenerlo como *matriz* de adyacencia, ver

    int n, m;
    std::cin >> n >> m;

    this->n = n;
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

void ResolverExacta::generarSubconjuntos(vector<int> &s, int tope, int actual) {
    if (actual <= this->n) {
        s[tope] = actual;

        // Tomo el subconjunto actual
        vector<int> subconjNodos(s.begin(), s.begin() + tope);

        // Si es clique veo si la frontera es maxima
        if (esClique(subconjNodos)) {
            int fronteraActual = frontera(subconjNodos);
            if (fronteraActual > this->fronteraMax) {
                this->fronteraMax = fronteraActual;
                this->solucion = subconjNodos;
            }
        }

        // Incluyo el actual en la pila
        generarSubconjuntos(s, tope+1, actual+1) ; /* with actual */

        // No incluyo el actual en la pila
        generarSubconjuntos(s, tope, actual+1) ; /*  without actual */
    }
}

void ResolverExacta::resolver(bool imprimirOutput) {

    this->solucion.clear();
    this->solucion.resize(0);
    this->fronteraMax = -1;

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

    std::vector<int> s(n, 0); // Temporal para generar los subconjuntos

    this->generarSubconjuntos(s, 0, 0);

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
