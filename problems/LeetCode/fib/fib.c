// LeetCode 509. Fibonacci Number

#include <stdio.h>


int fib(int n) {
    int arr[2] = { 0, 1 };

    if (n == 1) return arr[0];
    if (n == 2) return arr[1];

    for (int i = 0; i < n - 1; ++i) {
        int temp = arr[1];
        arr[1] = arr[0] + arr[1];
        arr[0] = temp;
    }

    return arr[1];
}

int main() {
  printf("Hello, World!\n");
  
  int n = 10;
  printf("Fibonacci of %d is %d\n", n, fib(n));

}
