#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VEC_IMPLEMENTATION
#include "vec.h"

int cmp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main(void) {
	printf("Enter the number of elements: ");
	int n; scanf("%d", &n);

	int arr[n];

	printf("Enter the elements: ");
	for (size_t i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	printf("Enter the value of k: ");
	int k; scanf("%d", &k);

	// Find the kth maximum element with O(nk) time complexity
	int max = 0;
	for (size_t i = 0; i < k; ++i) {
		for (size_t j = 0; j < n; ++j) {
			if (arr[j] >= arr[max]) {
				max = j;
			}
		}
		if (i != k - 1) {
			arr[max] = 0;
		}
	}
	printf("The %dth maximum element is: %d\n", k, arr[max]);

	// Find the kth maximum element with O(nlogn) time complexity
	qsort(arr, n, sizeof(int), cmp);
	printf("The %dth maximum element is: %d\n", k, arr[n - k]);

	// Find the kth maximum element with O(nlogk) time complexity
	int *queue = Vec(int, my_alloc);
	for (size_t i = 0; i < k; ++i) {
		Vec_push(queue, arr[i]);
	}

	for (size_t i = k; i < n; ++i) {
		printf("%2d", queue[i]);
	}

}
