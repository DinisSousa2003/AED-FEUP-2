//
// Created by User on 23/01/2022.
//

#ifndef PROJ_2_LINE_H
#define PROJ_2_LINE_H

#include <string>
#include <forward_list>
#include "stop.h"

using namespace std;

class Line {
private:
    string code, name;
    forward_list<string> line_stops0, line_stops1;
    bool night;
public:
    /*!
     * Line constructor
     *
     * @param c Code
     * @param n Name
     */
    Line(string c, string n);
    /*!
     * Adds all the stops of a line in a given direction, by reading from the respective file
     *
     * @param direction ('0' - for normal or '1' - for reverse)
     */
    void addStops(char direction);
    /*!
     *
     * @return night (true if it is a 'M' line)
     */
    bool getNight();
    /*!
     *
     * @return code
     */
    string getCode();
    /*!
     *
     * @return name
     */
    string getName();
    /*!
     *
     * @return list with the stops of the line in the normal order
     */
    forward_list<string> getLine0();
    /*!
     *
     * @return list with the stops of the line in the reverse order
     */
    forward_list<string> getLine1();
};


#endif //PROJ_2_LINE_H
