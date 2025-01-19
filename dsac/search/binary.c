#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int* get_elements(int* arr, int size);
int bin_search(int *arr, int left, int right, int key);

int main (int argc, char* argv[])
{
	if (argc == 1)
	{
		printf("Usage: ./binary [No.of Elements]");
		return 1;
	}

	int size = atoi(argv[1]);
	int* arr = get_elements(arr, size);
	// Get Key Before Line 19
	int key; printf("Enter Key to Search:");
	scanf("%d", &key);
	printf("Searching for %d in Stored Data\n", key);
	int idx = bin_search(arr, 0, size - 1, key);
	if (idx != -1)
		printf("Element Found at Index %d\n", idx);
	else
		printf("Element Not Found\n");
	free(arr);
	return 0;
}

int bin_search(int *arr, int left, int right, int key)
{
	if (right >= left)
	{
		int mid = left + ((right - left)/ 2);
		if (key == arr[mid])
			return mid;
		else if (key < arr[mid])
			return bin_search(arr, left, mid - 1, key);
		else if (key > arr[mid])
			return bin_search(arr, mid + 1, right, key);
	}

	return -1;
}

int* get_elements(int* arr, int size)
{
	arr =  calloc(size, sizeof(int));
	if (arr == NULL) {
		printf("Memory Allocation Failed");
		return NULL;
	}

	for (int i = 0; i < size; i++) {
		scanf("%d", &arr[i]);
	}

	return arr;
}
