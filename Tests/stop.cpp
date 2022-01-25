//
// Created by User on 23/01/2022.
//

#include "stop.h"

Stop::Stop(string c, string n, string z, double lat, double lon) : code(c), name(n), zone(z), latitude(lat), longitude(lon)
{}

double Stop::getLatitude() const {
    return latitude;
}

double Stop::getLongitude() const {
    return longitude;
}

string Stop::getCode() const{
    return code;
}