#include "xgui.h"
#include <stdio.h>

typedef struct
{
    XGui_Button btn;
} AppState;

void on_click(void *userdata)
{
    printf("button clicked!\n");
}

void on_draw(XGui_Context *ctx, void *userdata)
{
    draw_clear(&ctx->win, XGUI_RGB(30, 30, 30));
}

void on_key(XGui_Context *ctx, unsigned int keycode, void *userdata)
{
    (void)keycode;
    ctx_quit(ctx);
}

int main(void)
{
    XGui_Context ctx;
    if (!ctx_init(&ctx, 800, 600))
        return 1;

    AppState state;
    button_init(&state.btn, 300, 250, 200, 50, "Click Me", on_click, NULL);
    ctx_add_widget(&ctx, (XGui_Widget *)&state.btn);

    ctx_set_draw_callback(&ctx, on_draw, &state);
    ctx_set_key_callback(&ctx, on_key, &state);

    ctx_run(&ctx);
    ctx_shutdown(&ctx);
    return 0;
}