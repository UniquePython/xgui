#pragma once

#include "window.h"
#include "types.h"

#include <stdbool.h>

typedef struct XGui_Context XGui_Context;
typedef struct XGui_Widget XGui_Widget;

typedef void (*XGui_DrawCallback)(XGui_Context *ctx, void *userdata);
typedef void (*XGui_KeyCallback)(XGui_Context *ctx, unsigned int keycode, void *userdata);
typedef void (*XGui_MouseCallback)(XGui_Context *ctx, int x, int y, XGui_MouseButton button, XGui_MouseAction action, void *userdata);
typedef void (*XGui_MouseMoveCallback)(XGui_Context *ctx, int x, int y, void *userdata);

#define XGUI_MAX_WIDGETS 32

struct XGui_Context
{
    XGui_Window win;
    bool running;
    XGui_DrawCallback on_draw;
    XGui_KeyCallback on_key;
    XGui_MouseCallback on_mouse;
    XGui_MouseMoveCallback on_mouse_move;
    void *userdata;
    XGui_Widget *widgets[XGUI_MAX_WIDGETS];
    int widget_count;
};

bool ctx_init(XGui_Context *ctx, int width, int height);
void ctx_shutdown(XGui_Context *ctx);
void ctx_set_draw_callback(XGui_Context *ctx, XGui_DrawCallback cb, void *userdata);
void ctx_set_key_callback(XGui_Context *ctx, XGui_KeyCallback cb, void *userdata);
void ctx_set_mouse_callback(XGui_Context *ctx, XGui_MouseCallback cb, void *userdata);
void ctx_set_mouse_move_callback(XGui_Context *ctx, XGui_MouseMoveCallback cb, void *userdata);
void ctx_quit(XGui_Context *ctx);
void ctx_run(XGui_Context *ctx);
void ctx_add_widget(XGui_Context *ctx, XGui_Widget *widget);