#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <cstring>
#include <algorithm>

class TGraph {
private:
    std::set<int> *Edges; 
    bool *Checked; 
    std::vector<int> ConnectivityComponent; 
public:
    TGraph(int vertices);
    void AddConnection(int v1, int v2); 
    void DFS(int vertex); 
    void PrintComponent();
    void RemoveCurrentComponent();
    bool IsTraversed(int v); 
    ~TGraph();
};