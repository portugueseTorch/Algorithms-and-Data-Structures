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
		Queue() {
			_front = NULL;
			_rear = NULL;
		}
		~Queue() {
			Node *tmp = NULL;
			for (Node *p = _front; p; p = tmp) {
				tmp = p->next;
				delete p;
			}
		}
		void enqueue(int n) {
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
		int dequeue() {
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
		bool empty() { return _front == NULL; }
		void display() {
			for (Node *p = _front; p; p = p->next)
				cout << p->data << " ";
			cout << endl;
		}

	private:
		Node	*_front;
		Node	*_rear;
};

class PriorityQueue {
	public:
		PriorityQueue(int n);
		~PriorityQueue();
		void	enqueue(int, int);
		int		dequeue();
		void	display();

	private:
		int		_size;
		Queue	*queues;
};

PriorityQueue::PriorityQueue(int n) {
	_size = n;
	queues = new Queue[n];
}

PriorityQueue::~PriorityQueue() {
	delete[] queues;
}

void	PriorityQueue::enqueue(int x, int priority) {
	if (priority > _size) {
		cout << "Invalid priority: " << priority << endl;
		return ;
	}
	queues[priority - 1].enqueue(x);
}

int	PriorityQueue::dequeue() {
	int	i;
	for (i = 0; i < _size && queues[i].empty(); i++);
	if (i == _size) {
		cout << "All queues are empty" << endl;
		return INT16_MIN;
	} else
		return queues[i].dequeue();
}

void PriorityQueue::display() {
	for (int i = 0; i < _size; i++)
		queues[i].display();
}

int main() {
	PriorityQueue pq(3);

	pq.enqueue(4, 1);
	pq.enqueue(5, 1);
	pq.enqueue(6, 1);
	pq.enqueue(2, 2);
	pq.enqueue(3, 2);
	pq.enqueue(0, 3);
	pq.enqueue(1, 3);

	pq.display();

	cout << pq.dequeue() << endl;
	cout << pq.dequeue() << endl;
	cout << pq.dequeue() << endl;
	cout << pq.dequeue() << endl;
	cout << pq.dequeue() << endl;
	cout << pq.dequeue() << endl;
	cout << pq.dequeue() << endl;

	return 0;
}
