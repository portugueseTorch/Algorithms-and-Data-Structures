#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Array
{
	int *a;
	int	length;
	int	size;
}	Array;

void expand(Array *arr) {
	int	new_capacity = arr->size * (1 + 0.3) + 1;
	int i = 0;

	int *new_arr = (int *) malloc(sizeof(int) * new_capacity);
	if (!new_arr) exit(EXIT_FAILURE);
	if (arr->a) {
		for (; i < arr->length; i++)
			new_arr[i] = arr->a[i];
		arr->size = new_capacity;
		free(arr->a);
	}
	arr->a = new_arr;
}

void display(Array *arr) {
	if (!arr) return;
	for (int i = 0; i < arr->length; i++)
		printf("%d ", arr->a[i]);
	printf("\n");
}

void append(Array *arr, int x) {
	if (!arr) return ;

	// Check if we need to relocate the array
	if (arr->length == arr->size) {
		int	new_capacity = arr->size * (1 + 0.3) + 1;
		int i = 0;

		printf("Capacity reached, relocating...\n");
		printf("New capacity: %d\n", new_capacity);
		int *new_arr = (int *) malloc(sizeof(int) * new_capacity);
		if (!new_arr) exit(EXIT_FAILURE);
		for (; i < arr->length; i++)
			new_arr[i] = arr->a[i];
		new_arr[i] = x;
		arr->size = new_capacity;
		free(arr->a);
		arr->a = new_arr;
	} else {
		arr->a[arr->length] = x;
	}
	arr->length++;
}

void insert(Array *arr, int index, int x) {
	if (!arr || index >= arr->size) return ;

	// Check if we need to allocate a new array
	if (arr->length == arr->size) {
		int	new_capacity = arr->size * (1 + 0.3) + 1;
		int *new_arr = (int *) malloc(sizeof(int) * new_capacity);
		if (!new_arr) exit(EXIT_FAILURE);
		printf("Capacity reached, relocating...\n");
		printf("New capacity: %d\n", new_capacity);

		for (int i = 0, j = 0; i < arr->size; i++, j++) {
			if (i == index) {
				new_arr[j] = x;
				j++;
			}
			new_arr[j] = arr->a[i];
		}
		arr->size = new_capacity;
		free(arr->a);
		arr->a = new_arr;
		arr->length++;
	} else {
		for (int i = arr->length; i > index; i--)
			arr->a[i] = arr->a[i - 1];
		arr->a[index] = x;
		arr->length++;
	}
}

void delete(Array *arr, int index) {
	if (index >= arr->length) return;
	for (int i = index; i < arr->length - 1; i++)
		arr->a[i] = arr->a[i + 1];
	arr->length--;
}

// Simple linear search
int linearSearch(Array *arr, int key) {
	for (int i = 0; i < arr->length; i++) {
		if (arr->a[i] == key)
			return i;
	}
	return -1;
}

// Iterative Binary Search
int iterBinarySearch(Array *arr, int l, int h, int key) {
	int mid;
	int comp = 0;

	while (l <= h) {
		comp++;
		mid = (l + h) / 2;
		printf("Low: %d (%d), High: %d (%d), Mid: %d (%d)\n", arr->a[l], l, arr->a[h], h,  arr->a[mid], mid);
		if (arr->a[mid] == key) {
			printf("Found with %d comparisons\n", comp);
			return mid;
		}
		else if (arr->a[mid] < key)
			l = mid + 1;
		else if (arr->a[mid] > key)
			h = mid - 1;
	}
	return -1;
}

// Recursive Binary Search
int recrBinarySearch(Array *arr, int l, int h, int key) {
	if (l > h)
		return -1;
	int mid = (l + h) / 2;
	if (arr->a[mid] == key)
		return mid;
	else if (arr->a[mid] < key)
		return recrBinarySearch(arr, mid + 1, h, key);
	else if (arr->a[mid] > key)
		return recrBinarySearch(arr, l, h - 1, key);
}

int get(Array *arr, int index) {
	if (index >= 0 && index < arr->length)
		return arr->a[index];
	return -1;
}

void set(Array *arr, int index, int new_value) {
	if (index >= 0 && index < arr->length)
		arr->a[index] = new_value;
}

int max(Array *arr) {
	if (!arr->a) return -1;
	int max = arr->a[0];
	for (int i = 1; i < arr->length; i++) {
		if (arr->a[i] > max)
			max = arr->a[i];
	}
	return max;
}

int min(Array *arr) {
	if (!arr->a) return -1;
	int min = arr->a[0];
	for (int i = 1; i < arr->length; i++) {
		if (arr->a[i] < min)
			min = arr->a[i];
	}
	return min;
}

int sum(Array *arr) {
	int sum = 0;
	for (int i = 0; i < arr->length; i++)
		sum += arr->a[i];
	return sum;
}

int average(Array *arr) {
	int sum = 0;
	for (int i = 0; i < arr->length; i++)
		sum += arr->a[i];
	return sum / arr->length;
}

void reverse(Array *arr) {
	int tmp;
	for (int i = 0, j = arr->length - 1; i < j; i++, j--) {
		tmp = arr->a[i];
		arr->a[i] = arr->a[j];
		arr->a[j] = tmp;
	}
}

void insertSort(Array *arr, int key) {
	if (arr->length == arr->size) {
		expand(arr);
	}
	int i = arr->length - 1;
	for (; arr->a[i] > key; i--)
		arr->a[i + 1] = arr->a[i];
	arr->a[i + 1] = key;
	arr->length++;
}

