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
	int getVertex() {
		return vertex;
	}
	stack<int> tour;
	friend istream& operator>>(istream& is, Graph& g);
	friend ostream& operator<<(ostream& os, Graph g);
	int readFile(char const * filename);
	int writeFile(char const * filename, int isEuler);
	void find_tour(int u);
	void find_euler_walk();
	int checkGraph();
};

int Graph::checkGraph() {
	for (int i = 0; i < this->vertex; i++) {
		int sum = 0;
		for (int j = 0; j < this->vertex; j++) {
			sum += this->a[i][j];
		}
		if (sum % 2 != 0) {
			return 2;
		}
	}
	return 1;
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
			os << g.tour.top()+1 << endl;
			g.tour.pop();
		}
		else {
			os << g.tour.top()+1 << "->";
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

int Graph::writeFile(char const * filename, int isEuler) {
	fstream f(filename, ios::out);
	if (isEuler == 1) {
		f << "CHU TRINH EULER:" << endl;
		f << (*this);
	}
	else {
		f << "DUONG DI EULER:" << endl;
		f << (*this);
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

void Graph::find_euler_walk() {
	for (int i = 0; i < this->vertex; i++) {
		int sum = 0;
		for (int j = 0; j < this->vertex; j++) {
			sum += this->a[i][j];
		}
		if (sum % 2 != 0) {
			this->find_tour(i);
			break;
		}
	}
}

int main() {
	Graph g1, g2;
	g1.readFile("a.txt");
	g2.readFile("b.txt");
	
	int isEuler_1 = g1.checkGraph();
	int isEuler_2 = g2.checkGraph();

	if (isEuler_1 == 1) {
		g1.find_tour(0);
	}
	else {
		g1.find_euler_walk();
	}

	if (isEuler_2 == 1) {
		g2.find_tour(0);
	}
	else {
		g2.find_euler_walk();
	}

	g1.writeFile("out1.txt", isEuler_1);
	g2.writeFile("out2.txt", isEuler_2);
	return 0;
}