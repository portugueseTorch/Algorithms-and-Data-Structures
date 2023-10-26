#include <iostream>
#include <assert.h>

using namespace std;

class Queue {
	public:
		Queue(int);
		~Queue();

		void	enqueue(int);
		int		dequeue();
		bool	empty();
		bool	full();
		void	display();

	private:
		int	_size;
		int	_front;
		int	_back;
		int	*_data;
};

Queue::Queue(int n) {
	assert(n > 0);
	_size = n;
	_front = 0;
	_back = 0;
	_data = new int[n];
}

Queue::~Queue() {
	delete[] _data;
}

void	Queue::enqueue(int x) {
	if (full())
		cout << "Queue is full" << endl;
	else {
		_back = (_back + 1) % _size;
		_data[_back] = x;
	}
}

int	Queue::dequeue() {
	int to_ret = -INT16_MIN;
	if (empty())
		cout << "Queue is empty" << endl;
	else {
		_front = (_front + 1) % _size;
		to_ret = _data[_front];
		_data[_front] = 0;
	}
	return to_ret;
}

bool	Queue::empty() {
	return _front == _back;
}

bool	Queue::full() {
	return (_back + 1) % _size == _front;
}

void	Queue::display() {
	int i = _front + 1;
	do {
		cout << _data[i] << " ";
		i = (i + 1) % _size;
	} while (i != (_back + 1) % _size);
	cout << endl;
}

int main() {
	Queue qarr(7);

	qarr.enqueue(3);
	qarr.enqueue(7);
	qarr.enqueue(1);
	qarr.enqueue(8);
	qarr.enqueue(5);
	qarr.enqueue(2);
	qarr.display();

	qarr.dequeue();
	qarr.dequeue();
	qarr.display();

	qarr.enqueue(3);
	qarr.enqueue(7);
	qarr.display();
}
