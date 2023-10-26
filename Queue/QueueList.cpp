#include <iostream>

using namespace std;

class Node {
	public:
		Node(int x) { data = x; next = NULL; }
		~Node() {}
		int data;
		Node *next;
};

class Queue {
	public:
		Queue();
		~Queue();
		void	enqueue(int);
		int		dequeue();
		bool	empty();
		void	display();

	private:
		Node	*_front;
		Node	*_rear;
};

Queue::Queue() {
	_front = NULL;
	_rear = NULL;
}

Queue::~Queue() {
	Node *tmp = NULL;
	for (Node *p = _front; p; p = tmp) {
		tmp = p->next;
		delete p;
	}
}

void	Queue::enqueue(int n) {
	Node *new_node = new Node(n);
	if (!new_node) {
		cout << "Queue is full" << endl;
		return ;
	} else {
		if (empty())
			_front = _rear = new_node;
		else {
			_rear->next = new_node;
			_rear = new_node;
		}
	}
}

int	Queue::dequeue() {
	int to_ret = INT16_MIN;
	if (empty())
		cout << "Queue is empty" << endl;
	else {
		Node *tmp;
		tmp = _front;
		to_ret = _front->data;
		_front = _front->next;
		delete tmp;
	}
	return to_ret;
}

bool	Queue::empty() {
	return _front == NULL;
}

void	Queue::display() {
	for (Node *p = _front; p; p = p->next)
		cout << p->data << " ";
	cout << endl;
}

int main() {
	Queue q;
	q.enqueue(3);
	q.enqueue(7);
	q.enqueue(1);
	q.enqueue(8);
	q.enqueue(5);
	q.enqueue(2);
	q.display();

	q.dequeue();
	q.dequeue();
	q.display();

	q.enqueue(3);
	q.enqueue(7);
	q.display();
}
