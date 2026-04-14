#include "xgui.h"
#include <stdio.h>

int main(void)
{
    XGui gui;
    if (!xgui_init(&gui, 900, 600))
        return 1;
    printf("Display opened successfully\n");
    xgui_shutdown(&gui);
    return 0;
}