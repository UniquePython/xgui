#pragma once

#include "window.h"

typedef struct XGui_Context XGui_Context;

typedef enum
{
    XGUI_BUTTON_LEFT = 1,
    XGUI_BUTTON_MIDDLE = 2,
    XGUI_BUTTON_RIGHT = 3
} XGui_MouseButton;

typedef enum
{
    XGUI_MOUSE_PRESS,
    XGUI_MOUSE_RELEASE
} XGui_MouseAction;

typedef void (*XGui_DrawCallback)(XGui_Context *ctx, void *userdata);
typedef void (*XGui_KeyCallback)(XGui_Context *ctx, int keycode, void *userdata);
typedef void (*XGui_MouseCallback)(XGui_Context *ctx, int x, int y, XGui_MouseButton button, XGui_MouseAction action, void *userdata);

struct XGui_Context
{
    XGui_Window win;
    int running;
    XGui_DrawCallback on_draw;
    XGui_KeyCallback on_key;
    XGui_MouseCallback on_mouse;
    void *userdata;
};

int ctx_init(XGui_Context *ctx, int width, int height);
void ctx_shutdown(XGui_Context *ctx);
void ctx_set_draw_callback(XGui_Context *ctx, XGui_DrawCallback cb, void *userdata);
void ctx_set_key_callback(XGui_Context *ctx, XGui_KeyCallback cb, void *userdata);
void ctx_set_mouse_callback(XGui_Context *ctx, XGui_MouseCallback cb, void *userdata);
void ctx_quit(XGui_Context *ctx);
void ctx_run(XGui_Context *ctx);