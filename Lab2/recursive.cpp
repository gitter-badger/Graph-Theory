#include <iostream>
#include <fstream>

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

void visit(Graph &g, int i, int label[], int flag) {
	label[i] = flag;
	for (int j = i + 1; j < g.vertex; j++) {
		if (label[j] == 0 && g.a[i][j] == 1) {
			visit(g, j, label, flag);
		}
	}
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

void DFS(Graph g, char const * filename) {
	int label[MAX];
	int connected = 1;
	for (int i = 0; i < g.vertex; i++) {
		label[i] = 0;
	}
	for (int i = 0; i < g.vertex; i++) {
		if (label[i] == 0) {
			visit(g, i, label, connected);
			connected++;
		}
	}
	check(--connected, label, g.vertex, filename);
}

int main() {
	Graph g;
	g.readFile("input.txt");
	DFS(g, "output1.txt");
	return 0;
}
