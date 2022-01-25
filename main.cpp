#include <iostream>

#include "stcp.h"

int main() {
    STCP stcp;
    stcp.readLines();
    stcp.readStops();
    Graph g1(stcp.getStops().size() + 1, true);
    stcp.addEdges(g1);
    g1.printGraph();
    cout << stcp.fewerStops(g1, "5OTR2", "PCUA2");
    return 0;
}
