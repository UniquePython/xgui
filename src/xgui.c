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

    return true;
}

void xgui_shutdown(XGui *gui)
{
    XCloseDisplay(gui->display);
}