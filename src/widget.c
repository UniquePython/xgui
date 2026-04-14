#include "widget.h"

bool widget_contains(XGui_Widget *w, int px, int py)
{
    return px >= w->x && px <= w->x + w->width && py >= w->y && py <= w->y + w->height;
}