#include <iostream>
#include <fstream>
#include  <limits.h>

using namespace std;

#define MAX 100


class Graph {
public:
	int n;
	int a[MAX][MAX];
public:
	Graph() {
		this->n = 0;
	}
	friend istream& operator>>(istream& is, Graph &g);
	int readFile(char const * filename);

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

int Graph::readFile(char const * filename) {
	fstream f(filename, ios::in);
	f >> (*this);
	f.close();
	return 1;
}

void printPath(int parent[], int j) {
	if (parent[j] == -1) {
		cout << j << " ";
		return;
	}
	printPath(parent, parent[j]);
	cout << j << " ";
}

int printSolution(int dist[], int parent[], int Vstart, int Vend, int n) {
	for (int i = 0; i < n; i++) {
		if (i == Vend) {
			cout << "Distance from " << Vstart << " to " << Vend << ": " << dist[i] << endl;
			cout << "Path: ";
			printPath(parent, i);
			cout << endl;
			break;
		}
	}
}

int minDistance(Graph &g, int dist[], bool sptSet[]) {
	int min = INT_MAX;
	int min_index;
	for (int v = 0; v < g.n; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}
	}
	return min_index;
}

void DijkstraAlgorithm(Graph &g, int Vstart, int Vend) {
	int dist[MAX];
	bool sptSet[MAX];
	int parent[MAX];

	for (int i = 0; i < g.n; i++) {
		dist[i] = INT_MAX;
		sptSet[i] = false;
		parent[i] = -1;
	}
	dist[Vstart] = 0;

	for (int i = 0; i < g.n-1; i++) {
		int u = minDistance(g, dist, sptSet);
		sptSet[u] = true;
		for (int v = 0; v < g.n; v++) {
			if (!sptSet[v] && g.a[u][v] && dist[u]+g.a[u][v] < dist[v]) {
				parent[v] = u;
				dist[v] = dist[u] + g.a[u][v];
			}
		}
	}

	printSolution(dist, parent, Vstart, Vend, g.n);
}

int main() {
	Graph g;
	g.readFile("input.txt");
	DijkstraAlgorithm(g, 0, 2);
	return 0;
}
