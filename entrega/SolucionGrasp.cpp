#include "ResolverGrasp.h"
#include <vector>

int main(int argc, char *argv[]) {

    if (argc != 4) {
        std::cerr << "Se necesita alpha, repsGrasp y repsLocal como parametro!!\n";
        return -1;
    }

    double alpha = atof(argv[1]);
    int repsGrasp = strtol(argv[2], NULL, 10);
    int repsLocal = strtol(argv[3], NULL, 10);

    // Construcción de la solución
    ResolverGrasp problema;

    bool leyoInputCorrectamente = problema.leerInput();
    if (leyoInputCorrectamente) {
        problema.resolver(repsGrasp, repsLocal, alpha, true);
    } else {
    	return 1;
    }
}
