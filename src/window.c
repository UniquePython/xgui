#include "window.h"
#include <stdio.h>

bool window_init(XGui_Window *win, int width, int height)
{
    win->display = XOpenDisplay(NULL);
    if (!win->display)
    {
        fprintf(stderr, "Cannot open display\n");
        return false;
    }

    win->screen = DefaultScreen(win->display);
    win->width = width;
    win->height = height;

    win->window = XCreateSimpleWindow(
        win->display,
        RootWindow(win->display, win->screen),
        0, 0, width, height, 1,
        BlackPixel(win->display, win->screen),
        WhitePixel(win->display, win->screen));

    XSelectInput(win->display, win->window, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);

    XMapWindow(win->display, win->window);

    win->gc = XCreateGC(win->display, win->window, 0, NULL);

    win->font = XLoadQueryFont(win->display, "-misc-fixed-medium-r-normal--16-110-100-100-c-80-iso8859-1");
    if (!win->font)
    {
        fprintf(stderr, "Cannot load font\n");
        return false;
    }
    XSetFont(win->display, win->gc, win->font->fid);

    return true;
}

void window_shutdown(XGui_Window *win)
{
    XFreeFont(win->display, win->font);
    XFreeGC(win->display, win->gc);
    XDestroyWindow(win->display, win->window);
    XCloseDisplay(win->display);
}