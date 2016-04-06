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
private:
	int vertex;
	Node* a[MAX];
public:
	Graph() {
		// pass
	}

	~Graph() {
		for (int i = 0; i < this->vertex; i++) {
			while (this->a[i]->next) {
				Node* temp = this->a[i];
				this->a[i] = this->a[i]->next;
				delete temp;
			}
		}
	}

	int readFile(char*);
	int writeFile(char*);
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

int Graph::writeFile(char* filename) {
	fstream f(filename, ios::out);
	f << this->vertex << endl;

	for (int i = 0; i < this->vertex; i++) {
		Node* temp = this->a[i];
		while (temp != NULL) {
			if (temp->value == 0 && i + 1 == this->vertex) {
				break;
			}
			f << temp->value << " ";
			temp = temp->next;
		}
		f << endl;
	}
	
	f.close();
	return 1;
}

int main() {
	Graph g;
	g.readFile("bai_2_input.txt");
	g.writeFile("bai_2_output.txt");
	return 0;
}