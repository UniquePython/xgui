#pragma once

#include <X11/Xlib.h>
#include <stdbool.h>

typedef struct
{
    Display *display;
    Window window;
    GC gc;
    XFontStruct *font;
    int screen;
    int width;
    int height;
} XGui_Window;

bool window_init(XGui_Window *win, int width, int height);
void window_shutdown(XGui_Window *win);