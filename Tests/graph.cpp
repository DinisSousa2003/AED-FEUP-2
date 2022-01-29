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

void Graph::addZoneToNode(int nodeNum, string zoneName) {
    nodes.at(nodeNum).zone = zoneName;
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

void Graph::resetNodePathingValues() {
    for (int i=1; i<=n; i++) {
        nodes.at(i).dist=INT32_MAX;
        nodes.at(i).visited=false;
        nodes.at(i).pred=-1;
        nodes.at(i).predline = "-1";
    }
}


vector<int> Graph::backtrace(int start, int end, vector<string> &lines) {
    if(nodes[end].pred == -1){return {};}
    vector<int> path = {end};
    while (*path.rbegin() != start){
        lines.push_back(nodes[*path.rbegin()].predline);
        path.push_back(nodes[*path.rbegin()].pred);
    }
    reverse(path.begin(), path.end());
    reverse(lines.begin(), lines.end());
    return path;
}

vector<int> Graph::bfsstops(int v, int fv, vector<string> &lines) {
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
                if(w == fv){return backtrace(v, fv, lines);}
            }
        }
    }
    return {};
}

vector<int> Graph::dijkstraPath(int sNode, int endNode, vector<string> &lines) {
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

    return backtrace(sNode, endNode, lines);
}

vector<int> Graph::dijkstraPathLines(int sNode, int endNode, vector<string> &lines) {
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
            int changeLine = (nodes[cNode].predline == edge.line) ? 0 : 1;
            if (!nodes[edge.dest].visited && nodes[cNode].dist + changeLine < nodes[edge.dest].dist) {
                minHeap.decreaseKey(edge.dest, nodes[edge.dest].dist = nodes[cNode].dist + changeLine);
                nodes[edge.dest].pred = cNode;
                nodes[edge.dest].predline = edge.line;
            }
        }
    }
    return backtrace(sNode, endNode, lines);
}

vector<int> Graph::dijkstraPathZones(int sNode, int endNode, vector<string> &lines) {
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
            int changeZone = (nodes[cNode].zone == nodes[edge.dest].zone) ? 0 : 1;
            if (!nodes[edge.dest].visited && nodes[cNode].dist + changeZone < nodes[edge.dest].dist) {
                minHeap.decreaseKey(edge.dest, nodes[edge.dest].dist = nodes[cNode].dist + changeZone);
                nodes[edge.dest].pred = cNode;
            }
        }
    }
    return backtrace(sNode, endNode, lines);
}

int Graph::prim(int r) {
    MinHeap<int, int> heap(nodes.size(), -1);

    resetNodePathingValues();

    for(int i = 1; i < nodes.size(); i++){
        heap.insert(i, nodes[i].dist);
    }

    heap.decreaseKey(r, nodes[r].dist = 0);


    while(heap.getSize() != 0){
        int u = heap.removeMin();
        nodes[u].visited = true;
        for(auto &v : nodes[u].adj){
            if(heap.hasKey(v.dest) && (v.weight < nodes[v.dest].dist)){
                heap.decreaseKey(v.dest, nodes[v.dest].dist = v.weight);
            }
        }
    }

    int sumDist = 0;

    for(int i = 1; i < nodes.size(); i++){
        if(nodes[i].visited)
            sumDist += nodes[i].dist;
    }

    return sumDist;
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
