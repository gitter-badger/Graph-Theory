#include <iostream>
#include <fstream>

using namespace std;

#define MAX 100

class Graph {

private:
	int vertex;
	int a[MAX][MAX];

public:
	Graph() {
		// pass
	}

	~Graph() {
		// pass
	}

	friend istream& operator>>(istream&, Graph&);
	friend ostream& operator<<(ostream&, Graph);

	int readFile(char*);
	int writeFile(char*);

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

ostream& operator<<(ostream& os, Graph g) {
	int edges = 0;

	for (int i = 0; i < g.vertex; i++) {
		for (int j = i; j < g.vertex; j++) {
			if (g.a[i][j] == 1) {
				edges++;
			}
		}
	}

	os << edges << endl;

	for (int i = 0; i < g.vertex; i++) {
		for (int j = i; j < g.vertex; j++) {
			if (g.a[i][j] == 1) {
				os << i + 1 << " " << j + 1 << endl;
			}
		}
	}

	return os;
}

int Graph::readFile(char* filename) {
	fstream f(filename, ios::in);
	f >> (*this);
	f.close();
	return 1;
}

int Graph::writeFile(char* filename) {
	fstream f(filename, ios::out);
	f << (*this);
	f.close();
	return 1;
}

int main() {
	Graph g;
	g.readFile("bai_5_input.txt");
	g.writeFile("bai_5_output.txt");
	return 0;
}