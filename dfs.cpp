#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

void addEdge(vector<vector<int>>& adjList, int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u); // For undirected graph
}

void DFS(vector<vector<int>>& adjList, int start) {
    int V = adjList.size();
    vector<bool> visited(V, false);
    
    stack<int> stk;
    stk.push(start);
    visited[start] = true;

    while (!stk.empty()) {
        int current = stk.top();
        stk.pop();
        cout << current << " ";

        #pragma omp parallel for
        for (int i = 0; i < adjList[current].size(); i++) {
            int neighbor = adjList[current][i];
            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    stk.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> adjList(V);

    cout << "Enter the pairs of edges:\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cout << "Enter edge " << i + 1 << ": ";
        cin >> u >> v;
        addEdge(adjList, u, v);
    }

    int startVertex;
    cout << "Enter the start vertex: ";
    cin >> startVertex;

    cout << "DFS Traversal starting from vertex " << startVertex << ": ";
    DFS(adjList, startVertex);
    cout << endl;

    return 0;
}

