#include "xgui.h"
#include <stdio.h>

int main(void)
{
    XGui gui;
    if (!xgui_init(&gui, 800, 600))
        return 1;

    XEvent event;
    int running = 1;

    while (running)
    {
        XNextEvent(gui.display, &event);
        switch (event.type)
        {
        case KeyPress:
            running = 0;
            break;
        }
    }

    xgui_shutdown(&gui);
    return 0;
}