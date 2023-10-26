#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void insertionSort(vector<int> &vec) {
	for (int i = 1; i < vec.size(); i++) {
		int x = vec[i], j = i - 1;
		while (j >= 0 && vec[j] > x) {
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = x;
	}
}

void display(vector<int> &vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec.at(i);
		if (i + 1 < vec.size())
			cout << ", ";
	}
	cout << endl;
}

int main() {
	vector<int> vec = {3, 7, 9, 10, 6, 5, 12, 4, 11, 2};

	cout << "Unsorted:  "; display(vec);
	insertionSort(vec);
	cout << "Sorted:    "; display(vec);
}
