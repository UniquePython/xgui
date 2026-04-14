#include "xgui.h"
#include <stdio.h>

void on_draw(XGui_Context *ctx, void *userdata)
{
    draw_clear(&ctx->win, XGUI_RGB(30, 30, 30));
    draw_rect(&ctx->win, 100, 100, 200, 150, XGUI_RGB(255, 0, 0));
    draw_text(&ctx->win, 120, 180, "Hello, XGui!", XGUI_RGB(255, 255, 255));
}

void on_key(XGui_Context *ctx, int keycode, void *userdata)
{
    printf("key: %d\n", keycode);
    ctx_quit(ctx);
}

void on_mouse(XGui_Context *ctx, int x, int y, XGui_MouseButton button, XGui_MouseAction action, void *userdata)
{
    printf("mouse %s at (%d,%d) button %d\n", action == XGUI_MOUSE_PRESS ? "press" : "release", x, y, button);
}

int main(void)
{
    XGui_Context ctx;
    if (!ctx_init(&ctx, 800, 600))
        return 1;

    ctx_set_draw_callback(&ctx, on_draw, NULL);
    ctx_set_key_callback(&ctx, on_key, NULL);
    ctx_set_mouse_callback(&ctx, on_mouse, NULL);

    ctx_run(&ctx);
    ctx_shutdown(&ctx);
    return 0;
}