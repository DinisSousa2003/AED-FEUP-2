#include <iostream>

#include "stcp.h"

int main() {
    STCP stcp;
    stcp.readLines();
    stcp.readStops();
    Graph g1(stcp.getStops().size() + 1, true);
    stcp.addEdges(g1);
    g1.printGraph();
    cout << stcp.fewerStops(g1, "5OTR2", "PCUA2") << endl;

    //Test for shortest path between 2 stops
    cout << "Shortest Path\n";
    vector<string> strPath = stcp.shortestPath(g1, "5OTR2", "PCUA2");
    for (string str1: strPath) cout << str1 << " ";
    cout << endl;

    //Test for least amount of stops between 2 stops
    cout << "Least Stops Path\n";
    vector<string> strPath2 = stcp.leastStopsPath(g1, "5OTR2", "PCUA2");
    for (string str2: strPath2) cout << str2 << " ";
    cout << endl;

    return 0;
}
