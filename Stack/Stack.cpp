#include <iostream>
#include <exception>
#include <math.h>

using namespace std;

class Node {
	public:
		Node(int x) {
			data = x;
			next = NULL;
		}
		~Node() {}
		int data;
		Node *next;
};

class Stack {
	public:
		Stack(int);
		~Stack();
		void push(int);
		int pop();
		int peek(int);
		int size();
		int top();
		bool full();
		bool empty();

	private:
		int		_size;
		int		_len;
		Node	*_top;
};

Stack::Stack(int n) {
	_size = n;
	_len = 0;
	_top = NULL;
}

Stack::~Stack() {
	Node *p = _top, *q;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}
}

void Stack::push(int x) {
	if (_len == _size) return ;

	Node *new_node = new Node(x);
	new_node->next = _top;
	_top = new_node;
	_len++;
}

int Stack::pop() {
	if (!_top) return -1;

	Node *p = _top;
	int x = p->data;

	_top = _top->next;
	delete p;
	_len--;
	return x;
}

int Stack::peek(int pos) {
	if (!_top) return -1;

	Node *p = _top;
	int x = _top->data;
	for (int i = 0; i < pos; i++) p = p->next;
	return p->data;
}

int Stack::size() {
	return _len;
}

int Stack::top() {
	if (!_top) return -1;
	return _top->data;
}

bool Stack::full() {
	return _len == _size;
}

bool Stack::empty() {
	return !_top;
}

bool balanced_parenthesis(std::string input) {
	int popped;
	Stack stash(20);

	for (int i = 0; input[i]; i++) {
		if (input.at(i) == '(' || input.at(i) == '{' || input.at(i) == '[') {
			stash.push(input.at(i));
		} else if (input.at(i) == ')' || input.at(i) == '}' || input.at(i) == ']') {
			popped = stash.pop();
			if (popped == -1) return false;
			if ((input.at(i) == ')' && popped != '(') || \
				(input.at(i) == '}' && popped != '{') || \
				(input.at(i) == ']' && popped != '['))
				return false;
		}
	}
	return stash.empty() ? true : false;
}

int is_operator(int c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')';
}

int get_precedence(int c, int in_stack) {
	if (c == '+' || c == '-')
		return 1 + in_stack;
	else if (c == '*' || c == '/')
		return 3 + in_stack;
	else if (c == '^')
		return 6 - in_stack;
	else if (c == '(')
		return 7 - (7 * in_stack);
	else if (c == ')')
		return 0;
	return -1;
}

std::string to_postfix(std::string expression) {
	if (!balanced_parenthesis(expression))
		return "invalid expression";

	int i = 0;
	Stack stash(20);
	std::string res = "";

	while (expression[i]) {
		if (!is_operator(expression[i]) && !isblank(expression[i])) {
			res += expression[i++];
		} else if (is_operator(expression[i])) {
			if (get_precedence(expression[i], 0) > get_precedence(stash.top(), 1))
				stash.push(expression[i++]);
			else if (get_precedence(expression[i], 0) < get_precedence(stash.top(), 1)) {
				res += stash.pop();
				i++;
			} else {
				stash.pop();
				i++;
			}
		} else {
			i++;
		}
	}

	while (!stash.empty()) {
		int popped = stash.pop();
		if (popped != '(')
			res += popped;
	}
	return res;
}

int op(int a, int b, int operation) {
	switch (operation)	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	case '^':
		return pow(a, b);
	}
	return -85;
}

int evaluate_postfix(std::string expression) {
	Stack stash(20);
	int res = 0;

	for (int i = 0; expression[i]; i++) {
		if (isdigit(expression[i]))
			stash.push(expression[i]-48);
		else {
			int a, b;
			if (stash.size() < 2) return -85;
			b = stash.pop();
			a = stash.pop();
			stash.push(op(a, b, expression[i]));
		}
	}
	return stash.size() == 1 ? stash.top() : -85;
}

int main(int argc, char **argv) {
	if (argc != 2) return (1);
	std::string exp = to_postfix(argv[1]);
	// Stack st(10);

	cout << "Original expression: " << argv[1] << endl;
	cout << "Postfix expression: " << exp << endl;
	cout << "Solution: " << evaluate_postfix(exp) << endl;
	return 0;
}

