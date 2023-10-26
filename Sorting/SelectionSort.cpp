#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void selectionSort(vector<int> &vec) {
	for (int i = 0; i < vec.size() - 1; i++) {
		int min_index = i;
		for (int j = i; j < vec.size(); j++)
			if (vec[j] < vec[min_index]) min_index = j;
		swap(vec[i], vec[min_index]);
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
	selectionSort(vec);
	cout << "Sorted:    "; display(vec);
}
