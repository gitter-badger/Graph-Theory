#include <iostream>
#include <list>

using namespace std;

/*----------------------
  Still not finish yet
----------------------*/

class Graph {
private:
	int V;
	list<int> *adj;
public:
	Graph(int V);
	~Graph();
	int getV();
	int getEdge(int src, int dest);
	void addEdge(int src, int dest);
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}

Graph::~Graph() {
	delete [] adj;
}

int Graph::getV() {
	return V;
}

int Graph::getEdge(int src, int dest) {
	list<int>::iterator i;
	for (i = adj[src].begin(); i != adj[src].end(); i++) {
		if (*i == dest) {
			return 1;
		}
	}
	return 0;
} 

void Graph::addEdge(int src, int dest) {
	if (src >= V || dest >= V) {
		return;
	}
	else {
		adj[src].push_back(dest);
		adj[dest].push_back(src);
	}
}

void printSolution(int path[]) {
	int i = 0;
	for (int i = 0; path[i] != NULL; i++) {
		cout << path[i] << " ";
	}
	cout << path[0] << endl;
}

bool isSafe(int v, Graph &g, int path[], int pos) {
	if (g.getEdge(path[pos-1], v) == 0) {
		return false;
	}
	for (int i = 0; i < pos; i++) {
		if (path[i] == v) {
			return false;
		}
	}
	return true;
}

bool hamiltonCycleUtil(Graph &g, int path[], int pos) {
	if (pos == g.getV()) {
		if (g.getEdge(path[pos-1], path[0]) == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	for (int v = 1; v < g.getV(); v++) {
		if (isSafe(v, g, path, pos)) {
			path[pos] = v;
			if (hamiltonCycleUtil(g, path, pos+1) == true) {
				return true;
			}
			path[pos] = -1;
		}
	}
	return false;
}

bool hamiltonCycle(Graph &g) {
	int *path = new int[g.getV()];
	for (int i = 0; i < g.getV(); i++) {
		path[i] = -1;
	}
	path[0] = 0;
	if (hamiltonCycleUtil(g, path, 1) == false) {
		return false;
	}
	printSolution(path);
	return true;
}

int main () {
	Graph g(5);
	g.addEdge(0, 1);
	g.addEdge(2, 1);
	g.addEdge(0, 3);
	g.addEdge(2, 4);
	g.addEdge(3, 1);
	g.addEdge(4, 1);
	g.addEdge(3, 4);
	hamiltonCycle(g);
	return 0;
}