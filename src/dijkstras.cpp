#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous.assign(numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minheap;

    minheap.push({0, source});

    while (!minheap.empty()){
        auto [curr_dist, u] = minheap.top();
        minheap.pop();

        if (visited[u]) continue;
        visited[u] = true;
        for (auto & edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && curr_dist + weight < distances[v]) {
                distances[v] = curr_dist + weight;
                previous[v] = u; 
                minheap.push({distances[v], v});
            }
        }
    }
    return distances;

}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}