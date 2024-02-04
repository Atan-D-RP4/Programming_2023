#include <curses.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main()
{
    srand(time(NULL));
    WINDOW *win = initscr();
    if (win == NULL)
    {
        fprintf(stderr, "Screen Initialisation failed!: %d (%s)\n", errno, strerror(errno));
        return errno;
    }

    if (keypad(win, TRUE) != OK)
    {
        fprintf(stderr, "Setting Keypad Mode failed!: %d (%s)\n", errno, strerror(errno));
        endwin();
        return errno;
    }
    if (nodelay(win, TRUE) != OK)
    {
        fprintf(stderr, "Setting Nodelay Mode failed!: %d (%s)\n", errno, strerror(errno));
        endwin();
        return errno;
    }

    int posX = 0, posY = 0;
    int foodX = rand() % 20, foodY = rand() % 20;

    int dirX = 1, dirY = 0;

    while (true)
    {
        int pressed = wgetch(win);
        if (pressed == KEY_LEFT)
        {
            dirX = -1;
            dirY = 0;
        }
        if (pressed == KEY_RIGHT)
        {
            dirX = 1;
            dirY = 0;
        }
        if (pressed == KEY_UP)
        {
            dirX = 0;
            dirY = -1;
        }
        if (pressed == KEY_DOWN)
        {
            dirX = 0;
            dirY = 1;
        }

        posX += dirX;
        posY += dirY;
        erase();

        mvaddstr(posY, posX, "*");
        mvaddstr(foodY, foodX, "&");
        if (posX == foodX && posY == foodY)
        {
            foodX = rand() % 20;
            foodY = rand() % 20;
        }
        usleep(200000);
    }

    endwin();
    return 0;
}