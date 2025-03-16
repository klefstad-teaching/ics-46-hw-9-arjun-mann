#include "dijkstras.h"
#include <cstddef>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = -1; //UNDEFINED
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});
    while(!minHeap.empty()) {
        // cout << "minheap size: " << minHeap.size() << endl;
        // cout << "minheap top: " << minHeap.top().second << endl;
        int u = minHeap.top().second;
        minHeap.pop();
        if(visited[u]) continue;
        visited[u] = true;
        for(Edge edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if(!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> res;
    if(distances[destination] == INF) return res;
    int i = destination;
    while(i != -1) {
        res.push_back(i);
        i = previous[i];
    }
    reverse(res.begin(), res.end());
    return res;
}

void print_path(const vector<int>& v, int total) {
    for(int vert : v) {
        cout << vert << " ";
    }   
    cout << endl;
    cout << "Total cost is " << total << endl;
}

void tester(string name, int src, int dest) {
    // cout << "starting" << endl;
    Graph G;
    file_to_graph(name, G);
    // cout << "read file to graph" << endl;
    // cout << G.numVertices << endl;
    vector<int> prev(G.numVertices);
    vector<int> dist = dijkstra_shortest_path(G, src, prev);
    // cout << "created dist" << endl;
    vector<int> path = extract_shortest_path(dist, prev, dest);
    // cout << "created path" << endl;
    print_path(path, dist[dest]);
    // cout << "finished printing" << endl;
}


