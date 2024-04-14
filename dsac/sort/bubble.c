#include <stdio.h>
#include <stdlib.h>

int usage(int argc, char* argv[]);
int* get_elements(int size);
void show_elements(int* arr, int size);
void swap(int *a, int *b);
void bubble_sort(int arr[], int size);

int main(int argc, char* argv[])
{
    int error = usage(argc, argv);
    if (error != 0)
    {
            return error;
    }

	int size = atoi(argv[1]);
	int* arr = get_elements(size);
    printf("Original Order: "); show_elements(arr, size);
    bubble_sort(arr, size);
    printf("Sorted Order: ");show_elements(arr, size);
    free(arr);
}

int usage(int argc, char* argv[])
{
     if (argc == 1 || argc > 2)
    {
        printf("Usage: ./bubble [No.of elements(int)]\n");
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

void swap(int *a, int *b)
{
   int temp = *a;
    *a = *b;
    *b = temp;

}

void bubble_sort(int arr[], int size)
{
    int pass = 1;
    for (int i = 0, count = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                count = 1;
                printf("Pass %d: ", pass++);
                show_elements(arr, size);
            }

            if(count == 0)
            {
                break;
            }
        }
    }
}
