#include "ResolverGreedyConstructiva.h"

int main() {
    ResolverGreedyConstructiva problema;
    bool leyoInputCorrectamente = problema.leerInput();
    if (leyoInputCorrectamente) {
        problema.resolver(true);
    }
}
