#include "events.h"
#include "draw.h"
#include <stdio.h>

int ctx_init(XGui_Context *ctx, int width, int height)
{
    ctx->running = 0;
    ctx->on_draw = NULL;
    ctx->on_key = NULL;
    ctx->on_mouse = NULL;
    ctx->userdata = NULL;
    return window_init(&ctx->win, width, height);
}

void ctx_shutdown(XGui_Context *ctx)
{
    window_shutdown(&ctx->win);
}

void ctx_set_draw_callback(XGui_Context *ctx, XGui_DrawCallback cb, void *userdata)
{
    ctx->on_draw = cb;
    ctx->userdata = userdata;
}

void ctx_set_key_callback(XGui_Context *ctx, XGui_KeyCallback cb, void *userdata)
{
    ctx->on_key = cb;
    ctx->userdata = userdata;
}

void ctx_set_mouse_callback(XGui_Context *ctx, XGui_MouseCallback cb, void *userdata)
{
    ctx->on_mouse = cb;
    ctx->userdata = userdata;
}

void ctx_quit(XGui_Context *ctx)
{
    ctx->running = 0;
}

void ctx_run(XGui_Context *ctx)
{
    XEvent event;
    ctx->running = 1;

    while (ctx->running)
    {
        XNextEvent(ctx->win.display, &event);
        switch (event.type)
        {
        case Expose:
            if (ctx->on_draw)
                ctx->on_draw(ctx, ctx->userdata);
            XFlush(ctx->win.display);
            break;
        case KeyPress:
            if (ctx->on_key)
                ctx->on_key(ctx, event.xkey.keycode, ctx->userdata);
            break;
        case ButtonPress:
            if (ctx->on_mouse)
                ctx->on_mouse(ctx, event.xbutton.x, event.xbutton.y, (XGui_MouseButton)event.xbutton.button, XGUI_MOUSE_PRESS,
                              ctx->userdata);
            break;
        case ButtonRelease:
            if (ctx->on_mouse)
                ctx->on_mouse(ctx, event.xbutton.x, event.xbutton.y, (XGui_MouseButton)event.xbutton.button, XGUI_MOUSE_RELEASE,
                              ctx->userdata);
            break;
        }
    }
}