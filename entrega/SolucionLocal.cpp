#include "ResolverGreedyVariante.h"
#include "ResolverLocal.h"
#include <vector>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Se necesita la cantidad de iteraciones como parametro!\n";
        return -1;
    }

    int iteracionesLocal = strtol(argv[1], NULL, 10);

	// Construcción de la solución
    ResolverGreedyVariante problema;
    bool leyoInputCorrectamente = problema.leerInput();
    std::vector<int> solucion;
    if (leyoInputCorrectamente) {
        solucion = problema.resolver(true);
    } else {
    	return 1;
    }
    // Búsqueda Local
    ResolverLocal local;
    local.copiarInput(problema);
    local.resolver(iteracionesLocal, true, solucion);
}
