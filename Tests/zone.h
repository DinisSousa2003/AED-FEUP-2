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
    Zone(string c);
    void addStop(string stop);
    string getCode();
    vector<string> getStops();
    bool isAdjacent(string code);
    void addAdjacent(string code);
    list<string> getAdjacents();
};



#endif //PROJ_2_ZONE_H
