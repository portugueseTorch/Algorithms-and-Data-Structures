#include <iostream>
#include <math.h>

using namespace std;

typedef struct Element {
	int coef;
	int pow;
}	Element;

class Polynomial {
	public:
		Polynomial();
		Polynomial(int n);
		~Polynomial();
		Element	*elements;

		void display();
		int solve(int x);

		Polynomial *operator+(Polynomial &other);

	private:
		int _n;
};

Polynomial::Polynomial() {}

Polynomial::Polynomial(int n) {
	if (n < 1) {
		cout << "Invalid Polynomial" << endl;
		return ;
	}
	_n = n;
	elements = new Element[_n];

	cout << "Enter the " << n << " elements\n";
	for (int i = 0; i < n; i++) {
		int coef, pow;
		cout << "Coeff: "; cin >> coef;
		cout << "Power: "; cin >> pow;
		elements[i].coef = coef;
		elements[i].pow = pow;
	}
}

Polynomial::~Polynomial() {
	if (elements)
		delete[] elements;
}

void Polynomial::display() {
	for (int i = 0; i < _n; i++) {
		cout << "[ " << elements[i].coef << ", " << elements[i].pow << " ]";
	}
	cout << endl;
}

int Polynomial::solve(int x) {
	int sum = 0;
	for (int i = 0; i < _n; i++)
		sum += elements[i].coef * pow(x, elements[i].pow);
	return sum;
}

Polynomial *Polynomial::operator+(Polynomial &other) {
	Polynomial *res;
	int i = 0, j = 0, k = 0;

	res = new Polynomial;
	res->elements = new Element[this->_n + other._n];

	while (i < this->_n && j < other._n) {
		if (this->elements[i].pow > other.elements[j].pow)
			res->elements[k++] = this->elements[i++];
		else if (this->elements[i].pow < other.elements[j].pow)
			res->elements[k++] = other.elements[j++];
		else {
			res->elements[k].pow = this->elements[i].pow;
			res->elements[k++].coef = this->elements[i++].coef + other.elements[j++].coef;
		}
	}

	for (; i < this->_n; i++) res->elements[k++] = this->elements[i];
	for (; j < other._n; j++) res->elements[k++] = other.elements[j];
	res->_n = k;

	return res;
}

int main() {
	Polynomial poly(3);
	Polynomial other(2);
	poly.display();
	cout << "Result: " << poly.solve(0) << endl;
	Polynomial *sum = poly + other;
	sum->display();
	cout << sum->solve(1) << endl;
	free(sum);
	return 0;
}
