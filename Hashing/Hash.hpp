#pragma once
#ifndef HASH_HPP
# define HASH_HPP

# include <iostream>

using namespace std;

class AHash {
	public:
		AHash(int n = 20) {
			stash = new int[n];
			for (int i = 0; i < n; i++)
				stash[i] = -1;
			size = n;
			loading_factor = 0;
			num_elements = 0;
		}
		virtual ~AHash() {};
		int *hash() { return stash; }

		void insert(int key) {
			if (loading_factor >= 0.5) {
				cout << "Hash map is full" << endl;
				return;
			}
			int hashed_value = hashing_function(key);
			if (stash[hashed_value] == -1)
				stash[hashed_value] = key;
			else
				resolve_collision(key, hashed_value);
			loading_factor = (++num_elements) / (float) size;
		}

		void remove(int key) {
			int hashed_value = hashing_function(key);
			removal_method(key, hashed_value);
			loading_factor = (--num_elements) / (float) size;
		}

		int operator[](int key) {
			return search(key);
		}

		void display() {
			for (int i = 0; i < size; i++) {
				cout << i << ":  ";
				if (stash[i] != -1)
					cout << stash[i] << endl;
				else
					cout << endl;
			}
		}

	protected:
		int *stash;
		int size;
		int num_elements;
		float loading_factor;
		virtual int search(int key) = 0;
		virtual int hashing_function(int key) = 0;
		virtual void resolve_collision(int key, int index) = 0;
		virtual void removal_method(int key, int index) = 0;
};


#endif
