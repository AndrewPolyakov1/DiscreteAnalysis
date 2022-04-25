#include "graph.hpp"

TGraph::TGraph(int vnum) {
    Edges = new std::set<int>[vnum + 1];
    Checked = new bool[vnum + 1];
    std::memset(Checked, 0, vnum + 1);
}

// Adding new connection
void TGraph::AddConnection(int v1, int v2) {
    Edges[v1].insert(v2);
    Edges[v2].insert(v1);
}

// Search connectivity component
void TGraph::DFS(int vertex) {
    Checked[vertex] = true;
    ConnectivityComponent.push_back(vertex);
    for (std::set<int>::iterator iter = Edges[vertex].begin(); iter != Edges[vertex].end(); iter++) {
        if (Checked[(*iter)] == false) {
            DFS(*iter);
        }
    }
}

void TGraph::PrintComponent() {
    std::sort(ConnectivityComponent.begin(), ConnectivityComponent.end());
    for (size_t i = 0; i < ConnectivityComponent.size(); i++) {
        std::cout << ConnectivityComponent[i] << " ";
    }
    std::cout << "\n";
}

void TGraph::RemoveCurrentComponent() {
    ConnectivityComponent.clear();
}

// Checking whether the vertex has been traversed
bool TGraph::IsTraversed(int v) {
    return Checked[v];
}

TGraph::~TGraph() {
    delete [] Edges;
    delete [] Checked;
}