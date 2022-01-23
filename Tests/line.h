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
    Line(string c, string n);
    void addStops(char direction);
    bool getNight();
    string getCode();
    string getName();
    forward_list<string> getLine0();
    forward_list<string> getLine1();
};


#endif //PROJ_2_LINE_H
