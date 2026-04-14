#include "xgui.h"
#include <stdio.h>

void on_draw(XGui *gui, void *userdata)
{
    printf("draw\n");
}

void on_key(XGui *gui, int keycode, void *userdata)
{
    printf("key pressed: %d\n", keycode);
    xgui_quit(gui);
}

int main(void)
{
    XGui gui;
    if (!xgui_init(&gui, 900, 600))
        return 1;

    xgui_set_draw_callback(&gui, on_draw, NULL);
    xgui_set_key_callback(&gui, on_key, NULL);
    xgui_run(&gui);

    xgui_shutdown(&gui);
    return 0;
}