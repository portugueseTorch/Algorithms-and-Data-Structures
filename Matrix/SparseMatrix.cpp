#include <iostream>
#include <exception>

using namespace std;

typedef struct Element {
	int i;
	int j;
	int x;
}	Element;

class SparseMatrix {
	public:
		SparseMatrix();
		SparseMatrix(int m, int n, int non_zero);
		~SparseMatrix();
		Element	*elements;

		static SparseMatrix add(SparseMatrix &first, SparseMatrix &second);


		int	getM() const { return _m; }
		int	getN() const { return _n; }
		int	getNonZero() const { return _non_zero; }
		int getPrintableElement(int i, int j);

		void setElement(int index, int i, int j, int x);
		void create(int m, int n, int non_zero);
		void display();

		class InvalidInputException: public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Invalid input for sparse matrix";
				}
		};

		class InvalidAdditionOperationException: public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Invalid addition of sparse matrixes";
				}
		};


	private:
		int		_m;
		int		_n;
		int		_non_zero;
};

SparseMatrix::SparseMatrix(): _m(-1), _n(-1), _non_zero(-1), elements(NULL) {}

SparseMatrix::SparseMatrix(int m, int n, int non_zero) {
	if (m < 1 || n < 1 || non_zero < 0)
		throw InvalidInputException();
	_m = m;
	_n = n;
	_non_zero = non_zero;
	elements = new Element[non_zero + 1];
	elements[0].i = _m;
	elements[0].j = _n;
	elements[0].x = _non_zero;

	cout << "Insert the " << non_zero << " non-zero elements" << endl;
	for (int i = 1; i <= non_zero; i++) {
		int ei, ej, ex;
		cout << "Element " << i << ":" << endl;
		cout << "  row: "; cin >> ei;
		cout << "  col: "; cin >> ej;
		cout << "  val: "; cin >> ex;
		elements[i].i = ei;
		elements[i].j = ej;
		elements[i].x = ex;
	}
}

SparseMatrix::~SparseMatrix() {
	if (elements)
		delete[] elements;
}

int SparseMatrix::getPrintableElement(int i, int j) {
	for (int it = 1; it <= _non_zero; it++) {
		if (elements[it].i == i && elements[it].j == j)
			return elements[it].x;
	}
	return 0;
}

void SparseMatrix::display() {
	int k = 1;
	cout << "\nRows: " << _m << "\nCols: " << _n << "\nVals: " << elements[0].x << endl;
	if (elements) {
		for (int i = 1; i <=_m; i++) {
			for (int j = 1; j <= _n; j++) {
				if (elements[k].i == i && elements[k].j == j)
					cout << elements[k++].x << " ";
				else
					cout << "0 ";
			}
			cout << endl;
		}
	}
	cout << endl;
}

void SparseMatrix::setElement(int index, int i, int j, int x) {
	elements[index].i = i;
	elements[index].j = j;
	elements[index].x = x;
}

void SparseMatrix::create(int m, int n, int non_zero) {
	_m = m;
	_n = n;
	_non_zero = non_zero;
}

SparseMatrix SparseMatrix::add(SparseMatrix &first, SparseMatrix &second) {
	int i = 1, j = 1, num = 0;
	SparseMatrix res;

	if (first.getM() != second.getM() || first.getN() != second.getN())
		throw InvalidAdditionOperationException();

	// Create the resulting matrix
	res.create(first.getM(), first.getN(), first.getNonZero() + second.getNonZero());
	res.elements = new Element[res.getNonZero() + 1];
	res.elements[0].i = res.getM();
	res.elements[0].j = res.getN();

	while (i <= first.elements[0].x || j <= second.elements[0].x) {
		if (first.elements[i].i < second.elements[j].i) {
			res.elements[num + 1].i = first.elements[i].i;
			res.elements[num + 1].j = first.elements[i].j;
			res.elements[num + 1].x = first.elements[i].x;
			num++;
			i++;
		} else if (first.elements[i].i > second.elements[j].i) {
			res.elements[num + 1].i = second.elements[j].i;
			res.elements[num + 1].j = second.elements[j].j;
			res.elements[num + 1].x = second.elements[j].x;
			num++;
			j++;
		} else {
			if (first.elements[i].j < second.elements[j].j) {
				res.elements[num + 1].i = first.elements[i].i;
				res.elements[num + 1].j = first.elements[i].j;
				res.elements[num + 1].x = first.elements[i].x;
				num++;
				i++;
			} else if (first.elements[i].j > second.elements[j].j) {
				res.elements[num + 1].i = second.elements[j].i;
				res.elements[num + 1].j = second.elements[j].j;
				res.elements[num + 1].x = second.elements[j].x;
				num++;
				j++;
			} else {
				res.elements[num + 1].i = first.elements[i].i;
				res.elements[num + 1].j = first.elements[i].j;
				res.elements[num + 1].x = first.elements[i].x + second.elements[j].x;
				num++;
				i++;
				j++;
			}
		}
	}
	cout << num << endl;
	res.elements[0].x = num;
	return res;
}

int main() {
	try {
		SparseMatrix sp = SparseMatrix(5, 5, 5);
		SparseMatrix other = SparseMatrix(5, 5, 5);
		SparseMatrix sum = SparseMatrix::add(sp, other);
		sum.display();
	} catch (exception &e) {
		cout << "Error:\t" << e.what() << endl;
	}
	return 0;
}
