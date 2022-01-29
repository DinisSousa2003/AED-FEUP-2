#include <iostream>

#include "stcp.h"

int main() {
    STCP stcp;
    stcp.readStops();
    stcp.readLines();
    Graph g1(stcp.getStops().size(), true);
    Graph g2(stcp.getStops().size(), true);
    stcp.addEdges(g1, false);
    stcp.addEdges(g2, true);
    cout << g1.prim(25);
    cout << g1.prim(25);
  /* testing walking
    stcp.addWalkingEdges(g1,0.3);
    for (auto s:stcp.getStops()) cout << "stop" << endl;
    for (auto l:stcp.getLines()) cout << "line" << endl;
    for (auto z:stcp.getZones()) {
        cout << "zone " << z.second.getCode() << endl;
        for (auto a:z.second.getAdjacents()) cout << "Adjacent" << a << endl;
    }*/
/*
    //g1.printGraph();
    //g2.printGraph();

    //Test for shortest path between 2 stops
    stcp.addWalkingEdges(g1,0.2);
    stcp.addWalkingEdges(g2,0.2);
    cout << "\nShortest Path\n";
    vector<string> strPath = stcp.shortestPath(g1, "5OTR2", "PCUA2");
    cout << endl;
    strPath = stcp.shortestPath(g1, "CQ8", "MLAM");
    cout << endl;
    strPath = stcp.shortestPath(g2, "CQ8", "SRLZ1");
    cout << endl;
    strPath = stcp.shortestPath(g2, "CQ8", "MLAM");
    cout << endl;

    //Test for least amount of stops between 2 stops
    cout << "Least Stops Path\n";
    strPath = stcp.leastStopsPath(g1, "5OTR2", "PCUA2");
    cout << endl;
    strPath = stcp.leastStopsPath(g1, "CQ8", "MLAM");
    cout << endl;
    strPath = stcp.leastStopsPath(g2, "CQ8", "MLAM");
    cout << endl;

    //Test for fewer linechanges between 2 stops
    cout << "Least lines changed Path\n";
    strPath = stcp.leastLinesChanged(g1, "5OTR2", "PCUA2");
    cout << endl;
    strPath = stcp.leastLinesChanged(g1, "CQ8", "MLAM");
    cout << endl;
    strPath = stcp.leastLinesChanged(g2, "CQ8", "MLAM");
    cout << endl;
    */

    stcp.runUserInterface(g1,g2);
  
    return 0;
}
