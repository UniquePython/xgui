#include "events.h"
#include "draw.h"
#include "widget.h"

#include <stdio.h>

bool ctx_init(XGui_Context *ctx, int width, int height)
{
    ctx->running = false;
    ctx->on_draw = NULL;
    ctx->on_key = NULL;
    ctx->on_mouse = NULL;
    ctx->on_mouse_move = NULL;
    ctx->userdata = NULL;
    ctx->widget_count = 0;
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

void ctx_set_mouse_move_callback(XGui_Context *ctx, XGui_MouseMoveCallback cb, void *userdata)
{
    ctx->on_mouse_move = cb;
    ctx->userdata = userdata;
}

void ctx_quit(XGui_Context *ctx)
{
    ctx->running = false;
}

static void ctx_request_redraw(XGui_Context *ctx)
{
    XClearArea(ctx->win.display, ctx->win.window, 0, 0, 0, 0, True);
}

void ctx_run(XGui_Context *ctx)
{
    XEvent event;
    ctx->running = true;

    while (ctx->running)
    {
        XNextEvent(ctx->win.display, &event);
        switch (event.type)
        {
        case Expose:
            if (ctx->on_draw)
                ctx->on_draw(ctx, ctx->userdata);
            for (int i = 0; i < ctx->widget_count; i++)
            {
                XGui_Widget *w = ctx->widgets[i];
                if (w->on_draw)
                    w->on_draw(w, &ctx->win);
            }
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
            for (int i = 0; i < ctx->widget_count; i++)
            {
                XGui_Widget *w = ctx->widgets[i];
                if (w->on_mouse && widget_contains(w, event.xbutton.x, event.xbutton.y))
                    w->on_mouse(w, event.xbutton.x, event.xbutton.y, (XGui_MouseButton)event.xbutton.button, XGUI_MOUSE_PRESS);
            }
            ctx_request_redraw(ctx);
            break;
        case ButtonRelease:
            if (ctx->on_mouse)
                ctx->on_mouse(ctx, event.xbutton.x, event.xbutton.y, (XGui_MouseButton)event.xbutton.button, XGUI_MOUSE_RELEASE,
                              ctx->userdata);
            for (int i = 0; i < ctx->widget_count; i++)
            {
                XGui_Widget *w = ctx->widgets[i];
                if (w->on_mouse && widget_contains(w, event.xbutton.x, event.xbutton.y))
                    w->on_mouse(w, event.xbutton.x, event.xbutton.y, (XGui_MouseButton)event.xbutton.button, XGUI_MOUSE_RELEASE);
            }
            ctx_request_redraw(ctx);
            break;
        case MotionNotify:
            if (ctx->on_mouse_move)
                ctx->on_mouse_move(ctx, event.xmotion.x, event.xmotion.y, ctx->userdata);
            for (int i = 0; i < ctx->widget_count; i++)
            {
                XGui_Widget *w = ctx->widgets[i];
                if (w->on_mouse_move)
                    w->on_mouse_move(w, event.xmotion.x, event.xmotion.y);
            }
            ctx_request_redraw(ctx);
            break;
        }
    }
}

void ctx_add_widget(XGui_Context *ctx, XGui_Widget *widget)
{
    if (ctx->widget_count >= XGUI_MAX_WIDGETS)
    {
        fprintf(stderr, "Widget limit reached\n");
        return;
    }
    ctx->widgets[ctx->widget_count++] = widget;
}