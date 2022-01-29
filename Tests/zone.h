//
// Created by FranciscaSilva on 24/01/2022.
//

#ifndef PROJ_2_ZONE_H
#define PROJ_2_ZONE_H

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include "stop.h"

using namespace std;

class Zone {
private:
    string code;
    list<string> adj;
    vector<string> stops;   //if string of code change addStop in stcp.readStops
public:
    /*!
     * Zone constructor
     *
     * @param c code
     */
    Zone(string c);
    /*!
     * Add stop code to the vector of stops
     *
     * @param stop
     */
    void addStop(string stop);
    /*!
     *
     * @return code
     */
    string getCode();
    /*!
     *
     * @return stops that belong to the zone
     */
    vector<string> getStops();
    /*!
     *
     * @param code Code of another zone
     * @return true if the zone on the input is adjecent to the zone, false otherwise
     */
    bool isAdjacent(string code);
    /*!
     * Adds to the list of adjecent zones the string with the zone code
     *
     * @param code Code of another zone
     */
    void addAdjacent(string code);
    /*!
     *
     * @return list with adjecent zones
     */
    list<string> getAdjacents();
};



#endif //PROJ_2_ZONE_H
