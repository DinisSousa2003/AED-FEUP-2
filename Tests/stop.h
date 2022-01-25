//
// Created by User on 23/01/2022.
//

#ifndef PROJ_2_STOP_H
#define PROJ_2_STOP_H

#include <string>
using namespace std;

class Stop {
private:
    double latitude, longitude;
    string zone, name, code;

public:
    Stop(string c, string n, string z, double lat, double lon);
    double getLatitude() const;
    double getLongitude() const;
    string getZone() const;
    string getName() const;
};


#endif //PROJ_2_STOP_H
