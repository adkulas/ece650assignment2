#pragma once

// An example of a complex number
// See complex_main.cpp for compilation instructions

#include <cmath>
#include <iostream>
#include <vector>
#include <list>
#include <climits>

class Graph {
private:
    int vertices;
    std::vector< std::vector<int> > graph;
    std::vector<int> pred;
    std::vector<int> dist;

    bool breadth_first_search(int src, int dest);

public:
    Graph( int vertices = 0 );

    /// Accessors
    void print_shortest_path(int src, int dest);

    /// Mutators
    void add_edge(int src, int dest);

};

// Constructor
inline Graph::Graph( int v ):
    vertices(v), graph(v), pred(v), dist(v) {/*empty constructor*/}

inline bool Graph::breadth_first_search(int src, int dest) {
    std::list<int> queue;
    bool visited[vertices];

    // initialization: visted to false dist to inf and no predecessors
    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    // source is first to be visited and 
    // distance from source to itself should be 0 
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);

    // iterate through graph breadth first and halt when destination is found
    while (!queue.empty()) {
        int n = queue.front();
        queue.pop_front();
        for (int i =0; i < graph[n].size(); i++) {
            if (visited[graph[n][i]] == false) 
            {
                visited[graph[n][i]] == true;
                dist[graph[n][i]] = dist[n] + 1;
                pred[graph[n][i]] = n;
                queue.push_back(graph[n][i]);

                if (graph[n][i] == dest) {
                    return true;
                }
            }
        }
    }
    return false;
}

inline void Graph::add_edge(int src, int dest) {
    graph[src].push_back(dest); 
    graph[dest].push_back(src);

    return;
}

inline void Graph::print_shortest_path(int src, int dest) {
    std::vector<int> shortest_path;
    int current = dest;

    if (breadth_first_search(src, dest) == false) {
        std::cout << "There is no path between Souce: " << src 
                  << " and Destination: " << dest << std::endl;
        
        return;
    }

    shortest_path.push_back(current);
    while (pred[current] != -1) {
        shortest_path.push_back(pred[current]);
        current = pred[current];
    }

    for (int i = shortest_path.size() -1; i >=0; i--) {
        std::cout << shortest_path[i];
        if (i > 0) std::cout << "-";
    }
    std::cout << std::endl;

    return;
}
