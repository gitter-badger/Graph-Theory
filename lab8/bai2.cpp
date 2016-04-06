#include <iostream>
#include <fstream>
#include <vector>
#include  <limits.h>

using namespace std;

#define MAX 100


class Graph {
public:
	int n;
	int a[MAX][MAX];
	vector<int> place;
	// place[0]: Truong Nam
	// place[1]: Truong Nu
	// place[2]: Nha Phong
	// place[3]: Nha Phung
	// place[4]: Diem hen ho
public:
	Graph() {
		this->n = 0;
	}
	friend istream& operator>>(istream& is, Graph &g);
	int readFile(char const * filename);
	int writeFile(char const * filename);
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
	while (is >> temp) {
		g.place.push_back(temp);
	}
	return is;
}

int Graph::readFile(char const * filename) {
	fstream f(filename, ios::in);
	f >> (*this);
	f.close();
	return 1;
}

void findPath(int parent[], int j, vector<int> &path) {
	if (parent[j] == -1) {
		path.push_back(j);
		return;
	}
	findPath(parent, parent[j], path);
	path.push_back(j);
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

int Dijkstra(Graph &g, int Vstart, int Vend, int dist[], int parent[]) {
	bool sptSet[MAX];
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
}

int Graph::writeFile(char const * filename) {
	fstream f(filename, ios::out);
	
	int dist1[MAX];
	int dist2[MAX];
	int dist3[MAX];
	int dist4[MAX];

	int parent1[MAX];
	int parent2[MAX];
	int parent3[MAX];
	int parent4[MAX];
	
	Dijkstra((*this), this->place[0], this->place[4], dist1, parent1);
	Dijkstra((*this), this->place[1], this->place[4], dist2, parent2);
	Dijkstra((*this), this->place[4], this->place[2], dist3, parent3);
	Dijkstra((*this), this->place[4], this->place[3], dist4, parent4);

	vector<int> path1;
	vector<int> path2;
	vector<int> path3;
	vector<int> path4;

	findPath(parent1, this->place[4], path1);
	findPath(parent2, this->place[4], path2);
	findPath(parent3, this->place[2], path3);
	findPath(parent4, this->place[3], path4);


	f << dist1[this->place[4]] +
		 dist2[this->place[4]] +
		 dist3[this->place[2]] +
		 dist4[this->place[3]] << endl;

	for (int i = 0; i < path1.size(); i++) {
		f << path1[i] << " ";
	}
	
	for (int i = 0; i < path2.size(); i++) {
		f << path2[i] << " ";
	}
	
	for (int i = 0; i < path3.size(); i++) {
		f << path3[i] << " ";
	}
	
	for (int i = 0; i < path4.size(); i++) {
		f << path4[i] << " ";
	}

	f.close();
	return 1;
}

int main() {
	Graph g;
	g.readFile("HENHO.IN");
	g.writeFile("HENHO_DIJKSTRA.OUT");
	return 0;
}
