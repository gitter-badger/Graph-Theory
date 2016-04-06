#include <iostream>
#include <fstream>

using namespace std;

#define MAX 100

struct Node {
	int v1, v2;

	Node() {
		v1 = v2 = 0;
	}
};

class Graph {

private:
	int edges;
	Node* a[MAX];
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
	is >> g.edges;

	for (int i = 0; i < g.edges; i++) {
		g.a[i] = new Node();
		is >> g.a[i]->v1 >> g.a[i]->v2;
	}

	return is;
}

ostream& operator<<(ostream& os, Graph g) {
	os << g.edges << endl;

	for (int i = 0; i < g.edges; i++) {
		os << g.a[i]->v1 << " " << g.a[i]->v2 << endl;
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
	
	f << this->edges << endl;

	for (int i = 0; i < this->edges; i++) {
		f << this->a[i]->v1 << " " << this->a[i]->v2;
		f << endl;
	}

	f.close();
	return 1;
}

int main() {
	Graph g;
	g.readFile("bai_3_input.txt");
	cout << g << endl;
	g.writeFile("bai_3_output.txt");
	return 0;
}