#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

struct Edge {
    int to;
    int weight;
};

struct Node {
    int vertex;
    int distance;

    bool operator<(const Node &other) const {
        return distance > other.distance; 
    }
};

void takeInput(unordered_map<int, vector<Edge>>& graph) {// If custom input check, then use this junk of code
    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter edges in the format (from to weight):\n";
    for (int i = 0; i < numEdges; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight; // Take input for each edge
        graph[from].push_back({to, weight}); // Add edge to the graph
    }
}

void printing(const unordered_map<int, vector<Edge>>& graph) {
    for (unordered_map<int, vector<Edge>>::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        int vertex = it->first;
        const vector<Edge>& edges = it->second;

        // Print vertex
        printf("Vertex %c -> ", 'A' + vertex);

        for (vector<Edge>::const_iterator edgeIt = edges.begin(); edgeIt != edges.end(); ++edgeIt) {
            const Edge& edge = *edgeIt;
            printf("(%c, %d) ", 'A' + edge.to, edge.weight);
        }
        printf("\n");
    }
}

// Dijkstras impl
vi dijkstra(int start, int end, unordered_map<int, vector<Edge>> &graph, int numVertices) {
    vi dist(numVertices, INT_MAX); // minimum distance to each vertex
    vi previous(numVertices, -1); // To reconstruct the path
    priority_queue<Node> pq;

    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;

        // Process all neighbors of u
        for (const Edge &edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                previous[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    // Reconstruct path from start to end
    vector<int> path;
    for (int at = end; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    unordered_map<int, vector<Edge>> graph;

    graph[0] = {{1, 2}, {3, 1}};  // A -> B,  D
    graph[1] = {{3, 3}, {4, 10}};      // B -> D, E
    graph[2] = {{0,4}, {5, 5}};          // C -> A, F
    graph[3] = {{6, 4}, {5, 8}, {4, 2}, {2, 2}};          // D -> G, F, E, C
    graph[4] = {{6, 6}};                  // E -> G
    graph[6] = {{5, 1}};                  // G -> F
    graph[5] = {};                        // F has no outgoing edge

    // takeInput(graph);
    // printing(graph);

    // user Input! 
    // int start, end;
    // cout << "Enter the starting point (as an integer, e.g., 0 for A): ";
    // cin >> start;
    // cout << "Enter the ending point (as an integer, e.g., 5 for F): ";
    // cin >> end;

    // vector<int> shortestPath = dijkstra(start, end, graph, 7);

    // cout << "Shortest path from " << char('A' + start) << " to " << char('A' + end) << ": ";
    // for (int vertex : shortestPath) {
    //     if (vertex >= 0 && vertex < 26) {
    //         cout << char('A' + vertex) << " ";
    //     }
    // }
    // cout << endl;


    //  as per presentation I fixed from A to F(0 to 5)
    vector<int> shortestPath = dijkstra(0, 5, graph, 7);

    cout << "Shortest path from A to F: ";
    for (int vertex : shortestPath) {
        cout << char('A' + vertex) << " ";
    }
    cout << endl;

/*
Sample Input: 
12
0 1 2
0 3 1
1 3 3
1 4 10
2 0 4
2 5 5
3 6 4
3 5 8
3 4 2
3 2 2
4 6 6
6 5 1
*/

    return 0;
}
