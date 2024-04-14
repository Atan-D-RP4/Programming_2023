#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int val_a = *(int *) a;
    int val_b = *(int *) b;

    return val_b - val_a;
}

int findKthLargest(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), compare);

    return nums[k];
}

int main() {
  int nums[] = {3, 2, 1, 5, 6, 4};
  int k = 2;

  int result = findKthLargest(nums, 6, k);

  for (int i = 0; i < 6; i++) {
    printf("%d ", nums[i]);
  }

  printf("Result: %d\n", result);
}
