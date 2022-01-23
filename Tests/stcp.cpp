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

        stopNum++;
    }
}

map<string, Line> STCP::getLines() {
    return lines;
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
            g1.addEdge(idx1, idx2, weigth(stop1, stop2));
        }

        for(auto it1 = line0.begin(); it1 != line0.end(); ){
            string s1 = (*it1++);
            if(it1 == line0.end()) break;
            string s2 = (*it1);
            int idx1 = indexStops.at(s1), idx2 = indexStops.at(s2);
            Stop stop1 = stops.at(idx1), stop2 = stops.at(idx2);
            g1.addEdge(idx1, idx2, weigth(stop1, stop2));
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