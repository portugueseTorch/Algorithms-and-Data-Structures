#include <iostream>

class Array {
	public:
		Array();
		Array(int size);
		~Array();

		int		getSize() const { return _size; }
		int		getLength() const { return _length; }
		int		*getArray() const { return _arr; }

		void	display();
		void	append(int);
		void	insert(int, int);
		void	del(int);
		int		linearSearch(int);
		int		binarySearch(int);
		int		get(int);
		void	set(int, int);
		int		max();
		int		min();
		int		sum();
		int		average();
		void	reverse();
		void	insertSort(int);
		bool	isSorted();
		void	rearrange();
		void	sumPair(int sum);
		void	sumPairSorted(int sum);
		Array	merge(Array &other);
		Array	unionize(Array &other);
		Array	intersection(Array &other);
		Array	difference(Array &other);
		Array	findMissingElements();
		Array	hashFindMissingElements();
		Array	findDuplicates();
		int		&operator[](int);

	private:
		int _size;
		int _length;
		int *_arr;

		void expand();
};

int &Array::operator[] (int i) {
	return _arr[i];
}

Array::Array() {
	_size = 10;
	_length = 0;
	_arr = new int[_size];
	for (int i = 0; i < _size; i++)
		_arr[i] = 0;
}

Array::Array(int size) {
	_size = size;
	_length = 0;
	_arr = new int[_size];
	for (int i = 0; i < _size; i++)
		_arr[i] = 0;
}

Array::~Array() {
	delete[] _arr;
}

void Array::expand() {
	int	new_capacity = _size * (1 + 0.3) + 1;
	int i = 0;

	int *new_arr = new int[new_capacity];
	if (_arr) {
		for (; i < _length; i++)
			new_arr[i] = _arr[i];
		_size = new_capacity;
		delete[] _arr;
	}
	_arr = new_arr;
}

void Array::display() {
	if (!_arr) return;
	for (int i = 0; i < _length; i++)
		std::cout << _arr[i] << " ";
	std::cout << std::endl;
}

void Array::append(int key) {
	if (!_arr) return ;

	// Check if we need to relocate the array
	if (_length == _size) {
		int	new_capacity = _size * (1 + 0.3) + 1;
		int i = 0;

		int *new_arr = new int[new_capacity];
		for (; i < _length; i++)
			new_arr[i] = _arr[i];
		new_arr[i] = key;
		_size = new_capacity;
		delete[] _arr;
		_arr = new_arr;
	} else {
		_arr[_length] = key;
	}
	_length++;
}

void Array::insert(int index, int key) {
	if (!_arr || index >= _size) return ;

	// Check if we need to allocate a new array
	if (_length == _size) {
		int	new_capacity = _size * (1 + 0.3) + 1;
		int *new_arr = new int[new_capacity];

		for (int i = 0, j = 0; i < _size; i++, j++) {
			if (i == index) {
				new_arr[j] = key;
				j++;
			}
			new_arr[j] = _arr[i];
		}
		_size = new_capacity;
		delete[] _arr;
		_arr = new_arr;
		_length++;
	} else {
		for (int i = _length; i > index; i--)
			_arr[i] = _arr[i - 1];
		_arr[index] = key;
		_length++;
	}
}

void Array::del(int index) {
	if (index >= _length) return;
	for (int i = index; i < _length - 1; i++)
		_arr[i] = _arr[i + 1];
	_length--;
}

// Simple linear search
int Array::linearSearch(int key) {
	for (int i = 0; i < _length; i++) {
		if (_arr[i] == key)
			return i;
	}
	return -1;
}

// Iterative Binary Search
int Array::binarySearch(int key) {
	int mid, l = 0, h = _length - 1;
	int comp = 0;

	while (l <= h) {
		comp++;
		mid = (l + h) / 2;
		if (_arr[mid] == key) {
			return mid;
		}
		else if (_arr[mid] < key)
			l = mid + 1;
		else if (_arr[mid] > key)
			h = mid - 1;
	}
	return -1;
}

int Array::get(int index) {
	if (index >= 0 && index < _length)
		return _arr[index];
	return -1;
}

void Array::set(int index, int new_value) {
	if (index >= 0 && index < _length)
		_arr[index] = new_value;
}

int Array::max() {
	if (!_arr) return -1;
	int max = _arr[0];
	for (int i = 1; i < _length; i++) {
		if (_arr[i] > max)
			max = _arr[i];
	}
	return max;
}

