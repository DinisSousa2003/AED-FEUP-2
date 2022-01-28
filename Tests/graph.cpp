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

void Graph::resetNodePathingValues() {
    for (int i=1; i<=n; i++) {
        nodes.at(i).dist=INT32_MAX;
        nodes.at(i).visited=false;
        nodes.at(i).pred=-1;
    }
}

vector<int> Graph::backtrace(int start, int end) {
    vector<int> path = {end};
    while (*path.rbegin() != start){
        path.push_back(nodes[*path.rbegin()].pred);
        cout << nodes[*path.rbegin()].predline << " ";
    }
    cout << endl;
    reverse(path.begin(), path.end());
    return path;
}

vector<int> Graph::bfsstops(int v, int fv) {
    if(v == fv){return {v};}

    resetNodePathingValues();

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
                nodes[w].predline = e.line;
                nodes[w].dist = nodes[u].dist + 1;
                if(w == fv){return backtrace(v, fv);}
            }
        }
    }
    return {};
}

vector<int> Graph::dijkstraPath(int sNode, int endNode) {
    resetNodePathingValues();

    MinHeap<int, int> minHeap = MinHeap<int, int>(this->n, -1);

    for(int i = 1; i <= n; i++){
        minHeap.insert(i, nodes[i].dist);
    }

    minHeap.decreaseKey(sNode, nodes[sNode].dist = 0);

    while(minHeap.getSize() > 0) {
        int cNode = minHeap.removeMin();
        nodes.at(cNode).visited=true;

        for (Edge edge: nodes.at(cNode).adj) {
            if (!nodes[edge.dest].visited && nodes.at(cNode).dist + edge.weight < nodes.at(edge.dest).dist) {
                minHeap.decreaseKey(edge.dest, nodes[edge.dest].dist = nodes[cNode].dist + edge.weight);
                nodes[edge.dest].pred = cNode;
                nodes[edge.dest].predline = edge.line;
            }
        }
    }

    return backtrace(sNode, endNode);
}

vector<int> Graph::dijkstraPathLines(int sNode, int endNode) {
    resetNodePathingValues();

    MinHeap<int, int> minHeap = MinHeap<int, int>(this->n, -1);

    for(int i = 1; i <= n; i++){
        minHeap.insert(i, nodes[i].dist);
        nodes[i].predline = "-1";
    }

    minHeap.decreaseKey(sNode, nodes[sNode].dist = 0);

    while(minHeap.getSize() > 0) {
        int cNode = minHeap.removeMin();
        nodes.at(cNode).visited=true;

        for (Edge edge: nodes.at(cNode).adj) {
            int changeLine = (nodes[cNode].predline == edge.line) ? 0 : 1;
            if (!nodes[edge.dest].visited && nodes[cNode].dist + changeLine < nodes[edge.dest].dist) {
                minHeap.decreaseKey(edge.dest, nodes[edge.dest].dist = nodes[cNode].dist + changeLine);
                nodes[edge.dest].pred = cNode;
                nodes[edge.dest].predline = edge.line;
            }
        }
    }
    return backtrace(sNode, endNode);
}