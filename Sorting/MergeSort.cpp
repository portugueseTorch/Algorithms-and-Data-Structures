#include <iostream>
#include <vector>

using namespace std;

void display(vector<int> &vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec.at(i);
		if (i + 1 < vec.size())
			cout << ", ";
	}
	cout << endl;
}

void merge(vector<int> &vec, int l, int mid, int h) {
	vector<int> backup(vec.size());
	int i = l;
	int j = mid + 1;
	int k = i;
	while (i <= mid && j <= h) {
		if (vec[i] < vec[j])
			backup[k++] = vec[i++];
		else
			backup[k++] = vec[j++];
	}
	while (i <= mid) backup[k++] = vec[i++];
	while (j <= h) backup[k++] = vec[j++];
	for (int i = l; i <= h; i++)
		vec[i] = backup[i];
}

void iterativeMergeSort(vector<int> &vec) {
	int p, i;

	for (p = 2; p <= vec.size(); p = p * 2) {
		for (i = 0; i + p -1 < vec.size(); i = i + p)
			merge(vec, i, (i + i + p - 1) / 2, i + p - 1);
	}
	if (p / 2 < vec.size())
		merge(vec, 0, p / 2 - 1, vec.size() - 1);
}

void recursiveMergeSort(vector<int> &vec, int l, int h) {
	if (l >= h) return;
	int mid = (l + h) / 2;
	recursiveMergeSort(vec, l, mid);
	recursiveMergeSort(vec, mid + 1, h);
	merge(vec, l, mid, h);
}

int main() {
	vector<int> vec = {3, 7, 9, 10, 6, 5, 12, 4, 11, 2};

	cout << "Unsorted:  "; display(vec);
	recursiveMergeSort(vec, 0, vec.size() - 1);
	cout << "Sorted:    "; display(vec);
}
