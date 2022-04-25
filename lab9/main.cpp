#include <iostream>
#include "graph.hpp"
#include <chrono>

int main() {
    int vertices;
    int edges;
    
    std::cin >> vertices >> edges;
    TGraph graph(vertices);
    int vertex_1, vertex_2;
    for (int i = 0; i < edges; i++) {
        std::cin >> vertex_1 >> vertex_2;
        graph.AddConnection(vertex_1, vertex_2);
    }
    for (int i = 1; i < vertices + 1; i++) {
        if (graph.IsTraversed(i) == false) {
            graph.DFS(i);
            graph.PrintComponent();
            graph.RemoveCurrentComponent();
        }
    }
    return 0;
}