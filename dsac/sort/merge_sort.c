#include <stdio.h>
#include <stdlib.h>

int usage(int argc, char* argv[]);
int* get_elements(int size);
void show_elements(int* arr, int size);
void merge(int* arr, int size_main, int* left, int size_left, int* right, int size_right);
void merge_sort(int* arr, int size);



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
    merge_sort(arr, size);
    printf("Sorted Order:\n");
    show_elements(arr, size);
    free(arr);
}


int usage(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./merge_sort [No.of elements(int)]\n");
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


void merge(int* arr, int size_main, int* left, int size_left, int* right, int size_right)
{
    int i, j, k;

    for (i = 0, j = 0, k = 0; i < size_left && j < size_right; k++)
    {
        if (left[i] < right[j])
            arr[k] = left[i++];
        else
            arr[k] = right[j++];
    }

    for (; i < size_left; arr[k++] = left[i++]);

    for (; j < size_right; arr[k++] = right[j++]);

    return;
}


void merge_sort(int* arr, int size)
{
    if (size == 1)
        return;

    int mid = size / 2;
    int left[mid];
    int right[size - mid];

    for (int i = 0; i < size; i++)
    {
        if (i < mid)
            left[i] = arr[i];
        else
            right[i - mid] = arr[i];
    }

    merge_sort(left, mid);
    merge_sort(right, (size - mid));
    merge(arr, size, left, mid, right, (size - mid));
    show_elements(arr, size);

    return;
}
