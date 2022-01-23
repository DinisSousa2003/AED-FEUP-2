#include <iostream>

#include "stcp.h"

int main() {
    STCP stcp;
    stcp.readLines();
    stcp.readStops();
    Graph g1(stcp.getStops().size() + 1, true);
    stcp.addEdges(g1);
    return 0;
}
