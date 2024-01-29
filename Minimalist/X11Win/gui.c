#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>

int main()
{
    XEvent event;
    Display* display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "XOpenDisplay failed!\n");
        return 1;
    }
    Window win = XCreateSimpleWindow(display, DefaultRootWindow(display), 50, 50, 250, 250, 1, BlackPixel(display, 0), WhitePixel(display, 0)); 
    XMapWindow(display, win);
    XSelectInput(display, win, ExposureMask);

    while (true)
    {
        XNextEvent(display, &event);
        if (event.type == Expose)
        {
            XClearWindow(display, win);
            XDrawString(display, win, DefaultGC(display, 0), 100, 100, "Hello World!", 12);
        }
    }

    XCloseDisplay(display);
    return 0;
}