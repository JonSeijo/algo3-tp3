#include "ResolverGreedyConstructiva.h"
#include "ResolverLocal.h"
#include <vector>

int main() {
	// Construcción de la solución
    ResolverGreedyConstructiva problema;
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
    local.resolver(true, solucion);
}
