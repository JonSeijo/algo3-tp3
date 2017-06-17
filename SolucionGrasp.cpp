#include "ResolverGrasp.h"
#include <vector>

int main() {
	// Construcción de la solución
    ResolverGrasp problema;
    bool leyoInputCorrectamente = problema.leerInput();
    if (leyoInputCorrectamente) {
        problema.resolver(true);
    } else {
    	return 1;
    }
}
