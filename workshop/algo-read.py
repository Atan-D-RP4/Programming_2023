#include <stdio.h>
int trap(int* height, int heightSize) {
        int answer = 0;
     for (int i = 0, temp = 0; i < heightSize; ++i) {
           if (height[0] == 0)
                i++;
         for (int j = i + 1; j < heightSize; ++j) {
             if (height[j] >= height[i]) {
                 i = j;
                 break;
              }
             temp = height[i] - height[j];
             answer += temp;
     }
                                  }

      return answer;
 }

 int main() {
      int n;
      printf("Enter N:");
      scanf("%d", &n);

     int arr[n];
     for (int i = 0; i < n; ++i) {
         scanf("%d", &arr[i]);
     }

     printf("Answer: %d\n", trap(arr, n));
}
