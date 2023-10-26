#include "Heap.hpp"

Heap::Heap() {
	size = 0;
}

Heap::Heap(vector<int> &vec) {
	size = 0;
	for (auto it = vec.begin(); it != vec.end(); it++)
		insert(*it);
}

void Heap::insert(int key) {
	int i = size;
	data.push_back(key);
	while (i > 0 && data[i % 2 == 0 ? (i / 2) - 1 : i / 2] < key) {
		data[i] = data[i % 2 == 0 ? (i / 2) - 1 : i / 2];
		i = i % 2 == 0 ? (i / 2) - 1 : i / 2;
	}
	data[i] = key;
	size++;
}

void swap(int &a, int &b) {
	if (!a || !b) return;

	int tmp = a;
	a = b;
	b = tmp;
}

int Heap::remove() {
	if (size == 0) return -1;
	int popped = data.at(0);

	// Move last element to the root and decrease size
	data[0] = data[size - 1];
	data.at(size - 1) = popped;
	size--;

	int i = 0;
	int j = 2 * i + 1;
	while (j < size) {
		if (j + 1 < size && data[j + 1] > data[j])
			j++;
		if (data[i] < data[j]) swap(data[i], data[j]);
		else break;
		i = j;
		j = 2 * i + 1;
	}
	return popped;
}

void Heap::display() {
	for (int i = 0; i < size; i++) {
		cout << data.at(i);
		if (i < size - 1) cout << ", ";
	}
	cout << endl;
}

vector<int> heapSort(vector<int> &vec) {
	Heap hp(vec);

	for (int i = 0; i < vec.size(); i++)
		hp.remove();
	return hp.data;
}

void heapify(vector<int> &vec) {
	for (int i = (vec.size() / 2) - 1; i >= 0; i--) {
		int j = 2 * i + 1, k = i;
		while (j < vec.size()) {
			// Check larger child
			if (j + 1 < vec.size() && vec[j + 1] > vec[j])
				j++;

			// If child is greater than parent, swap
			if (vec[k] < vec[j]) swap(vec[k], vec[j]);
			else break;

			// Update j and k
			k = j;
			j = 2 * k + 1;
		}
	}
}

void display(vector<int> &vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec.at(i);
		if (i < vec.size() - 1) cout << ", ";
	}
	cout << endl;
}

int main() {
	vector<int> vec = {10, 8, 40, 15, 5, 20, 18, 7, 30, 3, 1};
	Heap hp(vec);

	cout << "Regular Heap: ";
	hp.display();
	// hp.remove();
	// hp.display();

	cout << "Heapsorted: ";
	vector<int> sorted = heapSort(vec);
	display(sorted);

	cout << "Heapified: ";
	heapify(vec);
	display(vec);

	return 0;
}
