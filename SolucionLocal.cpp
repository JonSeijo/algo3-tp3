#include "ResolverLocal.h"
#include "ResolverGreedyConstructiva.h"

int main() {
	// Construcción de la solución
    ResolverGreedyConstructiva problema;
    bool leyoInputCorrectamente = problema.leerInput();
    if (leyoInputCorrectamente) {
        problema.resolver(true, false);
    }
    // Búsqueda Local
    ResolverLocal local;
    local.copiarInput(problema);
}
