#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define MAX 100


class Graph {
public:
	int vertex;
	int a[MAX][MAX];
public:
	Graph() {
		// pass
	}
	~Graph() {
		// pass
	}
	friend istream& operator>>(istream& is, Graph& g);
	int readFile(char const * filename);
};


istream& operator>>(istream& is, Graph& g) {
	int temp;
	is >> g.vertex;
	for (int i = 0; i < g.vertex; i++) {
		for (int j = 0; j < g.vertex; j++) {
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

int minArray(int * array) {
	int min = array[0];
	int minIndex = 0;
	for (int i = 1; i < sizeof(array)/sizeof(array[0]); i++) {
		if (array[i] != -1 && array[i] < min) {
			minIndex = i;
		}
	}
	array[minIndex] = -1;
	return minIndex;
}

void check(int connected, int label[], int vertex, char const * filename) {
	fstream f(filename, ios::out);
	if (connected == 1) {
		f << "LIEN THONG" << endl;	
	}
	else {
		f << "KHONG LIEN THONG" << endl;
		f << connected << endl;
		int * count = new int[connected];
		for (int i = 0; i < connected; i++) {
			count[i] = 0;
			for (int j = 0; j < vertex; j++) {
				if (label[j] == i+1) {
					count[i]++;
				}
			}
		}
		for (int i = 0; i < connected; i++) {
			int minIndex = minArray(count);
			for (int j = 0; j < vertex; j++) {
				if (label[j] == minIndex+1) {
					f << j << " ";
				}
			}
			f << endl;
		}
	}
	f.close();
}

void visit(int u, Graph g, int label[], int connected) {
	queue<int> Q;
	label[u] = connected;
	Q.push(u);
	do {
		u = Q.front();
		Q.pop();
		int v = u + 1;
		for (v; v < g.vertex; v++) {
			if (label[v] == 0 && g.a[u][v] == 1) {
				label[v] = connected;
				Q.push(v);
			}
		}
	} while (!Q.empty());
}

void BFS(Graph g, char const * filename) {
	int connected = 1;
	int label[MAX];
	for (int i = 0; i < g.vertex; i++) {
		label[i] = 0;
	}
	for (int i = 0; i < g.vertex; i++) {
		if (label[i] == 0) {
			visit(i, g, label, connected);
			connected++;
		}
	}
	check(--connected, label, g.vertex, filename);
}

int main() {
	Graph g;
	g.readFile("input.txt");
	BFS(g, "output.txt");
	return 0;
}
