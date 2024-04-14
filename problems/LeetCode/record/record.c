// The Successful Implementation
// All Test Cases Passed

#include <stdio.h>
#include <stdlib.h>

typedef char* string;

int arrSum(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i)
        sum += arr[i];
    return sum;
}

int calPoints(string* operations, int operationsSize) {
    int record[100] = { 0 }, j = 0;
    for (int i = 0; i < operationsSize; ++i) {
        if (atoi(operations[i]) != 0) {
            record[j++] = atoi(operations[i]);
        } else if (operations[i][0] == 'D') {
            record[j] = record[j - 1] * 2;
            j++;
        } else if (operations[i][0] == 'C') {
            j--;
        } else if (operations[i][0] == '+') {
            record[j] = record[j - 2] + record[j - 1];
            j++;
        }
    }

    return arrSum(record, j);
}

int main (void) {
    char* operations[] = {"5","-2","4","C","D","9","+","+"};
    int score = calPoints(operations, 8);
}
