#include "ResolverExacta.h"

int main() {
    ResolverExacta problema;
    bool leyoInputCorrectamente = problema.leerInput();
    if (leyoInputCorrectamente) {
        problema.resolver(true);
    }
}