int Array::min() {
	if (!_arr) return -1;
	int min = _arr[0];
	for (int i = 1; i < _length; i++) {
		if (_arr[i] < min)
			min = _arr[i];
	}
	return min;
}

int Array::sum() {
	int sum = 0;
	for (int i = 0; i < _length; i++)
		sum += _arr[i];
	return sum;
}

int Array::average() {
	int sum = 0;
	for (int i = 0; i < _length; i++)
		sum += _arr[i];
	return sum / _length;
}

void Array::reverse() {
	int tmp;
	for (int i = 0, j = _length - 1; i < j; i++, j--) {
		tmp = _arr[i];
		_arr[i] = _arr[j];
		_arr[j] = tmp;
	}
}

void Array::insertSort(int key) {
	if (!isSorted()) return;
	if (_length == _size) {
		expand();
	}
	int i = _length - 1;
	for (; _arr[i] > key; i--)
		_arr[i + 1] = _arr[i];
	_arr[i + 1] = key;
	_length++;
}

bool Array::isSorted() {
	for (int i = 0; i < _length - 2; i++)
		if (_arr[i] > _arr[i + 1]) return false;
	return true;
}

void Array::rearrange() {
	int i = 0, j = _length - 1;
	while (i < j) {
		while (_arr[i] < 0)
			i++;
		while (_arr[j] >= 0)
			j--;
		if (i < j) {
			int tmp = _arr[i];
			_arr[i] = _arr[j];
			_arr[j] = tmp;
		}
	}
}

Array Array::merge(Array &other) {
	int i = 0, j = 0, k = 0;
	Array new_arr;

	new_arr._length = _length + other.getLength();
	new_arr._size = _size + other.getSize();
	new_arr._arr = new int[new_arr._size];

	while (i < _length && j < other.getLength()) {
		if (_arr[i] < other.get(j))
			new_arr._arr[k++] = _arr[i++];
		else
			new_arr._arr[k++] = other.get(j++);
	}
	for (; i < _length; i++)
		new_arr._arr[k++] = _arr[i];

	for (; j < other.getLength(); j++)
		new_arr._arr[k++] = other.get(j);

	return new_arr;
}

Array Array::unionize(Array &other) {
	int i = 0, j = 0, k = 0;
	Array new_arr;

	new_arr._size = _size + other.getSize();
	new_arr._length = 0;
	new_arr._arr = new int[new_arr._size];

	while (i < _length && j < other.getLength()) {
		if (_arr[i] < other.get(j))
			new_arr._arr[k++] = _arr[i++];
		else if (_arr[i] > other.get(j))
			new_arr._arr[k++] = other.get(j++);
		else {
			new_arr._arr[k++] = _arr[i++];
			j++;
		}
	}
	for (; i < _length; i++)
		new_arr._arr[k++] = _arr[i];

	for (; j < other.getLength(); j++)
		new_arr._arr[k++] = other.get(j);

	new_arr._length = k;

	return new_arr;
}

Array Array::intersection(Array &other) {
	int i = 0, j = 0, k = 0;
	Array new_arr;

	new_arr._size = _size + other.getSize();
	new_arr._length = 0;
	new_arr._arr = new int[new_arr._size];

	while (i < _length && j < other.getLength()) {
		if (_arr[i] < other.get(j))
			i++;
		else if (_arr[i] > other.get(j))
			j++;
		else {
			new_arr._arr[k++] = _arr[i++];
			j++;
		}
	}

	new_arr._length = k;

	return new_arr;
}

Array Array::difference(Array &other) {
	int i = 0, j = 0, k = 0;
	Array new_arr;

	new_arr._size = _size + other.getSize();
	new_arr._length = 0;
	new_arr._arr = new int[new_arr._size];

	while (i < _length && j < other.getLength()) {
		if (_arr[i] < other.get(j))
			new_arr._arr[k++] = _arr[i++];
		else if (_arr[i] > other.get(j))
			j++;
		else {
			i++;
			j++;
		}
	}

	new_arr._length = k;

	return new_arr;
}