bool isSorted(Array *arr) {
	for (int i = 0; i < arr->length - 2; i++)
		if (arr->a[i] > arr->a[i + 1]) return false;
	return true;
}

void rearrange(Array *arr) {
	int i = 0, j = arr->length - 1;
	while (i < j) {
		while (arr->a[i] < 0)
			i++;
		while (arr->a[j] >= 0)
			j--;
		if (i < j) {
			int tmp = arr->a[i];
			arr->a[i] = arr->a[j];
			arr->a[j] = tmp;
		}
	}
}

Array merge(Array *one, Array *two) {
	int i = 0, j = 0, k = 0;
	Array new_arr;

	new_arr.length = one->length + two->length;
	new_arr.size = one->size + two->size;
	new_arr.a = malloc(sizeof(int) * new_arr.size);

	while (i < one->length && j < two->length) {
		if (one->a[i] < two->a[j])
			new_arr.a[k++] = one->a[i++];
		else
			new_arr.a[k++] = two->a[j++];
	}
	for (; i < one->length; i++)
		new_arr.a[k++] = one->a[i];

	for (; j < two->length; j++)
		new_arr.a[k++] = two->a[j];

	return new_arr;
}

Array new_array(int size) {
	Array array;

	array.length = 0;
	array.size = size;
	array.a = malloc(sizeof(int) * size);

	return array;
}

Array unionize(Array *first, Array *second) {
	int i = 0, j = 0, k = 0;
	Array array;

	array.size = first->size + second->size;
	array.length = 0;
	array.a = malloc(sizeof(int) * array.size);

	while (i < first->length && j < second->length) {
		if (first->a[i] < second->a[j])
			array.a[k++] = first->a[i++];
		else if (first->a[i] > second->a[j])
			array.a[k++] = second->a[j++];
		else {
			array.a[k++] = first->a[i++];
			j++;
		}
	}

	for (; i < first->length; i++)
		array.a[k++] = first->a[i];

	for (; j < second->length; j++)
		array.a[k++] = second->a[j];
	
	array.length = k;

	return array;
}

Array intersection(Array *first, Array *second) {
	int i = 0, j = 0, k = 0;
	Array array;

	array.size = first->size + second->size;
	array.length = 0;
	array.a = malloc(sizeof(int) * array.size);

	while (i < first->length && j < second->length) {
		if (first->a[i] < second->a[j])
			i++;
		else if (first->a[i] > second->a[j])
			j++;
		else {
			array.a[k++] = first->a[i++];
			j++;
		}
	}
	
	array.length = k;

	return array;
}

// 1 32 41 84
// 2 5  10 32 84 92 104

// 1 41
Array difference(Array *first, Array *second) {
	int i = 0, j = 0, k = 0;
	Array array;

	array.size = first->size + second->size;
	array.length = 0;
	array.a = malloc(sizeof(int) * array.size);

	while (i < first->length && j < second->length) {
		if (first->a[i] < second->a[j])
			array.a[k++] = first->a[i++];
		else if (first->a[i] > second->a[j])
			j++;
		else {
			i++;
			j++;
		}
	}
	
	array.length = k;

	return array;
}

int main() {
	// Array	array;
	// int		n;

	// // Create initial array
	// printf("Insert the number of desired numbers:\n");
	// scanf("%d", &array.size);
	// array.length = 0;
	// array.a = (int *) malloc(sizeof(int) * array.size);
	// if (!array.a) return 1;

	// append(&array, -11);
	// append(&array, 18);
	// append(&array, -8);
	// append(&array, 24);
	// append(&array, -1);
	// append(&array, 11);
	// append(&array, 21);
	// append(&array, -4);
	// display(&array); 

	// int index = linearSearch(&array, 11);
	// printf("Item 11 at index: %d\n", index);

	// int index = iterBinarySearch(&array, 0, array.length - 1, 4);
	// printf("Found item at index: %d\n", index);

	// index = recrBinarySearch(&array, 0, array.length - 1, 4);
	// printf("Found item at index: %d\n", index);

	// printf("Getter at 5: %d\n", get(&array, 5));
	// printf("Max: %d\n", max(&array));
	// printf("Min: %d\n", min(&array));
	// printf("Sum: %d\n", sum(&array));
	// printf("Average: %d\n", average(&array));

	// reverse(&array);
	// insertSort(&array, 19);
	// insert(&array, 3, 32);
	// display(&array);

	// printf("Array is sorted: %d\n", isSorted(&array));

	// rearrange(&array);
	// display(&array);

	// free(array.a);

	Array first = new_array(5);
	Array second = new_array(7);

	append(&first, -8);
	append(&first, -1);
	append(&first, 2);
	append(&first, 4);
	append(&first, 9);
	printf("First:\t");
	display(&first);

	append(&second, -6);
	append(&second, -4);
	append(&second, 0);
	append(&second, 2);
	append(&second, 4);
	append(&second, 6);
	append(&second, 10);
	printf("Second:\t");
	display(&second);

	printf("\nMerged:\t");
	Array mer = merge(&first, &second);
	display(&mer);

	printf("Union:\t");
	Array uni = unionize(&first, &second);
	display(&uni);

	printf("Inter:\t");
	Array inter = intersection(&first, &second);
	display(&inter);

	printf("Diff:\t");
	Array diff = difference(&first, &second);
	display(&diff);

	return 0;
}