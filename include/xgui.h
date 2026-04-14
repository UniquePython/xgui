#pragma once

#include <X11/Xlib.h>
#include <stdbool.h>

typedef struct
{
    Display *display;
    Window window;
    int screen;
} XGui;

bool xgui_init(XGui *gui, int width, int height);
void xgui_shutdown(XGui *gui);