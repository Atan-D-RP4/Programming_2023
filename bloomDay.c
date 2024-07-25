#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARGPARSE_IMPLEMENTATION
#include "../cheaders/argparse.h"

int test(void);

int cmp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int minDays(int* bloomDay, int bloomDaySize, int m, int k) {
	if (m * k > bloomDaySize)
		return -1;

	int left = 1, right = bloomDay[bloomDaySize - 1];
	while (left < right) {
		int mid = left + (right - left) / 2;
		int flower = 0, bouquet = 0;
		for (int i = 0; i < bloomDaySize; i++) {
			if (bloomDay[i] <= mid) {
				flower++;
				if (flower == k) {
					bouquet++;
					flower = 0;
				}
			} else {
				flower = 0;
			}
		}
		if (bouquet < m) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}
	return left;
};

int main(void) {

	int bloomDay[] = {1,10,3,10,2};
	int bloomDaySize = sizeof(bloomDay) / sizeof(bloomDay[0]);
	int m = 3;
	int k = 1;

	int ret = minDays(bloomDay, bloomDaySize, m, k);

	printf("ret = %d\n", ret);

	int err = test();
	if (err) {
		printf("test failed\n");
	} else {
		printf("test pass\n");
	}

	return 0;
}

int test(void) {

	int *bloomDays[] = {
		(int[]){ 1, 10, 3, 10, 2 },
		(int[]){ 1, 10, 3, 10, 2 },
		(int[]){ 7, 7, 7, 7, 12, 7, 7 },
		(int[]){ 1000000000, 1000000000 },
		(int[]){ 1, 10, 2, 9, 3, 8, 4, 7, 5, 6 }
	};

	int bloomDaySizes[] = { 5, 5, 7, 2, 10 };

	int m[] = { 3, 3, 2, 1, 2 };

	int k[] = { 1, 2, 3, 1, 2 };

	int ret[] = { 3, -1, 12, 1000000000, 9 };

	for (int i = 0; i < 5; i++) {
		int bloomDaySize = bloomDaySizes[i];
		int res = minDays(bloomDays[i], bloomDaySize, m[i], k[i]);

		if(res != ret[i]) {
			printf("bloomDaySize: %d, m: %d, k: %d\n", bloomDaySize, m[i], k[i]);
			printf("Ret: %d, Expected: %d\n", res, ret[i]);
			for (int j = 0; j < bloomDaySize; j++) {
				printf("%d ", bloomDays[i][j]);
			}
			printf("\n");
			return -1;
		}
	}
	return 0;
}
