#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define max(a, ...) ({ \
    typeof(a) args[] = {a, __VA_ARGS__}; \
    typeof(a) max = args[0]; \
    for (int i = 1; i < sizeof(args) / sizeof(args[0]); ++i) { \
        if (args[i] > max) { \
            max = args[i]; \
        } \
    } \
    max; \
})

int DIRECTIONS[] = { 0, 1, 0, -1 };

int dfsBacktracking(int **grid, int rows, int cols, int row, int col) {
    if (row >= rows || row < 0 || col >= cols || col < 0 || grid[row][col] == 0)
        return 0;
    int maxGold = 0;
    int originVal = grid[row][col];
    grid[row][col] = 0;
    for (int dir = 0; dir < 4; ++dir) {
        int tmp = dfsBacktracking(grid, rows, cols, DIRECTIONS[dir] + row, DIRECTIONS[(dir + 1) % 4] + col);
        maxGold = maxGold > tmp ? maxGold : tmp;
    }
    grid[row][col] = originVal;
    return maxGold + originVal;
}

int getMaximumGold(int** grid, int gridSize, int* gridColSize) {
    int maxGold = 0;
    int rows = gridSize, cols = *gridColSize;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int tmp = dfsBacktracking(grid, rows, cols, row, col);
            maxGold = (maxGold > tmp) ? maxGold : tmp;
        }
    }
    return maxGold;
}

int main() {
    srand(time(NULL));

    int **grid = (int **) malloc(3 * sizeof(int *));
    int gridColSize = 3;
    for (int i = 0; i < 3; i++) {
        grid[i] = (int *) malloc(gridColSize * sizeof(int));
    }

    grid[0][0] = 0;
    grid[0][1] = 6;
    grid[0][2] = 0;
    grid[1][0] = 5;
    grid[1][1] = 8;
    grid[1][2] = 7;
    grid[2][0] = 0;
    grid[2][1] = 9;
    grid[2][2] = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
     //       grid[i][j] = rand() % 100;
            printf("%2d ", grid[i][j]);
        }
        printf("\n");
    }

    printf("Max gold: %d\n", getMaximumGold(grid, 3, &gridColSize));

    return 0;
}
