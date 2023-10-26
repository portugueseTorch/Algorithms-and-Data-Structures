#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void bubbleSort(vector<int> &vec) {
	// Flag checking if the vector is already sorted after the first pass O(n)
	int sorted = 1;

	for (int i = 0; i < vec.size() - 1; i++) {
		for (int j = 0; j < vec.size() - i - 1; j++) {
			if (vec[j] > vec[j + 1]) {
				swap(vec[j], vec[j + 1]);
				sorted = 0;
			}
		}
		if (sorted)
			break;
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
	bubbleSort(vec);
	cout << "Sorted:    "; display(vec);
}
