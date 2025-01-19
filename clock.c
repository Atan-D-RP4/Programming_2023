// Run Command: cc -o clock clock.c && ./clock && rm clock
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int font[] = {31599, 19812, 14479, 31207, 23524, 29411,
              29679, 30866, 31727, 31719, 1040};
#define FONT_N 11
#define FONT_ROWS 5
#define FONT_COLS 3

#define DIGIT_N 8
#define DIGIT_PAD 2

#define KB 1024ULL

void print_time(int width, int height);

int main(void) {
  int width = (FONT_COLS + DIGIT_PAD) * DIGIT_N;
  int height = FONT_ROWS;

  while (1) {
    print_time(width, height);
    sleep(1);
    printf("\033[%dA\033[%dD", height, width);
  }
}

void print_time(int width, int height) {

  time_t t = time(NULL);
  struct tm *tm = localtime(&t);

  int digits[DIGIT_N];
  digits[0] = tm->tm_hour / 10;
  digits[1] = tm->tm_hour % 10;
  digits[2] = 10;
  digits[3] = tm->tm_min / 10;
  digits[4] = tm->tm_min % 10;
  digits[5] = 10;
  digits[6] = tm->tm_sec / 10;
  digits[7] = tm->tm_sec % 10;

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int digit = x / (FONT_COLS + DIGIT_PAD);
      int dx = x % (FONT_COLS + DIGIT_PAD);
      if (y < FONT_ROWS && dx < FONT_COLS &&
          (font[digits[digit]] >> ((FONT_ROWS - y - 1) * FONT_COLS + dx)) & 1) {
        printf("\033[1;31m█\033[0m");
      } else {
        printf("█");
      }
    }
    printf("\n");
  }
}
