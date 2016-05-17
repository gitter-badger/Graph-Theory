#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

struct Edge {
	int src;
	int dest;
	double weight;
};

class Graph {
private:
	int V;
	std::vector<Edge> edge;
public:
	Graph(int V);
	void addEdge(int src, int dest, int weight);
	void BellmanFord(int src);
};

Graph::Graph(int V) {
	this->V = V;
}

void Graph::addEdge(int src, int dest, int weight) {
	Edge e;
	e.src = src;
	e.dest = dest;
	e.weight = weight;
	edge.push_back(e);
}

void printSolution(int dist[], int V) {
	for (int i = 0; i < V; i++) {
		cout << i << " " << dist[i] << endl;
	}
}

void Graph::BellmanFord(int src) {
	int dist[V];

	for (int i = 0; i < V; i++) {
		dist[i] = INT_MAX;
	}

	dist[src] = 0;

	for (int i = 1; i <= V-1; i++) {
		for (int j = 0; j < edge.size(); j++) {
			int u = edge[j].src;
			int v = edge[j].dest;
			int weight = edge[j].weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
			}
		}
	}

	for (int j = 0; j < edge.size(); j++) {
		int u = edge[j].src;
		int v = edge[j].dest;
		int weight = edge[j].weight;
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
			dist[v] = dist[u] + weight;
		}
	}

	printSolution(dist, V);
}

int main() {
	Graph g(5);

	g.addEdge(0, 1, -1);
	g.addEdge(0, 2, 4);
	g.addEdge(1, 2, 3);
	g.addEdge(1, 3, 2);
	g.addEdge(1, 4, 2);
	g.addEdge(3, 2, 5);
	g.addEdge(3, 1, 1);
	g.addEdge(4, 3, -3);

	g.BellmanFord(0);

	return 0;
}
