// Hashing and Linear Probing

#include <stdio.h>

int main(void)
{

    printf("No.of elements to be stored: ");
    int table_size; scanf("%d", &table_size);

    int hash_table[table_size];
    int hash_value, key;
    for(int i = 0; i < table_size; i++)
        hash_table[i] = -1;

    printf("Enter Elements:\n");

    for (int i = 0; i < table_size; i++)
    {
        printf("%d.", (i + 1));
        scanf("%d", &key);
        hash_value = key % table_size;

        while (hash_table[hash_value] != -1)
           hash_value = (hash_value + 1) % table_size;


        if (hash_table[hash_value] == -1)
        {
            hash_table[hash_value] = key;
        }
    }

    printf("Hash Table:\n");
    for (int i = 0; i < table_size; i++)
        printf("Index %d: %d\n", (i + 1), hash_table[i]);
}

