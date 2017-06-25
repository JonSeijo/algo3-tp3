#include "ResolverGreedyVariante.h"

// Lee el input por stdin y guarda el grafo como lista de adyacencia
bool ResolverGreedyVariante::leerInput() {
    int n, m;
    std::cin >> n >> m;
    this->grafo_lst.clear();
    this->grafo_lst.resize(n, vector<int>(0));

    this->grafo_ady.resize(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int v1, v2;
        std::cin >> v1 >> v2;

        v1--;
        v2--;

        this->grafo_lst[v1].push_back(v2);
        this->grafo_lst[v2].push_back(v1);

        this->grafo_ady[v1][v2] = 1;
        this->grafo_ady[v2][v1] = 1;
    }

    return true;
}

vector<int> ResolverGreedyVariante::resolver(int inicial, bool imprimirOutput, bool minimoOutput) {

    int n = grafo_lst.size();
    if (inicial < 0 || inicial >= n) {
        std::cerr << "ResolverGreedyVariante: El nodo inicial: " << inicial << " no es valido!!\n";
        return vector<int>();
    }

    int fronteraMax = -1;
    vector<int> candidatos(0);
    vector<int> solucion(0);
    solucion.push_back(inicial);

    // Agrego todos los nodos al vector de candidatos, exepto el inicial
    for (int i = 0; i < n; i++) {
        if (i != inicial) {
            candidatos.push_back(i);
        }
    }

    while (!candidatos.empty()) {

        int mejor_candidato = -1;
        int fronteraMaxAnterior = fronteraMax;  //La frontera que los candidatos tienen que superar

        //Itero los candidatos
        vector<int>::iterator it = candidatos.begin();

        while (it != candidatos.end()) {    //Itero los candidatos

            solucion.push_back(*it);    //Agrego temporalmente a la solucion

            if (!esClique(solucion)){   //No era clique => lo saco de la solucion y elimino de los candidatos
                it = candidatos.erase(it);
                solucion.pop_back();
                continue;
            }

            int fronteraActual = frontera(solucion);    //Es clique => calculo frontera

            if (fronteraActual < fronteraMaxAnterior){  //La frontera es peor a la que tenia => lo saco de la solucion y elimino de candidatos
                it = candidatos.erase(it);
                solucion.pop_back();
                continue;
            }

            if (fronteraActual >= fronteraMax) {        //La frontera es mayor o igual a la maxima frontera encontrada hasta ahora
                fronteraMax = fronteraActual;           //En caso de que el mejor candidato tenga igual frontera que la anterior me permite hacer cliques mas grandes y seguir buscando en vez de parar alli
                mejor_candidato = it - candidatos.begin();
            }
            ++it;
            solucion.pop_back();
        }

        // Hay un mejor candidato => lo agrego definitivamente a la solucion y lo quito de candidatos
        if (mejor_candidato != -1) {
            solucion.push_back(candidatos[mejor_candidato]);
            candidatos.erase(candidatos.begin() + mejor_candidato);
        }
    }

    if (imprimirOutput) {
        std::cout << fronteraMax << " ";
        std::cout << solucion.size() << " ";
        for (int v : solucion) {
            std::cout << v + 1 << " ";
        }
        std::cout << "\n";
    }

    // @DEBUG, esto es para las mediciones, borrar luego
    if (minimoOutput) {
        std::cout << fronteraMax << ",";
        std::cout << solucion.size();
    }

    return solucion;
}

// Dice si los nodos forman un grafo completo
// O(n^2)*O(sonVecinos)
bool ResolverGreedyVariante::esClique(vector<int> &nodos) {
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
int ResolverGreedyVariante::frontera(vector<int> &clique) {

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

bool ResolverGreedyVariante::sonVecinos(int v1, int v2) {
    return (grafo_ady[v1][v2] == 1);
}
