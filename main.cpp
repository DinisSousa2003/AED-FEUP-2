#include <iostream>

#include "stcp.h"

int main() {
    STCP stcp;
    stcp.readStops();
    stcp.readLines();
    Graph g1(stcp.getStops().size() + 1, true);
    stcp.addEdges(g1);
    for (auto s:stcp.getStops()) cout << "stop" << endl;
    for (auto l:stcp.getLines()) cout << "line" << endl;
    for (auto z:stcp.getZones()) {
        cout << "zone " << z.second.getCode() << endl;
        for (auto a:z.second.getAdjacents()) cout << "Adjacent" << a << endl;
    }
    return 0;
}
