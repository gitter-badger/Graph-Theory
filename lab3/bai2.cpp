#include <iostream>
#include <fstream>

using namespace std;

#define MAX 100

class Graph {
public:
	int vertex;
	int infected;
	int a[MAX][MAX];
public:
	Graph() {
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				this->a[i][j] = 0;
			} 
		}
	}
	~Graph() {
		// pass
	}
	int readFile(char const * filename);
};

int Graph::readFile(char const * filename) {
	char value;
	fstream f(filename, ios::in);
	f.get(value);
	this->vertex = value - '0';
	f.get(value);
	f.get(value);
	this->infected = value - '0';
	f.get(value);
	for (int i = 0; i < vertex; i++) {
		f.get(value);
		f.get(value);
		f.get(value);
		while (!f.eof()) {
			if (value == ' ') {
				f.get(value);
			}
			else if (value == '\n') {
				break;
			}
			else {
				int temp = value - '0';
				this->a[i][temp-1] = 1;
				this->a[temp-1][i] = 1;
				f.get(value);
			}
		}	
	}
	f.close();
	return 1;
}

int writeFile(char const * filename, Graph &g, int label[]) {
	int infected_num = 0;
	for (int i = 0; i < g.vertex; i++) {
		if (label[i] == g.infected) {
			infected_num++;
		}
	}
	fstream f(filename, ios::out);
	f<< infected_num << endl;
	for (int i = 0; i < g.vertex; i++) {
		if (label[i] == g.infected) {
			f << i+1 << " ";
		}
	}
	return 1;
}

void visit(Graph &g, int i, int label[], int flag) {
	label[i] = flag;
	for (int j = 0; j < g.vertex; j++) {
		if (label[j] == 0 && g.a[i][j] == 1) {
			visit(g, j, label, flag);
		}
	}
}

void DFS(Graph g, int label[]) {
	for (int i = 0; i < g.vertex; i++) {
		label[i] = 0;
	}
	visit(g, g.infected, label, g.infected);
}


int main() {
	Graph g;
	int label[MAX];
	g.readFile("SARS.INP");
	DFS(g, label);
	writeFile("SARS.OUT", g, label);
	return 0;
}