#include "button.h"
#include <string.h>

static void button_draw(XGui_Widget *base, XGui_Window *win)
{
    XGui_Button *btn = (XGui_Button *)base;

    XGui_Color color;
    switch (btn->state)
    {
    case XGUI_BUTTON_STATE_NORMAL:
        color = XGUI_RGB(80, 80, 80);
        break;
    case XGUI_BUTTON_STATE_HOVER:
        color = XGUI_RGB(120, 120, 120);
        break;
    case XGUI_BUTTON_STATE_PRESSED:
        color = XGUI_RGB(50, 50, 200);
        break;
    default:
        color = XGUI_RGB(80, 80, 80);
        break;
    }

    draw_rect(win, base->x, base->y, base->width, base->height, color);
    draw_text(win, base->x + 10, base->y + base->height / 2 + 5, btn->label, XGUI_RGB(255, 255, 255));
}

static void button_on_mouse(XGui_Widget *base, int x, int y, XGui_MouseButton button, XGui_MouseAction action)
{
    XGui_Button *btn = (XGui_Button *)base;
    (void)x;
    (void)y;

    if (button != XGUI_BUTTON_LEFT)
        return;

    if (action == XGUI_MOUSE_PRESS)
        btn->state = XGUI_BUTTON_STATE_PRESSED;
    else
    {
        btn->state = XGUI_BUTTON_STATE_HOVER;
        if (btn->on_click)
            btn->on_click(btn->userdata);
    }
}

static void button_on_mouse_move(XGui_Widget *base, int x, int y)
{
    XGui_Button *btn = (XGui_Button *)base;

    if (widget_contains(base, x, y))
    {
        if (btn->state != XGUI_BUTTON_STATE_PRESSED)
            btn->state = XGUI_BUTTON_STATE_HOVER;
    }
    else
        btn->state = XGUI_BUTTON_STATE_NORMAL;
}

void button_init(XGui_Button *btn, int x, int y, int width, int height, const char *label, void (*on_click)(void *), void *userdata)
{
    btn->base.x = x;
    btn->base.y = y;
    btn->base.width = width;
    btn->base.height = height;
    btn->base.on_draw = button_draw;
    btn->base.on_mouse = button_on_mouse;
    btn->base.on_mouse_move = button_on_mouse_move;
    btn->state = XGUI_BUTTON_STATE_NORMAL;
    btn->on_click = on_click;
    btn->userdata = userdata;
    strncpy(btn->label, label, sizeof(btn->label) - 1);
    btn->label[sizeof(btn->label) - 1] = '\0';
}