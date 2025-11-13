#include <bits/stdc++.h>
using namespace std;
struct Edge {
	int u, v, w;
};
void bellmanFord(int V, int E, vector<Edge>& edges, int src) {
	vector<int> dist(V, INT_MAX), pred(V, -1);
	dist[src] = 0;
// Step 2: Relax edges repeatedly
	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = edges[j].u;
			int v = edges[j].v;
			int w = edges[j].w;
			if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pred[v] = u;
			}
		}
	}
// Step 3: Check for negative-weight cycles
	for (int j = 0; j < E; j++) {
		int u = edges[j].u;
		int v = edges[j].v;
		int w = edges[j].w;
		if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
			cout << "Graph contains negative weight cycle\n";
			return;
		}
	}
	cout << "Vertex distances from source " << src << ":\n";
	for (int i = 0; i < V; i++) {
		if (dist[i] == INT_MAX)
			cout << i << " : INF\n";
		else
			cout << i << " : " << dist[i] << " (Predecessor: " << pred[i] << ")\n";
	}
}
int main() {
	int V = 5, E = 8;
	vector<Edge> edges = {
		{0, 1, -1}, {0, 2, 4}, {1, 2, 3},
		{1, 3, 2}, {1, 4, 2}, {3, 2, 5},
		{3, 1, 1}, {4, 3, -3}
	};
	bellmanFord(V, E, edges, 0);
	return 0;
}

//Time Complexity O(VE)

//Space Complexity O(V + E)