Array Array::findMissingElements() {
	Array missing;
	if (_length < 2)
		return missing;

	int diff = _arr[0] - 0;
	for (int i = 1; i < _length; i++) {
		std::cout << "Diff is " << _arr[i] - i << std::endl;
		if (_arr[i] - i != diff) {
			while (diff < _arr[i] - i) {
				std::cout << "Missing element " << i + diff << std::endl;
				missing.append(i + diff++);
			}
			diff = _arr[i] - i;
		}
	}
	return missing;
}

Array Array::hashFindMissingElements() {
	Array hash(this->max() + 1);
	Array missing;

	for (int i = 0; i < _length; i++)
		hash._arr[_arr[i]]++;
	for (int i = this->min(); i < hash._size; i++) {
		if (hash._arr[i] == 0) {
			std::cout << "Missing element " << i << std::endl;
			missing.append(i);
		}
	}
	return missing;
}


Array Array::findDuplicates() {
	Array hash(this->max() + 1);
	Array duplicates;

	for (int i = 0; i < _length; i++) {
		if (hash[_arr[i]] == 0) {
			hash[_arr[i]]++;
		} else if (hash[_arr[i]] == 1) {
			std::cout << "Duplicate found: " << _arr[i] << std::endl;
			duplicates.append(_arr[i]);
			hash[_arr[i]]++;
		}
	}
	return duplicates;
}

void Array::sumPair(int sum) {
	Array hash(this->max() + 1);
	int diff;

	for (int i = 0; i < _length; i++) {
		diff = sum - _arr[i];
		if (hash[diff] == 0)
			hash[_arr[i]] = i + 1;
		else {
			std::cout << "Found mathcing sum: " << _arr[i] << " (" << i << ") and " << diff << " (" << hash[diff] - 1 << ")" << std::endl;
		}
	}
}

void Array::sumPairSorted(int sum) {
	for (int i = 0, j = _length - 1; i < j; ) {
		if (_arr[i] + _arr[j] > sum)
			j--;
		else if (_arr[i] + _arr[j] < sum)
			i++;
		else {
			std::cout << "Found matching sum: " << _arr[i] << " and " << sum - _arr[i] << std::endl;
			i++;
			j--;
		}
	}
}

int main() {
	{
		// Array a(5);
		// Array b(7);

		// std::cout << "Array A:\t";
		// a.append(-1);
		// a.append(3);
		// a.append(6);
		// a.append(7);
		// a.append(12);
		// a.display();

		// std::cout << "Array B:\t";
		// b.append(-4);
		// b.append(0);
		// b.append(2);
		// b.append(5);
		// b.append(10);
		// b.append(12);
		// b.append(18);
		// b.display();

		// std::cout << "\n#############################################\n" << std::endl;

		// std::cout << "Average A:\t" << a.average() << std::endl;
		// std::cout << "Average B:\t" << b.average() << std::endl;

		// std::cout << "\n#############################################\n" << std::endl;

		// std::cout << "3 in A:\t\t" << a.binarySearch(3) << std::endl;
		// std::cout << "10 in B:\t" << b.binarySearch(10) << std::endl;

		// std::cout << "\n#############################################\n" << std::endl;

		// std::cout << "Deleting index 2 from A\n  Before:\t";
		// a.display();
		// a.del(2);
		// std::cout << "  After:\t";
		// a.display();

		// std::cout << "\nDeleting index 2 from B\n  Before:\t";
		// b.display();
		// b.del(2);
		// std::cout << "  After:\t";
		// b.display();

		// std::cout << "\n#############################################\n" << std::endl;

		// std::cout << "Array A:\t";
		// a.display();
		// std::cout << "Array B:\t";
		// b.display();

		// std::cout << "\nDiff a - b:\t";
		// Array diffa = a.difference(b);
		// diffa.display();

		// std::cout << "Diff b - a:\t";
		// Array diffb = b.difference(a);
		// diffb.display();

		// Array array(11);
		// array.append(6);
		// array.append(7);
		// array.append(8);
		// array.append(9);
		// array.append(11);
		// array.append(12);
		// array.append(15);
		// array.append(16);
		// array.append(17);
		// array.append(18);
		// array.append(19);
		// array.display();

		// Array missing = array.hashFindMissingElements();
		// missing.display();
	}

	Array array(11);
	array.append(5);
	array.append(7);
	array.append(9);
	array.append(11);
	array.append(12);
	array.append(15);
	array.append(17);
	array.append(18);
	array.display();

	array.sumPairSorted(20);

	return 0;
}
