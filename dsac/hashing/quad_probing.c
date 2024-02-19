#include <stdio.h>

void show_table(int table[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d.%d ", i, table[i]);
    }
    printf("\n");
}

int main(void)
{

    printf("No.of elements to be stored: ");
    int table_size;
    scanf("%d", &table_size);

    int hash_table[table_size];
    int hash_value, key;
    for (int i = 0; i < table_size; i++)
        hash_table[i] = -1;

    printf("Enter Elements:\n");

    for (int i = 0; i < table_size; i++)
    {
        printf("%d.", (i + 1));
        scanf("%d", &key);
        if (key == -1)
            continue;
        hash_value = key % table_size;

        for (int j = 1; hash_table[hash_value] != -1; j++)
        {
            if (j >= table_size)
            {
                printf("Hash Table is full. No more elements can be Inserted\n");
                break;
            }
            hash_value = (hash_value + (j * j)) % table_size;
            if (j >= (table_size - 1))
            {
                printf("Hash Table is full. No more elements can be Inserted\n");
                break;
            }
        }

        if (hash_table[hash_value] == -1)
        {
            hash_table[hash_value] = key;
            //show_table(hash_table, table_size);
        }
        else
            printf("Element %d couldn't be inserted. Hash Table is full.\n", key);
    }

    printf("Hash Table:\n");
    for (int i = 0; i < table_size; i++)
        printf("Index %d: %d\n", (i), hash_table[i]);
}

