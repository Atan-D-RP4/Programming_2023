
#include <stdio.h>

void printBytes(void *, int size, int typeSize);

int main(int argc, char *argv[])
{
    int arr[] = {16, 31, 32, 65};
    printBytes(arr, 4, sizeof(int));
}

void printBytes(void *arr, int size, int typeSize)
{
    for (int i = 0; i < size; i++)
    {
        switch (typeSize)
        {
            case sizeof(int):
                // Cast the void pointer to appropriate type then dereference it to get it's value.
                printf("%08x", ((int *) arr)[i]);
                break;
            case sizeof(char):
                printf("%02x", ((char *) arr)[i]);
                break;
            default:
                printf("????");
                break;
        }
        printf(" | ");
    }
    printf("\n");
}
