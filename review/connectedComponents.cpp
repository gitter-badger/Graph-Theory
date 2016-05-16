#include <iostream>
#include <list>
#include <fstream>

using namespace std;

class Graph {
private:
	int V;
	// Pointer to array containing adjacency lists
	list<int> *adj;
	void DFSUtil(int v, bool visited[]);
public:
	Graph(int V);
	~Graph();
	friend istream& operator >>(istream& is, Graph& g);
	int readFile(char const * filename);
	void addEdge(int src, int dest);
	void connectedComponents();
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}

Graph::~Graph() {
	delete [] adj;
}

istream& operator >>(istream& is, Graph& g) {
	int val = 0;
	is >> g.V;
	g.adj = new list<int>[g.V];

	for (int i = 0; i < g.V; i++) {
		for (int j = 0; j < g.V; j++) {
			is >> val;
			if (val == 1) {
				g.addEdge(i, j);
			}
		}
	}
	return is;
}

int Graph::readFile(char const * filename) {
	fstream f(filename, ios::in);
	f >> (*this);
	f.close();
	return 1;
}

void Graph::addEdge(int src, int dest) {
	if (src >= V || dest >= V) {
		cout << "Error: cannot add edge!" << endl;
	}
	else {
		adj[src].push_back(dest);
		adj[dest].push_back(src);
	}
}

void Graph::DFSUtil(int v, bool visited[]) {
	// Mark the current vertex as visited and print it
	visited[v] = true;
	cout << v << " ";

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); i++) {
		if (visited[*i] == false) {
			DFSUtil(*i, visited);
		}
	}
}

void Graph::connectedComponents() {
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int v = 0; v < V; v++) {
		visited[v] = false;
	}

	for (int v = 0; v < V; v++) {
		if (visited[v] == false) {
			DFSUtil(v, visited);
			cout << endl;
		}
	}
}

int main() {
	Graph g(0);
	g.readFile("input.txt");
	cout << "Connected components:" << endl;
	g.connectedComponents();
	return 0;
}
