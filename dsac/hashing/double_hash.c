// Double Hashing

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int usage(int argc, char* argv[]);
int* get_elements(int* arr, int size);
void show_elements(int* arr, int size);
int closest_prime(int size);
int hash(int key, int* arr, int size);

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
        printf("Memory Allocation Failed");
        return 1;
    }

    show_elements(arr, size);
    free(arr);
    return 0;
}

int usage(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Usage: ./double_hash [No.of elements]\n");
        return 1;
    }
    return 0;
}

int* get_elements(int* arr, int size)
{
    arr =  malloc(size * (sizeof(int)));
    if (arr == NULL)
    {
        printf("Memory Allocation Failed");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        arr[i] = -1;
    }

    int key, index;
    for (int i = 0; i < size; i++)
    {
        printf("Element %d:", (i + 1));
        scanf("%d", &key);
        index = hash(key, arr, size);
        arr[index] = key;
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

int closest_prime(int key)
{
   for (int i = key; i >= 2; i--)
    {
        if (((i % 6 == 5 || i % 6 == 1)) || ((i == 3 || i == 2)))
        {
            return i;
        }
    }
    return 2;
}

int hash(int key, int* arr, int size)
{
    int hash_value0;
    int prime = closest_prime(key);
    int hash_value1 = key % size;
    int hash_value2 = prime - (key % prime);
    if (arr[hash_value1] == -1)
    {
        hash_value0 = hash_value1;
        return hash_value0;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            hash_value0 = (hash_value1 + (i * hash_value2)) % size;
            if (arr[hash_value0] == -1)
                return hash_value0;
        }
    }
    return hash_value0;
}
