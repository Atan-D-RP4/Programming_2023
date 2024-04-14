#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b);
int* get_elements(int size);
void show_elements(int* arr, int size);
void select_sort(int* arr, int size);

int main(void)
{
    printf("No.of Elements to be Sorted: ");
	int size; scanf("%d", &size);
	int* N = NULL;
    N = get_elements(size);
    if (N == NULL)
    {
        free(N);
        return 1;
    }
    printf("Original Order: ");
    show_elements(N, size);
    select_sort(N, size);
    printf("Sorted Order: ");
    show_elements(N, size);
}

void swap(int *a, int *b)
{
   int temp = *a;
    *a = *b;
    *b = temp;

}

void show_elements(int* arr, int size)
{
        for(int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
    printf("\n");
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

void select_sort(int* N, int size)
{
    int min_index;
    for (int i = 0; i < size - 1; i++)
    {
        min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            if (N[] < N[min_index])
                    min_index = j;
        }
        if (min_index != i)
            swap(&N[min_index], &N[i]);
     }
}
