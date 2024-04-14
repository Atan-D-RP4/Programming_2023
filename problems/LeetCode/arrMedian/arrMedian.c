// Median of Two Sorted Arrays
// From LeetCode

#include <stdio.h>
#include <stdlib.h>

// Fully Working Solution. Meets All Test Requirments
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int nums3Size = nums1Size + nums2Size;
    int nums3[nums3Size];
    int i = 0, j = 0, k = 0;
    int l = 0, h = nums3Size + 1;
    int mid = l + (h - 1) / 2;
    double median = 0;
    while (i < nums1Size && j < nums2Size)
    {
        if (nums1[i] < nums2[j])
            nums3[k++] = nums1[i++];
        else
            nums3[k++] = nums2[j++];
    }

    for (; i < nums1Size; nums3[k++] = nums1[i++]);

    for (; j < nums2Size; nums3[k++] = nums2[j++]);

    if (nums3Size % 2 == 0 && nums3Size > 1)
        median = (float)(nums3[mid - 1] + nums3[mid]) / 2;
    else
        median = nums3[mid];

    return median;
}

int main()
{
    int arr1[0];
    int arr2[2] = {2, 3};
    double median = findMedianSortedArrays(arr1, 0, arr2, 2);
    printf("Median: %lf\n", median);
}
