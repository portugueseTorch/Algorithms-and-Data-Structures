#include <iostream>
#include <vector>
#include <list>
#include <math.h>

using namespace std;

void display(vector<int> &vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec.at(i);
		if (i + 1 < vec.size())
			cout << ", ";
	}
	cout << endl;
}

int max_digits(vector<int> &vec) {
	int max = vec.at(0);
	for (int n : vec) {
		if (n > max)
			max = n;
	}

	int digits = 0;
	do {
		++digits;
		max /= 10;
	} while (max != 0);
	return digits;
}

void radixSort(vector<int> &vec) {
	list<int> *bin = new list<int>[10];

	for (int pass = 0; pass < max_digits(vec); pass++) {
		for (int num : vec) {
			int d = (int) (num / pow(10, pass)) % 10;
			bin[d].push_back(num);
		}

		vec.clear();
		for (int i = 0; i < 10; i++) {
			for (list<int>::iterator it = bin[i].begin(); it != bin[i].end();) {
				vec.push_back(*it++);
				bin[i].pop_front();
			}
		}
	}
}

int main() {
	vector<int> vec = {3, 7, 9, 10, 6, 5, 12, 4, 11, 2};

	cout << "Unsorted:  "; display(vec);
	radixSort(vec);
	cout << "Sorted:    "; display(vec);
}
