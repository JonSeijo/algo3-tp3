#include "ResolverGrasp.h"
#include <vector>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cerr << "Se necesita la cantidad de repsGrasp y repsLocal como parametro!!\n";
        return -1;
    }

    int repsGrasp = strtol(argv[1], NULL, 10);
    int repsLocal = strtol(argv[1], NULL, 10);

	// Construcción de la solución
    ResolverGrasp problema;

    double alpha = 0.5;

    bool leyoInputCorrectamente = problema.leerInput();
    if (leyoInputCorrectamente) {
        problema.resolver(repsGrasp, repsLocal, alpha, true);
    } else {
    	return 1;
    }
}
