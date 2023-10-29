#pragma once
#ifndef HASH_HPP
# define HASH_HPP

# include <iostream>

using namespace std;

class Hash {
	public:
		Hash(int n) {
			stash = new int[n];
			for (int i = 0; i < n; i++) stash[i] = -1;
			size = n;
		}
		~Hash() { delete stash; }
		int *hash() { return stash; }

		void insert(int key) {
			int hashed_value = hashing_function(key);
			if (stash[hashed_value] == -1)
				insertion_method(key, hashed_value);
			else
				resolve_collision(key, hashed_value);
		}

		void remove(int key) {
			int hashed_value = hashing_function(key);
			removal_method(key, hashed_value);
		}

		int operator[](int key) {
			int hashed_value = hashing_function(key);
			return search(hashed_value);
		}

		void display() {
			for (int i = 0; i < size; i++) {
				if (stash[i] != -1)
					cout << i << ":  " << stash[i] << endl;
			}
		}

	private:
		int *stash;
		int size;
		virtual int search(int key) = 0;
		virtual int hashing_function(int key) = 0;
		virtual void resolve_collision(int key, int index) = 0;
		virtual void insertion_method(int key, int index) = 0;
		virtual void removal_method(int key, int index) = 0;
};


#endif
