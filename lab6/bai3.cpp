#include <iostream>
#include <fstream>

using namespace std;

#define MAX 100

struct Edge {
	int v1;
	int v2;
	double w;
};

class Graph {
public:
	int n;
	int a[MAX][MAX];
	Edge edge[MAX];
public:
	Graph() {
		this->n = 0;
	}
	friend istream& operator>>(istream& is, Graph& g);
	friend ostream& operator<<(ostream& is, Graph g);
	int readFile(char const * filename);
	int writeFile(char const * filename);
	Edge findMaxEdge(Graph g);
	void PrimAlgorithm(Graph g);
};

istream& operator>>(istream& is, Graph& g) {
	int temp;
	is >> g.n;
	for (int i = 0; i < g.n; i++) {
		for (int j = 0; j < g.n; j++) {
			g.a[i][j] = 0;
			if (is) {
				is >> temp;
				g.a[i][j] = temp;
			}
		}
	}
	return is;
}

double sum(Graph g) {
	double sum = 0;
	for (int i = 0; i < g.n-1; i++) {
		sum += g.edge[i].w;
	}
	return sum;
}

ostream& operator<<(ostream& os, Graph g) {
	os << sum(g) << endl;
	for (int i = 0; i < g.n-1; i++) {
		os << "(" << g.edge[i].v1 << "," << g.edge[i].v2 << "); ";
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

Edge findMaxEdge(Graph g, int vertex[]) {
	Edge eMax;
	eMax.v1 = -1;
	for (int i = 0; i < g.n; i++) {
		for (int j = 0; j < g.n; j++) {
			if (vertex[i] != 0 && vertex[j] == 0 && g.a[i][j] != 0) {
				if (eMax.v1 == -1 || eMax.w < g.a[i][j]) {
					eMax.w = g.a[i][j];
					eMax.v1 = i;
					eMax.v2 = j;
				}
			}
		}
	}
	return eMax;
}

void PrimAlgorithm(Graph& g) {
	int vertex[MAX];
	for (int i = 0; i < g.n; i++) {
		vertex[i] = 0;
	}
	int nEdge = 0;
	vertex[0] = 1;
	while (nEdge < g.n - 1) {
		Edge max = findMaxEdge(g, vertex);
		g.edge[nEdge] = max;
		nEdge++;
		vertex[max.v2] = 1;
		g.a[max.v1][max.v2] = 0;
	}
}

int main() {
	Graph g;
	g.readFile("input.txt");
	PrimAlgorithm(g);
	g.writeFile("VoThienHuy_51403394.txt");
	return 0;
}
