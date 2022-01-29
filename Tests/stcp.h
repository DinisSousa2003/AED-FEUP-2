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
    /*!
     * Used to determine the distance between two locations based on their coordinates
     * @param lat1 Latitude of first location
     * @param lon1 Longitude of first location
     * @param lat2 Latitude of second location
     * @param lon2 Longitude of second location
     * @return distance in kilometers
     */
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    /*!
     *  Determines the weight between too stops based on their distance
     * @param s1 First stop
     * @param s2 Second stop
     * @return Weight between the two stops
     */
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
    /*!
     * Used to store a double, given by input, in a certain variable
     *
     * @param doubleToStore Variable where the input will be stored
     * @return True if the input was successful, false otherwise
     */
    bool readDouble(double &doubleToStore) const;
    /*!
     * Runs the menu that allows the start and destiny locations to be given by coordinates
     * @param g1 Graph on which the program will operate
     * @return True if program should continue, false otherwise
     */
    bool coordenadasMenu(Graph &g1);
    /*!
     * Runs the menu that allows the start and destiny locations to be given by stop codes
     * @param start Variable that will store the code of the starting stop
     * @param destiny Variable that will store the code of the destiny stop
     * @return True if program should continue, false otherwise
     */
    bool codigoMenu(string &start, string &destiny);

public:
    /*!
     * Reads from the given files and stores the information about stops
     */
    void readStops();
    /*!
     * Reads from the given files and stores the information about lines
     */
    void readLines();
    /*!
     * @return Map of all Stops
     */
    map<int, Stop> getStops();
    /*!
     * @return Map of all Lines
     */
    map<string, Line> getLines();
    /*!
     * @return Map of all Zones
     */
    map<string, Zone> getZones();
    /*!
     * Adds two temporary stops to the database and to the proper graph.
     * These stops where calculated using the given coordinates in the coordinatesMenu.
     * @param g1 Graph where the stops will be added
     * @param start Stop where the path should start
     * @param destiny Stop where the path should end
     */
    void addTemporaryStops(Graph &g1, Stop &start, Stop &destiny);
    /*!
     * Removes temporary stops added in addTemporaryStops function
     * @param g1 Graph from where the stops will be removed
     */
    void removeTemporaryStops(Graph &g1);
    /*!
     * Adds edges to the graph based on lines' information
     * @param g1 Graph on which the edges will be added
     * @param night If True only adds the night lines, if False only adds the day lines
     */
    void addEdges(Graph &g1, bool night);
    /*!
     * Adds the correct zone to all the nodes in the given graph
     * @param g1 Graph on which the zones will be added
     */
    void addZones(Graph &g1);
    /*!
     * Adds edges between every two nodes which distance is lower than the given distance
     * @param g1 Graph on which the edges will be added
     * @param dist Maximum walking distance possible
     */
    void addWalkingEdges(Graph &g1, double dist);
    /*!
     * Calculates the shortest path in actual distance between two stops
     * @param g1 Graph on which the function will operate
     * @param s1 Code of the starting stop
     * @param s2 Code of the ending stop
     * @return Vector of stops passed in correct order
     */
    vector<string> shortestPath(Graph &g1, string s1, string s2);
    /*!
     * Calculates the path between two stops that passes least stops
     * @param g1 Graph on which the function will operate
     * @param s1 Code of the starting stop
     * @param s2 Code of the ending stop
     * @return Vector of stops passed in correct order
     */
    vector<string> leastStopsPath(Graph &g1, string s1, string s2);
    /*!
     * Calculates the path between two stops that changes lines fewer times
     * @param g1 Graph on which the function will operate
     * @param s1 Code of the starting stop
     * @param s2 Code of the ending stop
     * @return Vector of stops passed in correct order
     */
    vector<string> leastLinesChanged(Graph &g1, string s1, string s2);
    /*!
     * Calculates the path between two stops that changes zones fewer times
     * @param g1 Graph on which the function will operate
     * @param s1 Code of the starting stop
     * @param s2 Code of the ending stop
     * @return Vector of stops passed in correct order
     */
    vector<string> leastZonesTraversed(Graph &g1, string s1, string s2);
    /*!
     * Prints the given path stating which stops should be passed in each line
     * @param stops Vector containing all the stops passed by order
     * @param lines Vector containing which line is used in each step
     */
    void printPath(vector<string> &stops,vector<string> &lines);
    /*!
     * Starts the interface
     * @param g1 graph representing the day lines
     * @param g2 graph representing the night lines
     */
    void runUserInterface(Graph &g1, Graph &g2);

};


#endif //PROJ_2_STCP_H
