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

	int check(int&);
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
	os << g.vertex << endl;
	for (int i = 0; i < g.vertex; i++) {
		for (int j = 0; j < g.vertex; j++) {
			os << g.a[i][j] << " ";
		}
		os << endl;
	}
	return os;
}


int Graph::readFile(char* filename) {
	fstream f(filename, ios::in);
	f >> (*this);
	f.close();
	return 1;
}

int Graph::check(int& degree) {
	for (int i = 0; i < this->vertex; i++) {
		for (int j = 0; j < this->vertex; j++) {
			if (this->a[i][j] != this->a[j][i]) {
				return 0; // do thi co huong
			}
			else if (this->a[i][j] == this->a[j][i]) {
				degree++;
			}
		}
	}
	return 1; // do thi vo huong
}

int main() {
	int degree = 0;
	Graph g;
	g.readFile("bai_8_input.txt");
	cout << g << endl;
	
	if (g.check(degree) > 0) {
		cout << "Do thi vo huong" << endl;
		cout << "So bac cua do thi: " << degree / 2 << endl;
	}

	return 0;
}