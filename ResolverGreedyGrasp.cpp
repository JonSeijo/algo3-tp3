#include "ResolverGreedyGrasp.h"

bool ResolverGreedyGrasp::leerInput() {
    // Lee el input por stdin y guarda el grafo como lista de adyacencia
    //     --> Quiza convenga tenerlo como *matriz* de adyacencia, ver

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

vector<int> ResolverGreedyGrasp::resolver(double alpha, bool imprimirOutput, bool minimoOutput) {
    DEBUG_MODE = false;

    int n = grafo_lst.size();

    int fronteraMax = -1;

    vector<int> candidatosInicial(0);
    // Agrego todos los nodos al vector de candidatos, exepto el inicial
    for (int i = 0; i < n; i++) {
        candidatosInicial.push_back(i);
    }

    vector<int> solucion(0);

    // Un unico nodo cualquiera es clique
    bool puedoConstruirClique = true;

    while (puedoConstruirClique && candidatosInicial.size() > 0) {
        puedoConstruirClique = false;

        vector<pair<int, int> > candidatos(0);
        vector<int> RCL(0); // Random Candidate List

        auto it = candidatosInicial.begin();
        while (it != candidatosInicial.end()) {

            int v = *it;
            solucion.push_back(v);

            // Si el nuevo nodo con la solucion preexistente forma clique, entonces es candidato
            if (esClique(solucion)) {

                int front = frontera(solucion);
                candidatos.push_back(std::make_pair(front, v));

                puedoConstruirClique = true;
                it++;

            } else {
                it = candidatosInicial.erase(it);
            }

            solucion.pop_back();
        }

        // Calculo fronteras minimas y maximas entre mis candidatos, para usar en RCL
        int frontera_min_tmp = INFINITO;
        int frontera_max_tmp = -1;
        for (auto cand : candidatos) {
            frontera_min_tmp = std::min(frontera_min_tmp, cand.first);
            frontera_max_tmp = std::max(frontera_max_tmp, cand.first);
        }

        // Construyo la Random Candidate List de GRASP
        // alpha = 0 --> Greedy 100%
        // alpha = 1 --> Random 100%
        for (auto cand : candidatos) {
            if (cand.first >= frontera_max_tmp + int(alpha*(frontera_min_tmp - frontera_max_tmp))) {
                RCL.push_back(cand.second);
            }
        }

        if (puedoConstruirClique) {
            // Agrego a la solucion un elemento random de la RCL
            int randomIndex = rand() % RCL.size();
            solucion.push_back(RCL[randomIndex]);

            // Quito el nuevo elemento de la vieja lista de candidatos
            candidatosInicial.erase(std::find(candidatosInicial.begin(), candidatosInicial.end(), RCL[randomIndex]));
        }
    }

    fronteraMax = frontera(solucion);

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
bool ResolverGreedyGrasp::esClique(vector<int> &nodos) {
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
int ResolverGreedyGrasp::frontera(vector<int> &clique) {

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

bool ResolverGreedyGrasp::sonVecinos(int v1, int v2) {
    return (grafo_ady[v1][v2] == 1);
}
