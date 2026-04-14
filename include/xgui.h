#pragma once

#include <X11/Xlib.h>
#include <stdbool.h>

typedef struct xgui_t XGui;

typedef void (*XGui_DrawCallback)(XGui *gui, void *userdata);
typedef void (*XGui_KeyCallback)(XGui *gui, int keycode, void *userdata);

typedef struct xgui_t
{
    Display *display;
    Window window;
    GC gc;
    int screen;
    bool running;
    XGui_DrawCallback on_draw;
    XGui_KeyCallback on_key;
    void *userdata;
} XGui;

bool xgui_init(XGui *gui, int width, int height);
void xgui_shutdown(XGui *gui);

void xgui_set_draw_callback(XGui *gui, XGui_DrawCallback cb, void *userdata);
void xgui_set_key_callback(XGui *gui, XGui_KeyCallback cb, void *userdata);

void xgui_run(XGui *gui);
void xgui_quit(XGui *gui);

typedef struct
{
    unsigned char r, g, b;
} XGui_Color;

#define XGUI_RGB(r, g, b) ((XGui_Color){r, g, b})

void xgui_draw_rect(XGui *gui, int x, int y, int width, int height, XGui_Color color);