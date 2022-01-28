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
    map<string, Zone> zones;
    map<string , int> indexStops;
    double currentWalkingDist = 0.0;
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    double weigth(Stop &s1, Stop &s2);
    /*!
     * Used to store a string, given by input, in a certain variable
     *
     * @param stringToStore Variable where the input will be stored
     * @return True if the input was successful, false otherwise
     */
    bool readInput(string &stringToStore) const;
    /*!
     * Used to store a char, given by input, in a certain variable
     *
     * @param charToStore Variable where the input will be stored
     * @return True if the input was successful, false otherwise
     */
    bool readChar(char &charToStore) const;
    /*!
     * Used to store an int, given by input, in a certain variable
     *
     * @param intToStore Variable where the input will be stored
     * @return True if the input was successful, false otherwise
     */
    bool readInt(int &intToStore) const;
    bool readDouble(double &doubleToStore) const;
    bool coordenadasMenu(Graph &g1);
    bool codigoMenu(string &start, string &destiny);

public:
    void readStops();
    void readLines();
    map<int, Stop> getStops();
    map<string, Line> getLines();
    map<string, Zone> getZones();
    void addTemporaryStops(Graph &g1, Stop &start, Stop &destiny);
    void removeTemporaryStops(Graph &g1);
    void addEdges(Graph &g1);
    void addEdges(Graph &g1, bool night);
    void addWalkingEdges(Graph &g1, double dist);
    vector<string> shortestPath(Graph &g1, string s1, string s2);
    vector<string> leastStopsPath(Graph &g1, string s1, string s2);
    vector<string> leastLinesChanged(Graph &g1, string s1, string s2);
    /*!
     * Starts the interface
     */
    void runUserInterface(Graph &g1);

};


#endif //PROJ_2_STCP_H
