#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int* matrix_search(int **arr, int rows, int cols, int key);
int **get_matrix(int** arr, int rows, int cols);

int main (int argc, char* argv[])
{
	if (argc == 1)
	{
		printf("Usage: ./matrixSearch [No.of Rows] [No.of Columns]\n");
		return 1;
	}

	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);
	printf("Enter Matrix Data\n");
	int** arr = get_matrix(arr, rows, cols);
	// Get Key Before Line 19
	int key; printf("Enter Key to Search:");
	scanf("%d", &key);
	printf("Searching for %d in Stored Data\n", key);
	int* idx = matrix_search(arr, rows, cols, key);
	if (idx != NULL) {
		printf("Element Found at Index %d %d\n", idx[0], idx[1]);
		free(idx);
	} else {
		printf("Element Not Found\n");
	}
	return 0;
}


int* matrix_search(int **arr, int rows, int cols, int key)
{
	// O(log(m * n) solution
	int *idx = (int *)calloc(2, sizeof(int));
	int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
	if (key < arr[top][left] || key > arr[bottom][right]) {
		return NULL;
	} else if (key == arr[top][left]) {
		idx[0] = top;
		idx[1] = left;
		return idx;
	} else if (key == arr[bottom][right]) {
		idx[0] = bottom;
		idx[1] = right;
		return idx;
	}

	while (top <= bottom && left <= right) {
		int mid = (top + bottom) / 2;
		if (arr[mid][left] == key) {
			idx[0] = mid;
			idx[1] = left;
			return idx;
		} else if (arr[mid][left] < key) {
			top = mid + 1;
		} else {
			bottom = mid - 1;
		}

		mid = (left + right) / 2;
		if (arr[top][mid] == key) {
			idx[0] = top;
			idx[1] = mid;
			return idx;
		} else if (arr[top][mid] < key) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	
	return NULL;
}

int **get_matrix(int** arr, int rows, int cols)
{
	arr = (int **)calloc(rows, sizeof(int *));
	if (arr == NULL) {
		printf("Memory Allocation Failed");
		return NULL;
	}

	for (int i = 0; i < rows; i++) {
		arr[i] = (int *)calloc(cols, sizeof(int));
		if (arr[i] == NULL) {
			printf("Memory Allocation Failed");
			return NULL;
		}
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	return arr;
}
