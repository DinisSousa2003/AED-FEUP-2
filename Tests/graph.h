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
        int dist;
        int pred;
        bool visited;
        string predline;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented


private:
    /*!
     * Set all nodes values to default
     */
    void resetNodePathingValues();
    /*!
     * Starts in the end node and backtraces the lines and stops to the first stop
     *
     * @param start Starting node
     * @param end End node
     * @param lines Vector to fill with the lines
     * @return Vector with the stops the bus goes trough
     */
    vector<int> backtrace(int start, int end, vector<string> &lines);

public:
    /*!
     * Constructor: nr nodes and direction (default: undirected)
     *
     * @param nodes nr nodes
     * @param dir true if the graph is directed, false otherwise
     */
    Graph(int nodes, bool dir = false);
    /*!
     * Add edge from source to destination with a certain weight
     *
     * @param src Start node
     * @param dest End node
     * @param line Line that makes the connection possible
     * @param weight Weight of the connection
     */
    void addEdge(int src, int dest, string line, int weight = 1);
    /*!
     * Add temporary nodes
     */
    void addTemporatyNodes();
    /*!
     * Remove temporary nodes
     */
    void removeTemporaryNodes();
    /*!
     * Remove the edges created for walking purposes, where line == "walking"
     */
    void removeWalkingEdges();
    /*!
     * Prints all the nodes and the respective edges
     */
    void printGraph();
    /*!
     * Find the minimum distance between two nodes by using the Breadth-First Search
     * Big 0 : O(|V| + |E|) (where V is the number of nodes and E the number of edges)
     *
     * @param v Starting node
     * @param fv End node
     * @param lines Vector to store the lines the bus goes trough
     * @return Vector with the stops between the two nodes
     */
    vector<int> bfsstops(int v, int fv, vector<string> &lines);
    /*!
     * Finds the minimum path using the dijkstra algorithm
     * Big 0 : O(|E| log|V|) (where V is the number of nodes and E the number of edges)
     *
     * @param sNode Starting node
     * @param endNode End node
     * @param lines Vector to store the lines the bus goes trough
     * @return Vector with the stops between the two nodes
     */
    vector<int> dijkstraPath(int sNode, int endNode, vector<string> &lines);
    /*!
     * Finds the minimum path using the dijkstra algorithm, taking into account the minimum number of line changes
     * Big 0 : O(|E| log|V|) (where V is the number of nodes and E the number of edges)
     *
     * @param sNode Starting node
     * @param endNode End node
     * @param lines Vector to store the lines the bus goes trough
     * @return Vector with the stops between the two nodes
     */
    vector<int> dijkstraPathLines(int sNode, int endNode, vector<string> &lines);
    /*!
     * Algorithm to find the MST (Minimum Spanning Tree) of a graph, starting in a given node
     * Big 0 : O(|E| log|V|) (where V is the number of nodes and E the number of edges)
     *
     * @param sNode Starting node
     * @return Total distance on the edges
     */
    int prim(int sNode);
    int getSize() {return nodes.size();}
};

#endif
