#include <stdio.h>
#include <stdlib.h>

const int RUN = 32;

int usage(int argc, char* argv[]);
int* get_elements(int size);
void show_elements(int* arr, int size);
void insert_sort(int* arr, int left, int right);

int min(int x, int y) {

    return (x < y) ? x : y;

}

// Function to perform insertion sort on a given array and range
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Function to merge two sorted subarrays
void merge(int arr[], int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    int *left = (int *)malloc(sizeof(int) * len1);
    int *right = (int *)malloc(sizeof(int) * len2);

    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];

    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < len1)
        arr[k++] = left[i++];
    while (j < len2)
        arr[k++] = right[j++];

    free(left);
    free(right);
}

// Function to perform Timsort
void timSort(int arr[], int n) {
    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, min((i + RUN - 1), (n - 1)));

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}


int main(int argc, char* argv[])
{
    int error = usage(argc, argv);
    if(error != 0)
        return error;

    int size = atoi(argv[1]);
	int* arr = get_elements(size);
    if (arr == NULL)
    {
        free(arr);
        return 2;
    }
    printf("Original Order:\n");
    show_elements(arr, size);
    timSort(arr, size);
    printf("Sorted Order:\n");
    show_elements(arr, size);
    free(arr);
}

int usage(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./timsort [No.of elements(int)]\n");
        return 1;
    }
    return 0;
}

int* get_elements(int size)
{
    int* arr =  malloc(size * (sizeof(int)));

    if (arr == NULL)
    {
        printf("Memory Allocation Failed");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        printf("Element %d:", (i + 1));
        scanf("%d", &arr[i]);
    }

    return arr;
}


void show_elements(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}


