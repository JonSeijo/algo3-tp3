#include "ResolverLocal.h"
#include "ResolverGreedyConstructiva.h"

// INTERFAZ ++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++

void ResolverLocal::copiarInput(ResolverGreedyConstructiva problema) {
    // El input la lee el objeto 'problema' por la stdin
    this->n = problema.grafo_lst.size();
    this->grafo_lst = problema.grafo_lst;
    this->grafo_ady = problema.grafo_ady;
}

vector<int> ResolverLocal::resolver(bool imprimirOutput, vector<int> solucion) {
    /*
    La función 'búsquedaLocal' es la que explora los vecinos y busca una solución
    mejor. Pero corresponde a una única iteración: explora sólo los vecinos de la
    inicial y nada más. Está función se va a encargar de iterar sobre dicha función
    para continuar mejorándo nuestra solución. Tiene como responsabilidad las
    condiciones de corte.
    */
    int iteraciones = 10;
    int frontera_actual = frontera(solucion);
    for (int t = 1; t <= iteraciones; t++) {
        solucion = busquedaLocal(solucion); // búsqueda local para mejorar la solución
        int frontera_solucion = frontera(solucion);
        if (frontera_actual == frontera_solucion) {
            break; // si no mejoró, corto
        } else {
            frontera_actual = frontera_solucion;
        }
    }
    return solucion;
}


// BÚSQUEDA LOCAL ++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++

// Devuelve la solución vecina de la inicial con mayor frontera.
// Un clique será vecino de otro si se puede conseguir mediante una operación de
// añadir un nodo, eliminar un nodo o swappear un nodo (con el complemento).
vector<int> ResolverLocal::busquedaLocal(vector<int> &inicial) {
    vector<int> complemento_inicial = complemento(inicial);

    vector<int> solucionSwap = maximoPorSwap(inicial, complemento_inicial);

    return solucionSwap;
}

// Maximiza la frontera de los cliques obtenidos al swappear un nodo de la solución inicial
// O(n^2)
vector<int> ResolverLocal::maximoPorSwap(vector<int> &inicial, vector<int> &complemento_inicial) {

    vector<int> candidato = inicial;
    int max_frontera = frontera(inicial);
    int max_i = -1; // -1 implica ningún swap
    int max_j = -1;

    for (size_t i = 0; i < inicial.size(); i++) {
        for (size_t j = 0; j < complemento_inicial.size(); j++) {
            candidato[i] = complemento_inicial[j]; // hacemos el swap
            if (esClique(candidato)) {
                int frontera_candidato = frontera(candidato);
                if (frontera_candidato > max_frontera) {
                    max_i = i; // encontramos un clique mejor, actualizamos máximos
                    max_j = j;
                    max_frontera = frontera_candidato;
                }
            }
            candidato[i] = inicial[i]; // restauramos el candidato
        }
    }

    if (max_i != -1) { // AKA hubo un clique mejor
        candidato[max_i] = complemento_inicial[max_j];
    }

    return candidato;
}


// AUXILIARES ++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++

// Dice si los nodos forman un grafo completo
// O(n^2)
bool ResolverLocal::esClique(vector<int> &nodos) {
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
int ResolverLocal::frontera(vector<int> &clique) {
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

// Devuelve si los dos nodos son vecinos
// O(1)
bool ResolverLocal::sonVecinos(int v1, int v2) {
	return (grafo_ady[v1][v2] == 1);
}

// Devuelve el complemento del conjunto pasado como parámetro
// (sobre el universo de vértices en el grafo)
// O(n)
vector<int> ResolverLocal::complemento(vector<int> &nodos) {
    vector<int> complemento;
    vector<bool> pertenencia(n, false);

    for (size_t i = 0; i < nodos.size(); i++) {
        pertenencia[nodos[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        if (!pertenencia[i]) complemento.push_back(i);
    }

    return complemento;
}