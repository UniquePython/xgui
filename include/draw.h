#pragma once

#include "window.h"

typedef struct
{
    unsigned char r, g, b;
} XGui_Color;

#define XGUI_RGB(r, g, b) ((XGui_Color){r, g, b})

void draw_clear(XGui_Window *win, XGui_Color color);
void draw_rect(XGui_Window *win, int x, int y, int width, int height, XGui_Color color);
void draw_text(XGui_Window *win, int x, int y, const char *text, XGui_Color color);