// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <queue>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, string line, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, line});
}

void Graph::printGraph(){
    for(int v = 1; v <=n; v++){
        cout << v << " : ";
        for(auto e : nodes[v].adj){
            cout << e.dest << " ";
        }
        cout << endl;
    }
}

int Graph::bfsdistance(int v, int fv) {
    if(v == fv){return 0;}

    for (int v=1; v<=n; v++){
        nodes[v].visited = false;
        nodes[v].dist = 0;
    }

    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
                if(w == fv){return nodes[w].dist;}
            }
        }
    }
    return -1;
}

vector<int> Graph::dijkstraPath(int sNode, int endNode) {
    for (int i=0; i<nodes.size(); i++) {
        nodes.at(i).dist=2147483647;
        nodes.at(i).visited=false;
    }
    nodes.at(sNode).dist=0;
    nodes.at(sNode).pred=sNode;
    int visited=0;
    while(visited<nodes.size()) {
        int cNode=0, lowestDist=2147483647;
        for (int i=1; i<nodes.size(); i++) {
            if (!nodes.at(i).visited && nodes.at(i).dist < lowestDist) {
                lowestDist = nodes.at(i).dist;
                cNode = i;
            }
        }
        //if (cNode==0) {} //exception? will fix later
        nodes.at(cNode).visited=true;
        visited++;
        if (cNode==endNode) break;
        for (Edge edge: nodes.at(cNode).adj) {
            if (!nodes.at(edge.dest).visited && nodes.at(cNode).dist+edge.weight<nodes.at(edge.dest).dist) {
                nodes.at(edge.dest).dist = nodes.at(cNode).dist+edge.weight;
                nodes.at(edge.dest).pred = cNode;
            }
        }
    }
    vector<int> path;
    path.push_back(endNode);
    int pNode=endNode;
    while (pNode!=sNode) {
        pNode=nodes.at(pNode).pred;
        path.insert(path.begin(), pNode);
    }
    return path;
}
