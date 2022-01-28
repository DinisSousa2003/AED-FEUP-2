//
// Created by User on 23/01/2022.
//

#include "stcp.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

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

map<string, Line> STCP::getLines() {
    return lines;
}

map<string, Zone> STCP::getZones() {
    return zones;
}

map<int, Stop> STCP::getStops() {
    return stops;
}

void STCP::addEdges(Graph &g1, bool night) {
    for(auto it = lines.begin(); it != lines.end(); it++){
        if(it->second.getNight() != night){ continue;}
        Line l = it->second;
        auto line0 = l.getLine0(), line1 = l.getLine1();

        for(auto it0 = line0.begin(); it0 != line0.end(); ){
            string s1 = (*it0++);
            if(it0 == line0.end()) break;
            string s2 = (*it0);
            int idx1 = indexStops.at(s1), idx2 = indexStops.at(s2);
            Stop stop1 = stops.at(idx1), stop2 = stops.at(idx2);
            g1.addEdge(idx1, idx2, l.getCode(), weigth(stop1, stop2));

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
            g1.addEdge(idx1, idx2, l.getCode(), weigth(stop1, stop2));
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
    if(dist == currentWalkingDist) return;
    g1.removeWalkingEdges();
    currentWalkingDist = dist;
    double tempDist;
    Stop tempStop("", "", "", 0.0, 0.0);
    int i = 0;
    for (auto s1: stops) {
        list<string> adj = zones.at(s1.second.getZone()).getAdjacents();
        for (auto zone: adj) {
            for (auto s2: zones.at(zone).getStops()) {
                tempStop = stops.at(indexStops.at(s2));
                tempDist = haversine(s1.second.getLatitude(), s1.second.getLongitude(), tempStop.getLatitude(),
                                     tempStop.getLongitude());
                if (tempDist <= dist) {
                    g1.addEdge(s1.first, indexStops.at(s2), "Walking", tempDist);
                }
            }
        }
    }
}


int STCP::fewerStops(Graph &g1, string s1, string s2) {
    int i1 = indexStops.at(s1), i2 = indexStops.at(s2);
    cout << i1 << " " << i2 << endl;
    vector<string> lines;
    vector<int> intPath = g1.dijkstraPath(i1, i2, lines);
    vector<string> strPath;
    for (int i: intPath) strPath.push_back(stops.at(i).getCode());
    for (auto &l : lines) cout << l << " ";
    cout << endl;
    return path.size() - 1; //distance = number of stops - 1
}

vector<string> STCP::shortestPath(Graph &g1, string s1, string s2) {
    int i1 = indexStops.at(s1), i2 = indexStops.at(s2);
    cout << i1 << " " << i2 << endl;
    vector<string> lines;
    vector<int> intPath = g1.dijkstraPath(i1, i2, lines);
    vector<string> strPath;
    for (int i: intPath) strPath.push_back(stops.at(i).getCode());
    for (auto &l : lines) cout << l << " ";
    cout << endl;
    return strPath;
}
  
bool STCP::readInput(string &stringToStore) const{
    string temp;
    getline(cin,temp);
    if(cin.eof()){
        cout << "Should exit" << endl;  //eof n esta a funcionar
        cin.clear();
        return false;
    } else if (temp == "EXIT" || temp == "exit") {
        return false;
    }
    stringToStore = temp;
    return true;
}

bool STCP::readChar(char &charToStore) const {
    cin >> charToStore;
    cin.clear();
    cin.ignore();
    if(cin.eof()){
        cout << "Should exit" << endl;  //eof n esta a funcionar
        cin.clear();
        return false;
    } else if (tolower(charToStore) == 'q') {
        return false;
    }
    return true;
}

bool STCP::readInt(int &intToStore) const {
    string temp;
    while(getline(cin,temp)) {
        if (cin.eof()) {
            cout << "Should exit" << endl;  //eof n esta a funcionar
            cin.clear();
            return false;
        } else if (temp == "q" || temp == "Q") {
            return false;
        }
        try {
            intToStore = stoi(temp);
            return true;
        } catch (out_of_range & e) {
            cout << "Invalid Input" << endl;
        } catch (invalid_argument & e) {
            cout << "Invalid Input" << endl;
        }
    }
    return true;
}

bool STCP::readDouble(double &doubleToStore) const {
    string temp;
    while(getline(cin,temp)) {
        if (cin.eof()) {
            cout << "Should exit" << endl;  //eof n esta a funcionar
            cin.clear();
            return false;
        } else if (temp == "q" || temp == "Q") {
            return false;
        } else if (temp.find(",") != string::npos) {
            cout << "Invalid Input: separation caracter is '.' not ','" << endl;
            continue;
        }
        try {
            doubleToStore = stod(temp);
            return true;
        } catch (out_of_range & e) {
            cout << "Invalid Input" << endl;
        } catch (invalid_argument & e) {
            cout << "Invalid Input" << endl;
        }
    }
    return true;
}

void STCP::runUserInterface(Graph &g1) {
    cout << "Start" << endl;
    int input;
    bool stayInMenu = true;
    int walkingMetro;
    double walkingDist;
    string start = "Start",destiny = "Destiny";
    char next;
    do {
        cout << "Mensagem welcoming hihihi" << endl;
        cout << "How do you prefer to state the start and destiny of the trip?" << endl;
        cout << "1. Coordinates" << endl;
        cout << "2. Stop code" << endl;
        cout << "3. Stop name" << endl;   //tinha de ser o nome exato... é melhor n?
        cout << "0. Exit" << endl;
        cout << "Type 'q' or 'Q' at any menu to leave" << endl;
        stayInMenu = readInt(input);
        if (!stayInMenu) break;
        do {
            switch (input) {
                case 0:
                    return;
                case 1:
                    stayInMenu = coordenadasMenu(g1);
                    break;
                case 2:
                    stayInMenu = codigoMenu(start, destiny);
                    break;
                default:
                    cout << "Invalid Input";
                    break;
            }
        }while (!stayInMenu);


        cout << "What's the maximum distance you would be willing to walk?(in meters) ";
        if(!readInt(walkingMetro)) continue;
        walkingDist = (double) walkingMetro / 1000.0;
        addWalkingEdges(g1,walkingDist);


        cout << "What's more important? " << endl;
        cout << "1. Less actual distance" << endl;
        cout << "2. Less stops" << endl;
        cout << "3. Less line changes" << endl;
        cout << "4. Less zones" << endl;
        cout << "0. Exit" << endl;
        stayInMenu = readInt(input);
        if (!stayInMenu) break;
        switch (input) {
            case 0:
                stayInMenu = false;
                break;
            case 1:

                break;
            case 2:
                cout << fewerStops(g1, start, destiny);
                break;
            case 3:

                break;
            case 4:

                break;
            default:
                cout << "Invalid Input";
                break;
        }
        if(start == "Start") removeTemporaryStops(g1);
        cout << "Next trip?(y/n) ";
        stayInMenu = readChar(next);
        if(next == 'n') break;

    } while(stayInMenu);
    cout << "End" << endl;
}

bool STCP::coordenadasMenu(Graph &g1) {
    double lat1, lon1, lat2, lon2;
    cout << "Start latitude: ";
    if(!readDouble(lat1)) return false;
    cout << "Start longitude: ";
    if(!readDouble(lon1)) return false;
    cout << "Destiny latitude: ";
    if(!readDouble(lat2)) return false;
    cout << "Destiny longitude: ";
    if(!readDouble(lon2)) return false;
    Stop start = *(new Stop("Start","Start","Start",lat1,lon1));
    Stop destiny = *(new Stop("Destiny","Destiny","Destiny",lat2,lon2));
    addTemporaryStops(g1,start,destiny);
    return true;
}


bool STCP::codigoMenu(string &start, string &destiny) {
    bool notValid;
    do {
        cout << "Start Stop code: ";
        if(!readInput(start)) return false;
        try {
            indexStops.at(start);
            notValid = false;
        } catch (out_of_range & e) {
            cout << "The Stop code is incorrect." << endl;
            notValid = true;
        }
    } while (notValid);

    do {
        cout << "Destiny Stop code: ";
        if(!readInput(destiny)) return false;
        try {
            indexStops.at(destiny);
            notValid = false;
        } catch (out_of_range & e) {
            cout << "The Stop code is incorrect." << endl;
            notValid = true;
        }
        if(start == destiny) {
            cout << "Start and destiny stops cannot be equal." << endl;
            notValid = true;
        }
    } while (notValid);
    return true;
}


void STCP::addTemporaryStops(Graph &g1, Stop &start, Stop &destiny) {
    indexStops.insert(pair<string, int>("Start", stops.size()));
    stops.insert(pair<int, Stop>(stops.size(), start));
    indexStops.insert(pair<string, int>("Destiny", stops.size()));
    stops.insert(pair<int, Stop>(stops.size(),destiny));
    g1.printGraph();
    g1.addTemporatyNodes();
    g1.printGraph();

}

void STCP::removeTemporaryStops(Graph &g1) {
    stops.erase(indexStops.at("Start"));
    stops.erase(indexStops.at("Destiny"));
    indexStops.erase("Start");
    indexStops.erase("Destiny");
    g1.removeTemporaryNodes();
    g1.printGraph();
}



vector<string> STCP::leastStopsPath(Graph &g1, string s1, string s2) {
    int i1 = indexStops.at(s1), i2 = indexStops.at(s2);
    cout << i1 << " " << i2 << endl;
    vector<string> lines;
    vector<int> intPath = g1.bfsstops(i1, i2, lines);
    vector<string> strPath;
    for (int i: intPath) strPath.push_back(stops.at(i).getCode());
    for (auto &l : lines) cout << l << " ";
    cout << endl;
    return strPath;
}

vector<string> STCP::leastLinesChanged(Graph &g1, string s1, string s2) {
    int i1 = indexStops.at(s1), i2 = indexStops.at(s2);
    cout << i1 << " " << i2 << endl;
    vector<string> lines;
    vector<int> intPath = g1.dijkstraPathLines(i1, i2, lines);
    vector<string> strPath;
    for (int i: intPath) strPath.push_back(stops.at(i).getCode());
    for (auto &l : lines) cout << l << " ";
    cout << endl;
    return strPath;
}

