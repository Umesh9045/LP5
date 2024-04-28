#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void addEdge(vector<vector<int>>& adjList, int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u); // For undirected graph
}

void BFS(vector<vector<int>>& adjList, int start) {
    int V = adjList.size();
    vector<bool> visited(V, false);
    
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";

        #pragma omp parallel for
        for (int i = 0; i < adjList[current].size(); i++) {
            int neighbor = adjList[current][i];
            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    q.push(neighbor);
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

    cout << "BFS Traversal starting from vertex " << startVertex << ": ";
    BFS(adjList, startVertex);
    cout << endl;

    return 0;
}

// OUTPUT:
// Enter the number of vertices: 5
// Enter the number of edges: 4
// Enter the pairs of edges:
// Enter edge 1: 0 1
// Enter edge 2: 0 2
// Enter edge 3: 0 3
// Enter edge 4: 0 4
// Enter the start vertex: 0
// BFS Traversal starting from vertex 0: 0 1 2 3 4 


