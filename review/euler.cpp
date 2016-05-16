#include <iostream>
#include <stack>
#include <list>

using namespace std;

class Graph {
private:
	int V;
	list<int> *adj;
public:
	Graph(int V);
	~Graph();
	void addEdge(int src, int dest);
	int isEulerian();
	bool isConnected();
	void DFSUtil(int v, bool visited[]);
	void findTour(int v, stack<int> &tour);
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}

Graph::~Graph() {
	delete [] adj;
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

void Graph::DFSUtil(int v, bool visited[]) {
	visited[v] = true;
	list<int>::iterator i;
	for(i = adj[v].begin(); i != adj[v].end(); i++) {
		if (visited[*i] == false) {
			DFSUtil(*i, visited);
		}
	}
}

bool Graph::isConnected() {
	bool *visited = new bool[V];
	int i;
	for (int v = 0; v < V; v++) {
		visited[v] = false;
	}
	DFSUtil(0, visited);
	// Check if all non-zero degree vertices are visited
	for (i = 0; i < V; i++) {
		if (visited[i] == false && adj[i].size() > 0) {
			return false;
		}
	}
	return true;
}

int Graph::isEulerian() {
	if (isConnected() == false) {
		return 0;
	}
	int odd = 0;
	for (int i = 0; i < V; i++) {
		if (adj[i].size() & 1) {
			odd++;
		}
	}
	if (odd > 2) {
		return 0;
	}
	return (odd)? 1 : 2;
}

void Graph::findTour(int v, stack<int> &tour) {
	while (!adj[v].empty()) {
		int u = adj[v].front();
		adj[v].pop_front();
		adj[u].remove(v);
		findTour(u, tour);
	}
	tour.push(v);
}

void printTour(stack<int> &tour) {
	while (!tour.empty()) {
		cout << tour.top() << " ";
		tour.pop();
	}
	cout << endl;
}

void test(Graph& g) {
	int res = g.isEulerian();
	if (res == 0) {
		cout << "Graph is not Eulerian." << endl;
	}
	else if (res == 1) {
		cout << "Graph has a Euler path: ";
		stack<int> tour;
		g.findTour(0, tour);
		printTour(tour);
	}
	else {
		cout << "Graph has a Euler cycle: ";
		stack<int> tour;
		g.findTour(0, tour);
		printTour(tour);
	}
}

int main () {
	Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    test(g1);
 
    Graph g2(5);
    g2.addEdge(1, 0);
    g2.addEdge(0, 2);
    g2.addEdge(2, 1);
    g2.addEdge(0, 3);
    g2.addEdge(3, 4);
    g2.addEdge(4, 0);
    test(g2);
 
    Graph g3(5);
    g3.addEdge(1, 0);
    g3.addEdge(0, 2);
    g3.addEdge(2, 1);
    g3.addEdge(0, 3);
    g3.addEdge(3, 4);
    g3.addEdge(1, 3);
    test(g3);

    Graph g4(3);
    g4.addEdge(0, 1);
    g4.addEdge(1, 2);
    g4.addEdge(2, 0);
    test(g4);

    Graph g5(3);
    test(g5);

	return 0;
}