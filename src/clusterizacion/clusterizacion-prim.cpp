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

    Edge(int firstNode_, int secondNode_, int weight_) {
        secondNode = secondNode_;
        firstNode = firstNode_;
        weight = weight_;
    }
    ~Edge() {
    }

    bool operator <(const Edge& other) const {
        return weight < other.weight;
    }

    bool operator >(const Edge& other) const {
        return weight > other.weight;
    }

};

class edgesGreaterThan {
public:
    bool operator()(const Edge& l, const Edge& r) {
        return l.weight > r.weight;
    }
};


class Node {
public:
    ~Node() {}
    Node() {}
    Node(int id_) {id = id_;}

    int id;
    vector<Edge> edges;
};

bool edgeInBorder(Edge e, set<int> tree_nodes) {
    if (tree_nodes.find(e.firstNode) != tree_nodes.end() && tree_nodes.find(e.secondNode) != tree_nodes.end()) {
        return false;
    }
    if (tree_nodes.find(e.firstNode) != tree_nodes.end() || tree_nodes.find(e.secondNode) != tree_nodes.end()) {
        return true;
    }
    return false; //Wextra
}

int selectNewNodeIndex(Edge e, set<int> tree_nodes) {
    if (tree_nodes.find(e.firstNode) == tree_nodes.end()) {
        return e.firstNode;
    } else {
        return e.secondNode;
    }
}


void printQueue(priority_queue<Edge, std::vector<Edge>, edgesGreaterThan> edges) {


    while (!edges.empty()) {
        Edge e = edges.top();
        cout << " from: " << e.firstNode << " to:  " << e.secondNode << " weight: " << e.weight << endl;
        edges.pop();
    }
}

Edge selectMinEdge(vector<Node> graph) {
    Edge min_edge = graph[0].edges[0];
    for (Node n : graph) {
        for (Edge e : n.edges) {
            if (e.weight < min_edge.weight)
                min_edge = e;
        }
    }
    return min_edge;
}


set<Edge> prim(vector<Node> graph) {
    set<int> tree_nodes;
    set<Edge> tree_edges;

    //Busco la minima arista y uno de sus nodos.
    Edge min_edge = selectMinEdge(graph);
    Node root_node = graph[min_edge.firstNode];
    //Agrego la raiz junto con sus aristas.
    tree_nodes.insert(root_node.id);
    priority_queue<Edge, vector<Edge>, edgesGreaterThan> border_edges;
    for (Edge e : root_node.edges)
        border_edges.push(e);

    while (tree_nodes.size() < graph.size()) {
        cout << "ITER " << endl;
        //for (int e : tree_nodes)
        //    cout  << e <<  endl;
        printQueue(border_edges);
        //obtengo arista de menor peso
        //Asumo que ya tengo las aristas de los dos nodos agregadas.
        min_edge = border_edges.top();
        border_edges.pop();
        while (!edgeInBorder(min_edge, tree_nodes)) {
            min_edge = border_edges.top();
            border_edges.pop();
        }
        //agrego la nueva arista
        tree_edges.insert(min_edge);
        tree_nodes.insert(min_edge.secondNode);

        int new_node_index = selectNewNodeIndex(min_edge, tree_nodes);
        for (Edge e : graph[new_node_index].edges) {
            if (edgeInBorder(e, tree_nodes)) border_edges.push(e);
        }
    }
    return tree_edges;
}

using namespace std;

int main() {
    vector<Node> v;
    for (int i = 0; i < 5; i++) {
        v.push_back(Node(i));
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