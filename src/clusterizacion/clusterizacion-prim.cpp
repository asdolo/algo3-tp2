#include<iostream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

class Edge {
public:
    int firstNode;
    int secondNode;
    int weight;

    Edge(int secondNode_, int firstNode_, int weight_) {
        secondNode = secondNode_;
        firstNode = firstNode_;
        weight = weight_;
    }
    ~Edge() {
    }

    bool operator <(const Edge& other) const {
        return weight < other.weight;
    }

};


class compareEdges {
public:
    bool operator()(const Edge& l, const Edge& r) {
        return l.weight < r.weight;
    }
};


class Node {
public:
    ~Node() {}
    Node() {};
    vector<Edge> edges;

};



bool partiallyInANodeOf(Edge e, set<int> added_nodes) {
    if (added_nodes.find(e.firstNode) != added_nodes.end() && added_nodes.find(e.secondNode) != added_nodes.end()) {
        return false;
    }
    if (added_nodes.find(e.firstNode) != added_nodes.end() || added_nodes.find(e.secondNode) != added_nodes.end()) {
        return true;
    }
    return false; //Wextra
}


int selectNewNodeIndex(Edge e, set<int> added_nodes) {
    if (added_nodes.find(e.firstNode) == added_nodes.end()) {
        return e.firstNode;
    } else {
        return e.secondNode;
    }
}



set<Edge> prim(vector<Node> graph) {
    set<int> added_nodes;
    set<Edge> added_edges;
    Edge min_edge = graph[0].edges[0];
    for (Node n : graph) {
        for (Edge e : n.edges) {
            if (e.weight < min_edge.weight)
                min_edge = e;
        }
    }
    added_nodes.insert(min_edge.secondNode);
    added_nodes.insert(min_edge.firstNode);

    priority_queue<Edge, vector<Edge>, compareEdges> posible_edges;
    posible_edges.push(min_edge);
    while (added_nodes.size() < graph.size()) {
        cout << "ITER " << endl;
        for (int e : added_nodes)
            cout  << e <<  endl;


        //obtengo arista de menor peso
        //Asumo que ya tengo las aristas de los dos nodos agregadas.
        min_edge = posible_edges.top();
        posible_edges.pop();
        //agrego la nueva arista
        added_edges.insert(min_edge);
        added_nodes.insert(min_edge.secondNode);
        int new_node_index = selectNewNodeIndex(min_edge, added_nodes);
        for (Edge e : graph[new_node_index].edges) {
            if (partiallyInANodeOf(e, added_nodes)) posible_edges.push(e);
        }
    }
    return added_edges;
}


using namespace std;


int main() {
    vector<Node> v;
    for (int i = 0; i < 5; i++) {
        v.push_back(Node());
    }

    v[0].edges.push_back(Edge(0, 1, 5));
    v[1].edges.push_back(Edge(1, 0, 5));
    v[0].edges.push_back(Edge(0, 4, 1));
    v[4].edges.push_back(Edge(4, 0, 1));
    v[1].edges.push_back(Edge(1, 2, 6));
    v[2].edges.push_back(Edge(2, 1, 6));
    v[1].edges.push_back(Edge(1, 3, 16));
    v[3].edges.push_back(Edge(3, 1, 16));
    v[2].edges.push_back(Edge(2, 3, 28));
    v[3].edges.push_back(Edge(3, 2, 28));
    v[2].edges.push_back(Edge(2, 4, 3));
    v[4].edges.push_back(Edge(4, 2, 3));

    set<Edge> res = prim(v);
    cout << "RES " << endl;
    for (Edge e : res)
        cout  << e.weight <<  endl;
}