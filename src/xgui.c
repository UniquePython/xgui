#include "xgui.h"

#include <stdio.h>

bool xgui_init(XGui *gui, int width, int height)
{
    gui->display = XOpenDisplay(NULL);
    if (!gui->display)
    {
        fprintf(stderr, "Cannot open display\n");
        return false;
    }

    gui->screen = DefaultScreen(gui->display);

    gui->window = XCreateSimpleWindow(
        gui->display,
        RootWindow(gui->display, gui->screen), /* parent window */
        0, 0,                                  /* x, y position */
        width, height,                         /* size */
        1,                                     /* border width */
        BlackPixel(gui->display, gui->screen), /* border color */
        WhitePixel(gui->display, gui->screen)  /* background color */
    );

    XSelectInput(gui->display, gui->window, ExposureMask | KeyPressMask | ButtonPressMask);

    XMapWindow(gui->display, gui->window);

    return true;
}

void xgui_shutdown(XGui *gui)
{
    XDestroyWindow(gui->display, gui->window);
    XCloseDisplay(gui->display);
}