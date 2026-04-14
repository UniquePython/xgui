#pragma once

#include "widget.h"
#include "draw.h"

typedef enum
{
    XGUI_BUTTON_STATE_NORMAL,
    XGUI_BUTTON_STATE_HOVER,
    XGUI_BUTTON_STATE_PRESSED
} XGui_ButtonState;

typedef struct
{
    XGui_Widget base;
    char label[64];
    XGui_ButtonState state;
    void (*on_click)(void *userdata);
    void *userdata;
} XGui_Button;

void button_init(XGui_Button *btn, int x, int y, int width, int height, const char *label, void (*on_click)(void *), void *userdata);