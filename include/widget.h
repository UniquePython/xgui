#pragma once

#include "window.h"
#include "types.h"

#include <stdbool.h>

typedef struct XGui_Widget
{
    int x, y, width, height;
    void (*on_draw)(struct XGui_Widget *w, XGui_Window *win);
    void (*on_mouse)(struct XGui_Widget *w, int x, int y, XGui_MouseButton button, XGui_MouseAction action);
    void (*on_mouse_move)(struct XGui_Widget *w, int x, int y);
} XGui_Widget;

bool widget_contains(XGui_Widget *w, int px, int py);