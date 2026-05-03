
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

const int INF = 1000000000;

class Graph {
private:
    int vertexCount;
    bool directed;
    vector<vector<int>> matrix;

    void DFSUtil(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        cout << vertex << " ";

        for (int i = 0; i < vertexCount; i++) {
            if (matrix[vertex][i] != INF && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

public:
    Graph(int n, bool isDirected) {
        vertexCount = n;
        directed = isDirected;
        matrix.assign(vertexCount, vector<int>(vertexCount, INF));

        for (int i = 0; i < vertexCount; i++) {
            matrix[i][i] = 0;
        }
    }

    void addEdge(int from, int to, int weight) {
        if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            cout << "Invalid edge: " << from << " -> " << to << endl;
            return;
        }

        if (weight < 0) {
            cout << "Dijkstra cannot use negative weight edges." << endl;
            return;
        }

        matrix[from][to] = weight;

        if (!directed) {
            matrix[to][from] = weight;
        }
    }

    void printMatrix() {
        cout << "Adjacency Matrix:" << endl;
        cout << setw(5) << " ";
        for (int i = 0; i < vertexCount; i++) {
            cout << setw(5) << i;
        }
        cout << endl;

        for (int i = 0; i < vertexCount; i++) {
            cout << setw(5) << i;
            for (int j = 0; j < vertexCount; j++) {
                if (matrix[i][j] == INF) {
                    cout << setw(5) << "-";
                } else {
                    cout << setw(5) << matrix[i][j];
                }
            }
            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(vertexCount, false);

        cout << "DFS from " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(vertexCount, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS from " << start << ": ";

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << current << " ";

            for (int i = 0; i < vertexCount; i++) {
                if (matrix[current][i] != INF && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        cout << endl;
    }

    void connectedComponents() {
        vector<bool> visited(vertexCount, false);
        int componentCount = 0;

        cout << "Connected Components:" << endl;

        for (int i = 0; i < vertexCount; i++) {
            if (!visited[i]) {
                componentCount++;
                cout << "Component " << componentCount << ": ";
                DFSUtil(i, visited);
                cout << endl;
            }
        }
    }

    void dijkstra(int start) {
        vector<int> distance(vertexCount, INF);
        vector<bool> selected(vertexCount, false);

        distance[start] = 0;

        for (int count = 0; count < vertexCount; count++) {
            int u = -1;
            int minDistance = INF;

            for (int i = 0; i < vertexCount; i++) {
                if (!selected[i] && distance[i] < minDistance) {
                    minDistance = distance[i];
                    u = i;
                }
            }

            if (u == -1) {
                break;
            }

            selected[u] = true;

            for (int v = 0; v < vertexCount; v++) {
                if (!selected[v] && matrix[u][v] != INF && distance[u] + matrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + matrix[u][v];
                }
            }
        }

        cout << "Dijkstra shortest path from " << start << ":" << endl;
        for (int i = 0; i < vertexCount; i++) {
            cout << "Vertex " << i << ": ";
            if (distance[i] == INF) {
                cout << "unreachable";
            } else {
                cout << distance[i];
            }
            cout << endl;
        }
    }
};

int main() {
    Graph graph(7, false); // false means this is an undirected graph.

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 10);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 3);
    // Vertex 6 is isolated, so it can test connected components and unreachable shortest path.

    graph.printMatrix();
    cout << endl;

    graph.DFS(0);
    graph.BFS(0);
    cout << endl;

    graph.connectedComponents();
    cout << endl;

    graph.dijkstra(0);

    return 0;
}
