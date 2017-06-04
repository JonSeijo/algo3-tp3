#include "ResolverExacta.h"

bool ResolverExacta::leerInput() {
    // Lee el input por stdin y guarda el grafo como lista de adyacencia
    //     --> QUIZA convenga tenerlo como matriz de adyacencia, ver
    return false
}

void ResolverExacta::resolver(bool imprimirOutput) {
    // La idea es la siguiente:

    /*
    solucion = Vacio
    maxFrontera = -1

    Para todo subconjunto S de nodos:
        si (esClique(S)):
            si (frontera(S) > maxFrontera):
                maxFrontera = frontera
                solucion = S

    */
}

bool ResolverExacta::esClique(vector<int> &nodos) {
    // Dice si los nodos forman un grafo completo
    // Esperado: O(n + m)
}

// Pre: esClique(clique)
int ResolverExacta::frontera(vector<int> &clique) {
    // Da la cantidad de aristas que pertenecen a la frontera,
    //  (asumiendo que clique es una clique)
    // Esperado: O(n + m)
    return -1;
}
