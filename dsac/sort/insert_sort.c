#include <stdio.h>
#include <stdlib.h>

int usage(int argc, char* argv[]);
int* get_elements(int* arr, int size);
void show_elements(int* arr, int size);
int* insert_sort(int* arr, int size);

int main(int argc, char* argv[])
{
    if(usage(argc, argv) == 1)
        return 1;

    int size = atoi(argv[1]);
    printf("Enter Elements:\n");

    int* arr = NULL;
    arr = get_elements(arr, size);
    if (arr == NULL)
    {
        printf("Failed to allocate memory\n");
        return 1;
    }

    arr = insert_sort(arr, size);

    show_elements(arr, size);
}

int usage(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Usage: ./insert_sort [No.of elements]\n");
        return 1;
    }
    return 0;
}

int* get_elements(int* arr, int size)
{
    arr = malloc(size * sizeof(int));
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
        printf("Index %d: %d\n", (i + 1), arr[i]);
    }
    return;
}

int* insert_sort(int* arr, int size)
{
    int i, j;
    for (i = 1; i < size; i++)
    {
        int temp = arr[i];

        for (j = i - 1; j > 0 && arr[j] > temp; j--)
        {
                arr[j + 1] = arr[j];
        }

        arr[j + 1] = temp;
    }

    return arr;
}
