#include<iostream>
#include<vector>

namespace graph {

int INF = 999999;

typedef std::vector<std::vector<std::pair<int, int>>> adjacencyList;
//first index selects the node, second one selects a pair.
//The pair represents destination and weight of an edge.


adjacencyList readGraph() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    adjacencyList graph(vertex_count);
    int from, to, weight;
    for (int i = 0; i < edge_count; i++) {
        std::cin >> from >> to >> weight;
        graph[from].push_back({to, weight});
    }
    return graph;
}

std::vector<int> bellmanFord(const adjacencyList &graph, int source) {
    //init
    std::vector<int> distances(graph.size(), INF);
    distances[source] = 0;
    for (uint iterations = 0; iterations < graph.size(); ++iterations) {
        //iterate vertex_count times.
        bool changed_a_distance = false;
        //for each iteration we visit all the edges.
        for (uint i = 0; i < graph.size(); ++i) {
            for (uint j = 0; j < graph[i].size(); ++j) {
                //for each edge, if it improves a distance, we record that.
                int other_vertex = graph[i][j].first;
                int weight = graph[i][j].second;
                if (distances[other_vertex] > distances[i] + weight) {
                    distances[other_vertex] = distances[i] + weight;
                    changed_a_distance = true;
                }
            }
        }
        if (!changed_a_distance) break;
    }
    return distances;
}


bool hasNegativecycle(const adjacencyList &graph) {
    //init
    int source = 0;
    bool negative_cycle = false;
    std::vector<int> distances(graph.size(), INF);
    distances[source] = 0;
    for (uint iterations = 0; iterations < graph.size(); ++iterations) {
        //iterate vertex_count times.
        bool changed_a_distance = false;
        //for each iteration we visit all the edges.
        for (uint i = 0; i < graph.size(); ++i) {
            for (uint j = 0; j < graph[i].size(); ++j) {
                //for each edge, if it improves a distance, we record that.
                int other_vertex = graph[i][j].first;
                int weight = graph[i][j].second;
                //Here is where we have to modify to make it
                //work with multiplication instead of addition.
                if (distances[other_vertex] > distances[i] + weight) {
                    distances[other_vertex] = distances[i] + weight;
                    changed_a_distance = true;
                }
            }
            if (!changed_a_distance) break;
        }
        //check for negative cycles, over all edges.
        for (uint i = 0; i < graph.size(); ++i) {
            for (uint j = 0; j < graph[i].size(); ++j) {
                //for each edge, if it improves a distance, we record that.
                int other_vertex = graph[i][j].first;
                int weight = graph[i][j].second;
                if (distances[other_vertex] > distances[i] + weight) {
                    negative_cycle = true;
                }
            }
        }
        //return negative_cycle;
    }
    return negative_cycle;

}


}//end of namespace
int main() {
    //Init.
    graph::adjacencyList g = graph::readGraph();

    //Bellman-Ford:
    std::vector<int> res = graph::bellmanFord(g, 0);
    for (int i : res) std::cout << i << std::endl;
}
