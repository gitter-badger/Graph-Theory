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
	int path[MAX];
	int label[MAX];
	int getV() {
		return vertex;
	}
	friend istream& operator>>(istream& is, Graph& g);
	friend ostream& operator<<(ostream& is, Graph g);
	int readFile(char const * filename);
	int writeFile(char const * filename);
	int findHamiltonPath(int inter, int currVertex);
	void HamiltonPath(int vertex);
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
	for (int i = 0; i < g.getV(); i++) {
		os << g.path[i] << " ";
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

int Graph::findHamiltonPath(int inter, int currVertex) {
	if (inter == this->vertex) {
		for (int i = 0; i < this->vertex; i++) {
			cout << path[i] << " ";
		}
		cout << endl;
		return 0;
	}
	for (int i = 0; i < this->vertex; i++) {
		if (this->a[currVertex][i] == 1 && label[i] == 0) {
			label[i] = 1;
			path[inter] = i;
			if (findHamiltonPath(inter + 1, i) == 1) {
				return 1;
			}
			label[i] = 0;
		}
	}
	return 0;
}

void Graph::HamiltonPath(int vertex) {
	for (int i = 0; i < this->vertex; i++) {
		label[i] = 0;
		path[i] = 0;
	}
	path[vertex] = vertex;
	findHamiltonPath(1, vertex);
}


int main() {
	Graph g;
	g.readFile("input.txt");
	g.HamiltonPath(0);
	g.writeFile("output.txt");
	return 0;
}
