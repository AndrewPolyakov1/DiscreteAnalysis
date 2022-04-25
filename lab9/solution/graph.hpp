#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <cstring>
#include <algorithm>

class TGraph {
private:
    std::set<int> *Edges; // All connections for each vertex with vertices numbered above
    bool *Checked; // Massive for marking the traversed vertices
    std::vector<int> ConnectivityComponent; // For writing connectivity components
public:
    TGraph(int vertices);
    void AddConnection(int v1, int v2); // Adding new connection
    void DFS(int vertex); // Search connectivity component
    void PrintComponent();
    void RemoveCurrentComponent();
    bool IsTraversed(int v); // Checking whether the vertex has been traversed
    ~TGraph();
};