#include "ResolverGrasp.h"

#include <stdlib.h>
#include <chrono>
#include <stdexcept>

#define ya std::chrono::high_resolution_clock::now

int main() {
    ResolverGrasp problema;
    bool leyoInputCorrectamente = problema.leerInput();

    auto start = ya();
    if (leyoInputCorrectamente) {
        problema.resolver(false);
    } else {
        std::cerr << "NO SE LEYO INPUT CORRECTAMENTE";
        return 1;
    }
    auto end = ya();
    std::cout << "," << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
}
