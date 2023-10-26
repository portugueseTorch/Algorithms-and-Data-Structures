#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int partition(vector<int> &vec, int l, int h) {
	int pivot = vec[h];
	int s, b;
	s = b = l;
	while (s <= h) {
		if (vec[s] <= pivot)
			swap(vec[s++], vec[b++]);
		else
			s++;
	}
	return b - 1;
}

void quickSort(vector<int> &vec, int low, int high) {
	if (low >= high) return;

	int pos = partition(vec, low, high);
	quickSort(vec, low, pos - 1);
	quickSort(vec, pos + 1, high);
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
	quickSort(vec, 0, vec.size() - 1);
	cout << "Sorted:    "; display(vec);
}
