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

void shellSort(vector<int> &vec) {
	for (int pass = vec.size() / 2; pass > 0; pass /= 2) {
		for (int i = 0; i + pass < vec.size(); i++) {
			cout << "Comparing " << vec[i] << " and " << vec[i + pass] << endl;
			int j = i;
			do {
				if (vec[j + pass] < vec[j])
					swap(vec[j + pass], vec[j]);
				j -= pass;
			} while (j >= 0);
		}
		display(vec);
	}
}

int main() {
	vector<int> vec = {3, 7, 9, 10, 6, 5, 12, 4, 11, 2};

	cout << "Unsorted:  "; display(vec);
	shellSort(vec);
	cout << "Sorted:    "; display(vec);
}
