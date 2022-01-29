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
    /*!
     * Stop constructor
     *
     * @param c code
     * @param n name
     * @param z zone
     * @param lat latitude
     * @param lon longitude
     */
    Stop(string c, string n, string z, double lat, double lon);
    /*!
     *
     * @return latitude
     */
    double getLatitude() const;
    /*!
     *
     * @return longitude
     */
    double getLongitude() const;
    /*!
     *
     * @return zone
     */
    string getZone() const;
    /*!
     *
     * @return name
     */
    string getName() const;
    /*!
     *
     * @return code
     */
    string getCode() const;
};


#endif //PROJ_2_STOP_H
