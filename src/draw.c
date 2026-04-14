#include "draw.h"

#include <string.h>

static unsigned long color_to_pixel(XGui_Window *win, XGui_Color color)
{
    XColor xcolor;
    xcolor.red = color.r * 257;
    xcolor.green = color.g * 257;
    xcolor.blue = color.b * 257;
    xcolor.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(win->display, DefaultColormap(win->display, win->screen), &xcolor);
    return xcolor.pixel;
}

void draw_clear(XGui_Window *win, XGui_Color color)
{
    XSetForeground(win->display, win->gc, color_to_pixel(win, color));
    XFillRectangle(win->display, win->window, win->gc, 0, 0, win->width, win->height);
}

void draw_rect(XGui_Window *win, int x, int y, int width, int height, XGui_Color color)
{
    XSetForeground(win->display, win->gc, color_to_pixel(win, color));
    XFillRectangle(win->display, win->window, win->gc, x, y, width, height);
}

void draw_text(XGui_Window *win, int x, int y, const char *text, XGui_Color color)
{
    XSetForeground(win->display, win->gc, color_to_pixel(win, color));
    XDrawString(win->display, win->window, win->gc, x, y, text, strlen(text));
}