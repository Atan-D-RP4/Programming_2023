// The Successful Implementation
// All Test Cases Passed


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// sort the strings in lexicographically non-decreasing order.
int lexicographic_sort(const char* a, const char* b)
{
    return strcmp(a, b);
}

//sort the strings in lexicographically non-increasing order.
int lexicographic_sort_reverse(const char* a, const char* b)
{
    return strcmp(b, a);
}

//sort the strings in non-decreasing order of the number of distinct characters present in them.
//If two strings have the same number of distinct characters present in them, then the
//lexicographically smaller string should appear first.
int sort_by_number_of_distinct_characters(const char* a, const char* b)
{
    int uniqLenA = 0, uniqLenB = 0;
    int charInA[26] = {0}, charInB[26] = {0};
    const char *tmpA = a; const char *tmpB = b;
    for (int c = 0; (c = *a++); )
    {
        charInA[tolower(c) - 'a']++;
    }


    for (int c = 0; (c = *b++); )
    {
        charInB[tolower(c) - 'a']++;

    }

    for (int i = 0, n = 0; i < 26; i++)
    {
        (charInA[i] > 0 ? uniqLenA++ : n++);
        (charInB[i] > 0 ? uniqLenB++ : n++);
    }

    int x = (uniqLenA == uniqLenB ? strcmp(tmpA, tmpB): uniqLenA - uniqLenB);
    return x;
}

//sort the strings in non-decreasing order of their lengths. If two strings have the same length,
//then the lexicographically smaller string should appear first.
int sort_by_length(const char* a, const char* b)
{
    int lenA = strlen(a);
    int lenB = strlen(b);
    return ((lenA == lenB) ? strcmp(a, b) : (lenA - lenB));
}

void string_sort(char** arr, const int len, int (*cmp_func)(const char* a, const char* b)) {
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (cmp_func(arr[i], arr[j]) > 0) {
                // Swap pointers, not the strings
                char* tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}


int main()
{
    int n;
    scanf("%d", &n);

    char** arr;
	arr = (char**)malloc(n * sizeof(char*));

    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }

    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");
}
