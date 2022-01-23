//
// Created by User on 23/01/2022.
//

#include "line.h"
#include <fstream>
#include <iostream>

Line::Line(string c, string n) : code(c), name(n)
{
    if(code[-1] == 'M'){
        night = true;
    }
    night = false;
}

void Line::addStops(char direction) {
    ifstream file;

    file.open("..//Tests//dataset//line_" + code + "_" + direction + ".csv");

    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
    }

    string stopCode;

    //remove header
    getline(file, stopCode);

    if (direction == '0') {
        auto it = line_stops0.before_begin();
        while (getline(file, stopCode)) {
            it = line_stops0.insert_after(it, stopCode);
        }
    }
    else if (direction == '1') {
        auto it = line_stops1.before_begin();
        while (getline(file, stopCode)) {
            it = line_stops1.insert_after(it, stopCode);
        }
    }

    file.close();
}

bool Line::getNight(){
    return night;
}

string Line::getName() {
    return name;
}

string Line::getCode() {
    return code;
}

forward_list<string> Line::getLine0() {
    return line_stops0;
}

forward_list<string> Line::getLine1() {
    return line_stops1;
}



