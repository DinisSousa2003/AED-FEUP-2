// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        string line; //
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int zone;
        int dist;
        int zoneDist;
        int pred;
        bool visited;
        string name;
    };

    struct Zone {
        int n;
        bool visited;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    vector<Zone> zones;


private:
    void resetNodePathingValues();
    vector<int> backtrace(int start, int end);

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add zone identifying int to specified node
    void addZone(int zoneNum);
    void addZoneToNode(int nodeNum, int zoneNum);
    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, string line, int weight = 1);
    vector<int> bfsdistance(int v, int fv);
    vector<int> dijkstraPath(int sNode, int endNode);
    vector<int> zoneReducingDijkstraPath(int sNode, int endNode);
    void printGraph();
};

#endif
