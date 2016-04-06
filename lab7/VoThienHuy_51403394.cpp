#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 100

struct Edge {
	int v1;
	int v2;
	double w;
	static bool asc(const Edge &e1, const Edge &e2) {
		return e1.w < e2.w;
	}
	static bool desc(const Edge &e1, const Edge &e2) {
		return e1.w > e2.w;
	}
};

class Graph {
private:
	int n;
	int a[MAX][MAX];
	// Kruskal
	int vertex[100];
	std::vector<Edge> Le;
	std::vector<Edge> eT;
	int nVertex;
public:
	Graph() {
		this->n = 0;
	}
	friend istream& operator>>(istream& is, Graph &g);
	friend ostream& operator<<(ostream& is, Graph &g);
	int readFile(char const * filename);
	int writeFile(char const * filename);
	void InitEdge();
	void KruskalAlgorithm();
	void KruskalAlgorithm_Max();
	void SortAscListEdge();
	void SortDescListEdge();
	bool IsCircle(int index);
};

istream& operator>>(istream& is, Graph& g) {
	int temp;
	is >> g.n;
	for (int i = 0; i < g.n; i++) {
		for (int j = 0; j < g.n; j++) {
			g.a[i][j] = 0;
			if (is) {
				is >> temp;
				g.a[i][j] = temp;
			}
		}
	}
	return is;
}

int sum(vector<Edge> eT) {
	int result = 0;
	for (int i = 0; i < eT.size(); i++) {
		result += eT[i].w;
	}
	return result;
}

ostream& operator<<(ostream& os, Graph &g) {
	os << sum(g.eT) << endl;
	for (int i = 0; i < g.eT.size(); i++) {
		if (i + 1 == g.eT.size()) {
			os << "(" << g.eT[i].v1 << "," << g.eT[i].v2 << ")";
		}
		else {
			os << "(" << g.eT[i].v1 << "," << g.eT[i].v2 << "); ";
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
	f << (*this);
	f.close();
	return 1;
}

void Graph::InitEdge() {
	for (int i = 0; i < this->n; i++) {
		for (int j = i; j < this->n; j++) {
			if (j != i && this->a[i][j] != 0) {
				Edge edge;
				edge.v1 = i;
				edge.v2 = j;
				edge.w = this->a[i][j];
				Le.push_back(edge);
			}
		}
	}
}

void Graph::SortAscListEdge() {
	std::sort(this->Le.begin(), this->Le.end(), Edge::asc);
}

void Graph::SortDescListEdge() {
	std::sort(this->Le.begin(), this->Le.end(), Edge::desc);
}

bool Graph::IsCircle(int index) {
	if (vertex[Le[index].v1] == vertex[Le[index].v2]) {
		return true;
	}
	int label_min, label_max;
	if (vertex[Le[index].v1] > vertex[Le[index].v2]) {
		label_min = vertex[Le[index].v2];
		label_max = vertex[Le[index].v1];
	}
	else {
		label_min = vertex[Le[index].v1];
		label_max = vertex[Le[index].v2];
	}
	for (int i = 0; i < nVertex; i++) {
		if (vertex[i] == label_max) {
			vertex[i] = label_min;
		}
	}
	return false;
}

void Graph::KruskalAlgorithm() {
	nVertex = this->n;
	for (int i = 0; i < this->n; i++) {
		vertex[i] = i;
	}
	InitEdge();
	SortAscListEdge();
	int nT = 0;
	Edge eCurr;
	while (eT.size() < nVertex - 1) {
		eCurr = Le[nT];
		if (!IsCircle(nT)) {
			eT.push_back(eCurr);
		}
		nT++;
	}
}

void Graph::KruskalAlgorithm_Max() {
	nVertex = this->n;
	for (int i = 0; i < this->n; i++) {
		vertex[i] = i;
	}
	InitEdge();
	SortDescListEdge();
	int nT = 0;
	Edge eCurr;
	while (eT.size() < nVertex - 1) {
		eCurr = Le[nT];
		if (!IsCircle(nT)) {
			eT.push_back(eCurr);
		}
		nT++;
	}
}

int main() {
	Graph g;
	g.readFile("input.txt");
	//g.KruskalAlgorithm();
	g.KruskalAlgorithm_Max();
	g.writeFile("VoThienHuy_51403394.txt");
	return 0;
}
