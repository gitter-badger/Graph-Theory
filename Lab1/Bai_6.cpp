#include <iostream>
#include <fstream>

using namespace std;

#define MAX 100

struct Node {
	int value;
	Node* next;

	Node() {
		value = 0;
		next = NULL;
	}
};

class Graph {
public:
	int vertex;
	Node* a[MAX];
public:
	Graph() {
		// pass
	}

	~Graph() {
		for (int i = 0; i < this->vertex; i++) {
			while (this->a[i] != NULL) {
				Node* temp = this->a[i];
				this->a[i] = this->a[i]->next;
				delete temp;
			}
		}
	}

	int readFile(char*);
};

int Graph::readFile(char* filename) {
	fstream f(filename, ios::in);
	char value;
	f.get(value);
	this->vertex = value - '0';
	f.get(value); // pass through the new line behind g.vertex
	f.get(value);

	for (int i = 0; i < this->vertex; i++) {
		this->a[i] = new Node();
		Node* temp = this->a[i];
		while (!f.eof()) {
			if (value == ' ') {
				f.get(value);
			}
			else if (value == '\n') {
				f.get(value);
				break;
			}
			else {
				temp->value = value - '0';
				f.get(value);
				char ctemp = value;
				if (ctemp != '\n') {
					temp->next = new Node();
					temp = temp->next;
				}
			}
		}
	}

	f.close();
	return 1;
}

int printMatrix(int matrix[MAX][MAX], Graph& g) {
	for (int i = 0; i < g.vertex; i++) {
		Node* temp = g.a[i];
		while (temp != NULL) {
			if (temp->value == 0 && i + 1 == g.vertex) {
				break;
			}
			matrix[i][temp->value - 1] = 1;
			temp = temp->next;
		}
	}
	return 1;
}

int main() {
	Graph g;
	int matrix[MAX][MAX];
	g.readFile("bai_6_input.txt");
	cout << g.vertex << endl;
	
	for (int i = 0; i < g.vertex; i++) {
		for (int j = 0; j < g.vertex; j++) {
			matrix[i][j] = 0;
		}
	}
	
	printMatrix(matrix, g);

	for (int i = 0; i < g.vertex; i++) {
		for (int j = 0; j < g.vertex; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}