//
// Created by FranciscaSilva on 24/01/2022.
//


#include "zone.h"
#include <fstream>
#include <iostream>

Zone::Zone(string c) : code(c) {}

void Zone::addStop(string stop) {
    stops.push_back(stop);
}

string Zone::getCode() {
    return code;
}

vector<string> Zone::getStops() {
    return stops;
}

bool Zone::isAdjacent(string code) {
    for (auto z : adj) if (z == code) return true;
    return false;
}

void Zone::addAdjacent(string code) {
    adj.push_back(code);
}

list<string> Zone::getAdjacents() {
    return adj;
}