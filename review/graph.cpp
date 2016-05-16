#include <fstream>
#include <iostream>

using namespace std;

class Graph {
private:
	int V;
	int edge[100][100];
public:
	Graph();
	Graph(int V);
	int getVertices();
	int getDegree();
	int addEdge(int src, int dest, int val);
	int getEdge(int src, int dest);
	int removeEdge(int src, int dest);
	friend istream& operator >>(istream& is, Graph& g);
	friend ostream& operator <<(ostream& os, Graph& g);
	int readFile(char const * filename);
	int writeFile(char const * filename);
};

Graph::Graph() {
	this->V = 0;
}

Graph::Graph(int V) {
	this->V = V;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			addEdge(i, j, 0);
		}
	}
}

int Graph::getVertices() {
	return this->V;
}

int Graph::getDegree() {
	int count = 0;
	for (int i = 0; i < this->V; i++) {
		for (int j = i; j < this->V; j++) {
			if (this->edge[i][j] == 1) {
				count++;
			}
		}
	}
	return count;
}

int Graph::addEdge(int src, int dest, int val) {
	if (src >= this->V || dest >= this->V) {
		return 0;
	}
	this->edge[src][dest] = val;
	this->edge[dest][src] = val;
	return 1;
}

int Graph::getEdge(int src, int dest) {
	if (src >= this->V || dest >= this->V) {
		return 0;
	}
	return this->edge[src][dest];
}

int Graph::removeEdge(int src, int dest) {
	if (src >= this->V || dest >= this->V) {
		return 0;
	}
	this->edge[src][dest] = 0;
	this->edge[dest][src] = 0;
	return 1;
}

istream& operator >>(istream& is, Graph& g) {
	is >> g.V;
	for (int i = 0; i < g.V; i++) {
		for (int j = 0; j < g.V; j++) {
			is >> g.edge[i][j];
		}
	}
	return is;
}

ostream& operator <<(ostream& os, Graph& g) {
	os << g.V << endl;
	for (int i = 0; i < g.V; i++) {
		for (int j = 0; j < g.V; j++) {
			os << g.edge[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

int Graph::readFile(char const * filename) {
	fstream f(filename, ios::in);
	f >> (*this);
	f.close();
	return 1;
}

int Graph::writeFile(char const * filename) {
	fstream f(filename, ios::out);
	f << (*this);
	f.close();
	return 1;
}

int main() {
	Graph g1;

	g1.readFile("input.txt");

	/*g1.addEdge(0, 1, 1);
	g1.addEdge(0, 2, 1);
	g1.addEdge(0, 3, 1);
	g1.addEdge(1, 2, 1);
	g1.addEdge(2, 3, 1);*/

	cout << "Vertices: " << g1.getVertices() << endl;
	
	//g1.removeEdge(2, 1);

	//cout << g1.getEdge(2, 1) << endl;

	cout << "Edges: " << g1.getDegree() << endl;

	g1.writeFile("output.txt");

	return 0;
}
