#include <iostream>

class LowerTri {
	public:
		LowerTri();
		LowerTri(int n);
		~LowerTri() { delete[] _arr; }

		void	set(int i, int j, int key);
		int		get(int i, int j);
		void	display();

	private:
		int *_arr;
		int _n;
};

LowerTri::LowerTri() {
	_n = 2;
	_arr = new int[_n * (_n+1) / 2];
}

LowerTri::LowerTri(int n) {
	_n = n;
	_arr = new int[_n * (_n+1) / 2];
}

void LowerTri::set(int i, int j, int key) {
	if (i >= j)
		_arr[i * (i - 1) / 2 + j - 1] = key;
}

int LowerTri::get(int i, int j) {
	return i >= j ? _arr[i * (i - 1) / 2 + j - 1] : 0;
}

void LowerTri::display() {
	for (int i = 1; i <= _n; i++) {
		for (int j = 1; j <= _n; j++) {
			if (i >= j) std::cout << _arr[i * (i - 1) / 2 + j - 1] << " ";
			else std::cout << "0 ";
		}
		std::cout << std::endl;
	}
}

int main() {
	LowerTri lotr(4);

	lotr.set(1, 1, 1);
	lotr.set(2, 1, 2);
	lotr.set(3, 1, 3);
	lotr.set(4, 1, 4);
	lotr.set(2, 2, 5);
	lotr.set(3, 2, 6);
	lotr.set(4, 2, 7);
	lotr.set(3, 3, 8);
	lotr.set(4, 3, 9);
	lotr.set(4, 4, 10);

	lotr.display();

}
