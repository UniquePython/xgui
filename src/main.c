#include "xgui.h"
#include <stdio.h>

void on_draw(XGui *gui, void *userdata)
{
    xgui_draw_rect(gui, 100, 100, 200, 150, XGUI_RGB(255, 0, 0));
    xgui_draw_rect(gui, 400, 200, 100, 100, XGUI_RGB(0, 0, 255));
}

void on_key(XGui *gui, int keycode, void *userdata)
{
    printf("key pressed: %d\n", keycode);
    xgui_quit(gui);
}

void on_mouse(XGui *gui, int x, int y, XGui_MouseButton button, XGui_MouseAction action, void *userdata)
{
    printf("mouse %s at (%d, %d) button %d\n", action == XGUI_MOUSE_PRESS ? "press" : "release", x, y, button);
}

int main(void)
{
    XGui gui;
    if (!xgui_init(&gui, 900, 600))
        return 1;

    xgui_set_draw_callback(&gui, on_draw, NULL);
    xgui_set_key_callback(&gui, on_key, NULL);
    xgui_set_mouse_callback(&gui, on_mouse, NULL);
    xgui_run(&gui);

    xgui_shutdown(&gui);
    return 0;
}