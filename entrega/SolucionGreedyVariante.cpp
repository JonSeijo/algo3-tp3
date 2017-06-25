#include "ResolverGreedyVariante.h"

int main() {
    ResolverGreedyVariante problema;
    bool leyoInputCorrectamente = problema.leerInput();
    if (leyoInputCorrectamente) {

        // Elijo el primer vecino que no sea aislado:
        int inicial = 0;
        for (int i = 0; i < (int)problema.grafo_lst.size(); i++) {
            if ((int)problema.grafo_lst[i].size() > 0) {
                inicial = i;
                break;
            }
        }

        problema.resolver(inicial, true);
    }
}
