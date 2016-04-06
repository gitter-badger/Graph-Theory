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

	friend istream& operator>>(istream&, Graph&);
	friend ostream& operator<<(ostream&, Graph);

	int readFile(char*);
	void printOut();
	int check();
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

// kiem tra xem do thi vo huong hay co huong
int Graph::check() {
	for (int i = 0; i < this->vertex; i++) {
		for (int j = 0; j < this->vertex; j++) {
			if (this->a[i][j] != this->a[j][i]) {
				return 0; // do thi co huong
			}
		}
	}
	return 1; // do thi vo huong
}

int checkCanh(Graph g) {
	int count = 0;

	for (int i = 0; i < g.vertex; i++) {
		for (int j = 0; j < g.vertex; j++) {
			if (g.a[i][j] == 1) {
				count++;
			}
		}
	}
	
	if (g.check() == 1) {
		count /= 2;
	}

	return count;
}

void maxDegree(Graph g) {
	int list_v[MAX];
	int count = 0;
	int max = count;

	for (int i = 0; i < g.vertex; i++) {
		count = 0;
		for (int j = 0; j < g.vertex; j++) {
			count += g.a[i][j];
		}
		if (count > max) {
			max = count;
		}
		list_v[i + 1] = count;
	}

	cout << "Dinh co bac lon nhat: ";

	for (int i = 0; i <= g.vertex; i++) {
		if (list_v[i] == max) {
			cout << i << " ";
		}
	}

	cout << endl;
}

void minDegree(Graph g) {
	int list_v[MAX];
	int count = 0;
	int min = count;

	for (int i = 0; i < g.vertex; i++) {
		count = 0;
		for (int j = 0; j < g.vertex; j++) {
			if (g.a[i][j] == 0) {
				count++;
			}
		}
		if (count > min) {
			min = count;
		}
		list_v[i + 1] = count;
	}
	
	cout << "Dinh co bac nho nhat: ";
	
	for (int i = 0; i <= g.vertex; i++) {
		if (list_v[i] == min) {
			cout << i << " ";
		}
	}

	cout << endl;
}

void zeroDegree(Graph g) {
	cout << "Cac dinh co lap: ";

	int degree = 0;
	for (int i = 0; i < g.vertex; i++) {
		for (int j = 0; j < g.vertex; j++) {
			degree += g.a[i][j];
		}
		if (degree == 0) {
			cout << i << " ";
		}
	}

	cout << endl;
}

void leafVertex(Graph g) {
	cout << "Cac dinh treo: ";

	int degree = 0;
	for (int i = 0; i < g.vertex; i++) {
		for (int j = 0; j < g.vertex; j++) {
			degree += g.a[i][j];
		}
		if (degree == 1) {
			cout << i << " ";
		}
	}

	cout << endl;
}

void evenVertex(Graph g) {
	int list_v[MAX];
	int number = 0, count = 0;

	for (int i = 0; i < g.vertex; i++) {
		count = 0;
		for (int j = 0; j < g.vertex; j++) {
			count += g.a[i][j];
		}
		if (count % 2 == 0) {
			number++;
		}
		list_v[i + 1] = count;
	}

	cout << "So luong cac dinh bac chan: " << number << endl;
	cout << "Cac dinh bac chan: ";
	for (int i = 0; i <= g.vertex; i++) {
		if (list_v[i] % 2 == 0 && i != 0) {
			cout << i << " ";
		}
	}

	cout << endl;
}

void oddVertex(Graph g) {
	int list_v[MAX];
	int number = 0, count = 0;

	for (int i = 0; i < g.vertex; i++) {
		count = 0;
		for (int j = 0; j < g.vertex; j++) {
			count += g.a[i][j];
		}
		if (count % 2 == 1) {
			number++;
		}
		list_v[i + 1] = count;
	}

	cout << "So luong cac dinh bac le: " << number << endl;
	cout << "Cac dinh bac le: ";
	for (int i = 0; i <= g.vertex; i++) {
		if (list_v[i] % 2 == 1 && i != 0) {
			cout << i << " ";
		}
	}

	cout << endl;
}

int main() {
	Graph g;
	g.readFile("InforGraph.txt");
	cout << g << endl;
	
	cout << "So dinh: " << g.vertex << endl;
	cout << "So canh: " << checkCanh(g) << endl;
	maxDegree(g); // cac dinh co bac lon nhat
	minDegree(g); // cac dinh co bac nho nhat
	zeroDegree(g); // cac dinh co lap
	leafVertex(g); // cac dinh treo
	evenVertex(g); // so luong va danh sach cac dinh bac chan
	oddVertex(g); // so luong va danh sach cac dinh bac le
	
	return 0;
}