#include <stdio.h>
#include <stdlib.h>

int bin_search(int *arr, int left, int right, int key)
{
    if (right >= 0)
    {
        int mid = left + ((right - 1)/ 2);
        if (key == arr[mid])
            return mid;
        else if (key < arr[mid])
            return bin_search(arr, left, mid - 1, key);
        else if (key > arr[mid])
            return bin_search(arr, mid + 1, right, key);
    }
    return -1;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int r[2];
    returnSize = NULL;
    for (int i = 0; i < numsSize; i++)
    {
        int index_s = bin_search(nums, 0, numsSize - 1, target - nums[i]);
        if (nums[index_s] + nums[i] == target && index_s != i)
        {
            returnSize = (int*)calloc(2, sizeof(int));
            returnSize[0] = r[0] = i;
            returnSize[1] = r[1] = index_s;
            return returnSize;
        }
    }

    return returnSize;
}

int main(void)
{
    int arr[4] = {2,7,11,15};
    int* returnS = NULL;
    returnS = twoSum(arr, 4, 9, returnS);
    for (int i = 0; i < 2; i++)
        printf("%d ", returnS[i]);
    printf("\n");
}
