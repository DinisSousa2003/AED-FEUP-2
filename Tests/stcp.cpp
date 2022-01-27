//
// Created by User on 23/01/2022.
//

#include "stcp.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

void STCP::readLines() {
    ifstream file;

    file.open("..//Tests//dataset//lines.csv");

    if(!file.is_open()){
        cerr << "Unable to open file" << endl;
    }

    string line, code, name;
    //remove header
    getline(file, line);

    while(getline(file, line)){
        stringstream lineSS(line);
        getline(lineSS, code, ',');
        getline(lineSS, name);

        Line stcpLine(code, name);

        stcpLine.addStops('0');
        stcpLine.addStops('1');

        lines.insert(pair<string, Line>(code, stcpLine));
    }
    file.close();
}

void STCP::readStops() {
    ifstream file;

    file.open("..//Tests//dataset//stops.csv");

    if(!file.is_open()){
        cerr << "Unable to open file" << endl;
    }

    string line, code, name, zone, lon, lat;
    //remove header
    getline(file, line);

    int stopNum = 1;
    while(getline(file, line)){
        stringstream lineSS(line);
        getline(lineSS, code, ',');
        getline(lineSS, name, ',');
        getline(lineSS, zone, ',');
        getline(lineSS, lat, ',');
        getline(lineSS, lon);

        Stop stop(code, name, zone, stof(lat), stof(lon));

        stops.insert(pair<int, Stop>(stopNum, stop));
        indexStops.insert(pair<string, int>(code, stopNum));

        auto z = zones.find(zone);
        if(z == zones.end()) {
            Zone zone1 = *(new Zone(zone));
            zone1.addStop(stop.getCode());
            zones.insert({zone,zone1});
        }
        else {
            z->second.addStop(stop.getCode());
        }

        stopNum++;
    }
}

map<string, Line> STCP::getLines() {
    return lines;
}

map<string, Zone> STCP::getZones() {
    return zones;
}

map<int, Stop> STCP::getStops() {
    return stops;
}

void STCP::addEdges(Graph &g1) {
    for(auto it = lines.begin(); it != lines.end(); it++){
        Line l = it->second;
        auto line0 = l.getLine0(), line1 = l.getLine1();

        for(auto it0 = line0.begin(); it0 != line0.end(); ){
            string s1 = (*it0++);
            if(it0 == line0.end()) break;
            string s2 = (*it0);
            int idx1 = indexStops.at(s1), idx2 = indexStops.at(s2);
            Stop stop1 = stops.at(idx1), stop2 = stops.at(idx2);
            g1.addEdge(idx1, idx2, l.getName(), weigth(stop1, stop2));

            if(stop1.getZone() != stop2.getZone() && !zones.at(stop1.getZone()).isAdjacent(stop2.getZone())){
                zones.at(stop1.getZone()).addAdjacent(stop2.getZone());
                zones.at(stop2.getZone()).addAdjacent(stop1.getZone());
            }


        }

        for(auto it1 = line1.begin(); it1 != line1.end(); ){
            string s1 = (*it1++);
            if(it1 == line1.end()) break;
            string s2 = (*it1);
            int idx1 = indexStops.at(s1), idx2 = indexStops.at(s2);
            Stop stop1 = stops.at(idx1), stop2 = stops.at(idx2);
            g1.addEdge(idx1, idx2, l.getName(), weigth(stop1, stop2));
        }
    }
}

double STCP::haversine(double lat1, double lon1, double lat2, double lon2){
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

double STCP::weigth(Stop &s1, Stop &s2) {
    return haversine(s1.getLatitude(), s1.getLongitude(), s2.getLatitude(), s2.getLongitude());
}


void STCP::addWalkingEdges(Graph &g1, double dist) {
    double tempDist;
    Stop tempStop("","","",0.0,0.0);
    int i = 0;
    for (auto s1: stops){
        list<string> adj = zones.at(s1.second.getZone()).getAdjacents();
        for (auto zone:adj){
            for(auto s2 : zones.at(zone).getStops()){
                tempStop = stops.at(indexStops.at(s2));
                tempDist = haversine(s1.second.getLatitude(),s1.second.getLongitude(),tempStop.getLatitude(),tempStop.getLongitude());
                if (tempDist <= dist){
                    g1.addEdge(s1.first,indexStops.at(s2),"walking",tempDist);
                    cout << i++ << " Added edge : " << tempDist << endl;
                }
            }
        }
    }

int STCP::fewerStops(Graph &g1, string s1, string s2) {
    int i1 = indexStops.at(s1), i2 = indexStops.at(s2);
    cout << i1 << " " << i2 << endl;
    return g1.bfsdistance(i1, i2);

}