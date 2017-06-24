#include "ResolverGrasp.h"
#include <vector>

int main() {
	// Construcción de la solución
    ResolverGrasp problema;

    double alpha = 0.5;

    bool leyoInputCorrectamente = problema.leerInput();
    if (leyoInputCorrectamente) {
        problema.resolver(alpha, true);
    } else {
    	return 1;
    }
}
