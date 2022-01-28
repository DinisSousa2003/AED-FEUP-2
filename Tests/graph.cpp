// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <queue>
#include <algorithm>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, string line, int weight) {
    if (src<1 || src>nodes.size() || dest<1 || dest>nodes.size()) return;
    nodes[src].adj.push_back({dest, weight, line});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, line});
}

void Graph::printGraph(){
    for(int v = 1; v < nodes.size(); v++){
        cout << v << " : ";
        for(auto e : nodes[v].adj){
            cout << e.dest << " ";
        }
        cout << endl;
    }
}

void Graph::printLines(){
    for(int v = 1; v <=n; v++){
        cout << v << " : ";
        for(auto e : nodes[v].adj){
            if (e.line == "Walking") {
                cout << "Node " << v << " Edge " << e.line;
                cout << endl;
            }
        }
        cout << endl;
    }
}

vector<int> Graph::bfsdistance(int v, int fv) {
    if(v == fv){return {v};}

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
                nodes[w].pred = u;
                nodes[w].dist = nodes[u].dist + 1;
                if(w == fv){return backtrace(v, fv);}
            }
        }
    }
    return {};
}

vector<int> Graph::backtrace(int start, int end) {
    vector<int> path = {end};
    while (*path.rbegin() != start){
        path.push_back(nodes[*path.rbegin()].pred);
    }
    reverse(path.begin(), path.end());
    return path;
}


void Graph::addTemporatyNodes() {
    nodes.push_back(*(new Node()));
    nodes.push_back(*(new Node()));
}

void Graph::removeTemporaryNodes() {
    nodes.pop_back();
    nodes.pop_back();
}

void Graph::removeWalkingEdges() {
    int i = 0;
    for (auto &n:nodes) {
        auto it = n.adj.begin();
        while (it != n.adj.end()){
            if (it->line == "Walking") it = n.adj.erase(it);
            else it++;
        }
    }
}