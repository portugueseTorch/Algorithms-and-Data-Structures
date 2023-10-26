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

int get_max(vector<int> &vec) {
	int max = vec.at(0);
	for (int n : vec) {
		if (n > max)
			max = n;
	}
	return max;
}

void countSort(vector<int> &vec) {
	int max = get_max(vec);
	int *array = new int[max + 1];

	// Initialize array
	for (int i = 0; i < max + 1; i++)
		array[i] = 0;

	for (int i = 0; i < vec.size(); i++)
		array[vec[i]]++;

	int i = 0, j = 0;
	while (i < max + 1) {
		if (array[i] > 0) {
			vec[j++] = i;
			array[i]--;
		} else {
			i++;
		}
	}
}

int main() {
	vector<int> vec = {3, 7, 9, 10, 6, 5, 12, 4, 11, 2};

	cout << "Unsorted:  "; display(vec);
	countSort(vec);
	cout << "Sorted:    "; display(vec);
}
