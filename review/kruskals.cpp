#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
	int src;
	int dest;
	double weight;

	static bool asc(const Edge& e1, const Edge& e2) {
		return e1.weight < e2.weight;
	}
	static bool desc(const Edge& e1, const Edge& e2) {
		return e1.weight > e2.weight;
	}
};

class Graph {
private:
	int V;
	std::vector<Edge> edge;
public:
	Graph(int V);
	void addEdge(int src, int dest, double weight);
	void sortEdgeAsc();
	void sortEdgeDesc();
	void kruskalsMST();
};

Graph::Graph(int V) {
	this->V = V;
}

void Graph::sortEdgeAsc() {
	std::sort(edge.begin(), edge.end(), Edge::asc);
}

void Graph::sortEdgeDesc() {
	std::sort(edge.begin(), edge.end(), Edge::desc);
}

void Graph::addEdge(int src, int dest, double weight) {
	Edge e;
	e.src = src;
	e.dest = dest;
	e.weight = weight;
	edge.push_back(e);
}

void printSolution(std::vector<Edge> &edge) {
	cout << "Edge Weight" << endl;
	for (int i = 0; i < edge.size(); i++) {
		cout << edge[i].src << "-" << edge[i].dest << "  " << edge[i].weight << endl;
	}
}

bool isCircle(int v, int V, int parent[], std::vector<Edge> &edge) {
	if (parent[edge[v].src] == parent[edge[v].dest]) {
		return true;
	}
	int min = (parent[edge[v].src] > parent[edge[v].dest])?  parent[edge[v].dest] : parent[edge[v].src];
	int max = (parent[edge[v].src] > parent[edge[v].dest])?  parent[edge[v].src] : parent[edge[v].dest];
	for (int i = 0; i < V; i++) {
		if (parent[i] == max) {
			parent[i] = min;
		}
	}
	return false;
}

void Graph::kruskalsMST() {
	std::vector<Edge> result;
	int parent[V];
	int i = 0;

	for (int v = 0; v < V; v++) {
		parent[v] = v;
	}

	sortEdgeAsc();

	while (result.size() < V-1) {
		if (!isCircle(i, V, parent, edge)) {
			result.push_back(edge[i]);
		}
		i++;
	}

	printSolution(result);
}

int main() {
	Graph g(7);

	g.addEdge(0, 3, 5);
	g.addEdge(0, 1, 7);
	g.addEdge(1, 3, 9);
	g.addEdge(1, 2, 8);
	g.addEdge(2, 4, 5);
	g.addEdge(1, 4, 7);
	g.addEdge(3, 4, 15);
	g.addEdge(3, 5, 6);
	g.addEdge(4, 5, 8);
	g.addEdge(4, 6, 9);
	g.addEdge(5, 6, 11);

	g.kruskalsMST();
	
	return 0;
}