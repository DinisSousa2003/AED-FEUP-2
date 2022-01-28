//
// Created by User on 23/01/2022.
//

#ifndef PROJ_2_STCP_H
#define PROJ_2_STCP_H

#include "stop.h"
#include "line.h"
#include "graph.h"
#include "zone.h"
#include <map>

using namespace std;

class STCP {
private:
    map<int, Stop> stops;
    map<string, Line> lines;
    map<int, Zone> zones;
    map<string, int> indexStops;
    map<string, int> indexZones;
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    double weigth(Stop &s1, Stop &s2);

public:
    void readStops();
    void readLines();
    map<int, Stop> getStops();
    map<string, Line> getLines();
    map<int, Zone> getZones();
    void addZonesToGraph(Graph &g1);
    void addEdges(Graph &g1);
    void addWalkingEdges(Graph &g1, double dist);
    vector<string> shortestPath(Graph &g1, string s1, string s2);
    vector<string> leastStopsPath(Graph &g1, string s1, string s2);
};


#endif //PROJ_2_STCP_H
