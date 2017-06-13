#include "ResolverLocal.h"
#include "ResolverGreedyConstructiva.h"

void ResolverLocal::copiarInput(ResolverGreedyConstructiva problema) {
    // El input la lee el objeto 'problema' por la stdin
    this->n = problema.grafo_lst.size();
    this->grafo_lst = problema.grafo_lst;
    this->grafo_ady = problema.grafo_ady;
}

vector<int> ResolverLocal::resolver(bool imprimirOutput, vector<int> inicial) {

    /*
    La idea va a ser maximizar la frontera en la vecindad de nuestra solución inicial.
    Un clique será vecino de otro si se puede conseguir mediante una operación de
    añadir un nodo, eliminar un nodo o swappear un nodo (con el complemento).
    */
    
    vector<int> solucion(0);

    /*int n = grafo_lst.size();

    int fronteraMax = -1;
    
    vector<int> candidatos(0);

    for (int i = 0; i < n; i++) {
    	candidatos.push_back(i);	//Agrego todos los nodos al vector de candidatos
    }
    
    while (!candidatos.empty()) {

    	int mejor_candidato = -1;
    	
    	vector<int>::iterator it = candidatos.begin();
    	
    	int fronteraMaxAnterior = fronteraMax;	//La frontera que los candidatos tienen que superar
    	
    	while (it != candidatos.end()) {	//Itero los candidatos
    	
    		solucion.push_back(*it);	//Agrego temporalmente a la solucion
    		
    		std::cout << "PRUEBO: " << *it << std::endl;
    		
    		if (!esClique(solucion)){	//No era clique => lo saco de la solucion y elimino de los candidatos
    			std::cout << "NO CLIQUE" << std::endl;
    			it = candidatos.erase(it);
    			solucion.pop_back();
    			continue;
    		}
    		
			int fronteraActual = frontera(solucion);	//Es clique => calculo frontera
			
			if (fronteraActual < fronteraMaxAnterior){	//La frontera es peor a la que tenia => lo saco de la solucion y elimino de candidatos
				std::cout << "NO MEJORA" << std::endl;
    			it = candidatos.erase(it);
    			solucion.pop_back();
    			continue;
			}

			if (fronteraActual >= fronteraMax) {		//La frontera es mayor o igual a la maxima frontera encontrada hasta ahora
				fronteraMax = fronteraActual;			//En caso de que el mejor candidato tenga igual frontera que la anterior me permite hacer cliques mas grandes y seguir buscando en vez de parar alli
				mejor_candidato = it - candidatos.begin();
				std::cout << "SETEO" << std::endl;
			}
			++it;
			solucion.pop_back();
		}
		if (mejor_candidato != -1){	//Hay un mejor candidato => lo agrego definitivamente a la solucion y lo quito de candidatos
			std::cout << "MEJOR: " << mejor_candidato << " SIZE: " << candidatos.size() << std::endl;
			solucion.push_back(candidatos[mejor_candidato]);
			candidatos.erase(candidatos.begin() + mejor_candidato);
		}
	}


    std::cout << "FIN" << std::endl;
    if (imprimirOutput) {
        // Recordar que a cada nodo hacerle un +1
        std::cout << fronteraMax << " ";
        std::cout << solucion.size() << " ";
        for (int v : solucion) {
            std::cout << v + 1 << " ";
        }
        std::cout << "\n";
    }

    */

    return solucion;
}

// Dice si los nodos forman un grafo completo
// O(n^2)*O(sonVecinos)
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

bool ResolverLocal::sonVecinos(int v1, int v2) {
	return (grafo_ady[v1][v2] == 1);
}
