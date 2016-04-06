#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

#define MAX 100

class Graph {
private:
	int vertex;
	int a[MAX][MAX];
public:
	Graph() {
		vertex = 0;
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				this->a[i][j] = 0;
			}
		}
	}
	~Graph() {
		//pass
	}
	stack<int> tour;
	friend istream& operator>>(istream& is, Graph& g);
	friend ostream& operator<<(ostream& os, Graph g);
	int readFile(char const * filename);
	int writeFile(char const * filename);
	void find_tour(int u);
	bool checkGraph();
};

bool Graph::checkGraph() {
	for (int i = 0; i < this->vertex; i++) {
		int sum = 0;
		for (int j = 0; j < this->vertex; j++) {
			sum += this->a[i][j];
		}
		if (sum % 2 != 0) {
			return false;
		}
	}
	return true;
}

istream& operator>>(istream& is, Graph& g) {
	int temp;
	is >> g.vertex;
	for (int i = 0; i < g.vertex; i++) {
		for (int j = 0; j < g.vertex; j++) {
			if (is) {
				is >> temp;
				g.a[i][j] = temp;
			}
		}
	}
	return is;
}

ostream& operator<<(ostream& os, Graph g) {
	while (!g.tour.empty()) {
		if (g.tour.size() == 1) {
			os << g.tour.top() + 1 << endl;
			g.tour.pop();
		}
		else {
			os << g.tour.top() + 1 << "->";
			g.tour.pop();
		}
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
	if (this->checkGraph()) {
		f << "CHU TRINH EULER:" << endl;
		f << (*this);
	}
	else {
		f << "KHONG CO LO TRINH NAO THOA" << endl;
	}
	f.close();
	return 1;
}

void Graph::find_tour(int u) {
	for (int i = 0; i < this->vertex; i++) {
		if (this->a[u][i] == 1) {
			this->a[u][i] = this->a[i][u] = 0;
			find_tour(i);
		}
	}
	tour.push(u);
}

int main() {
	Graph g;
	g.readFile("map.inp");
	if (g.checkGraph()) {
		g.find_tour(0);
	}
	g.writeFile("out.txt");
	return 0;
}