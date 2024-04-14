#include <stdio.h>
#include <stdlib.h>

int usage(int argc, char* argv[]);
int* get_elements(int size);
void show_elements(int* arr, int size);
void swap(int* a, int* b);
void q_sort(int* arr, int lower, int upper);
int set_pivot(int*arr, int lower, int upper);

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
    q_sort(arr, 0, (size - 1));
    printf("Sorted Order:\n");
    show_elements(arr, size);
    free(arr);
}


int usage(int argc, char* argv[])
{
     if (argc != 2)
    {
        printf("Usage: ./q_sort [No.of elements(int)]\n");
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

void swap(int* a, int* b)
{
    if(a != b)
    {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}


void q_sort(int* arr, int lower, int upper)
{
    if (lower < upper)
    {
        int pivot = set_pivot(arr, lower, upper);
        q_sort(arr, lower, pivot);
        q_sort(arr, (pivot + 1), upper);
    }
    show_elements(arr, lower + upper);
}

int set_pivot(int* arr, int lower, int upper)
{
    int i, j, pivot = arr[lower];
    for(i = lower; (arr[i] <= pivot) && (i <= upper); i++);

    for(j = upper; (arr[j] > pivot) && (j >= lower); j--);

    if (i < j)
    {
        swap(&arr[i], &arr[j]);
        i++;
        j--;
    }
    else
        i++;
    arr[lower] = arr[j];
    arr[j] = pivot;

    return j;
}
