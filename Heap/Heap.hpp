#pragma once
#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <vector>

using namespace std;

class Heap {
	public:
		Heap();
		Heap(vector<int> &);

		void insert(int);
		void display();
		int	remove();

		vector<int>	data;
		int			size;
	private:
};

#endif
