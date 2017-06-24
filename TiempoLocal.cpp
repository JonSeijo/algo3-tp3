#include "ResolverGreedyVariante.h"
#include "ResolverLocal.h"

#include <vector>
#include <stdlib.h>
#include <chrono>
#include <stdexcept>

#define ya std::chrono::high_resolution_clock::now

int main() {
	// Construcción de la solución
    ResolverGreedyVariante problema;
    bool leyoInputCorrectamente = problema.leerInput();
    std::vector<int> solucion;

    if (leyoInputCorrectamente) {
        // Elijo el primer vecino que no sea aislado:
        int inicial = 0;
        for (int i = 0; i < (int)problema.grafo_lst.size(); i++) {
            if ((int)problema.grafo_lst[i].size() > 0) {
                inicial = i;
                break;
            }
        }
        solucion = problema.resolver(inicial);
    } else {
        return 1;
    }
    // Búsqueda Local
    ResolverLocal local;
    local.copiarInput(problema);


    auto start = ya();

    // Tercer true es para minimo output
    local.resolver(false, solucion, true);

    auto end = ya();
    std::cout << "," << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
}
