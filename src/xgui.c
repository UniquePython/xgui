#include "xgui.h"

#include <stdio.h>

bool xgui_init(XGui *gui, int width, int height)
{
    gui->display = XOpenDisplay(NULL);
    if (!gui->display)
    {
        fprintf(stderr, "Cannot open display\n");
        return false;
    }

    gui->screen = DefaultScreen(gui->display);

    gui->window = XCreateSimpleWindow(
        gui->display,
        RootWindow(gui->display, gui->screen), /* parent window */
        0, 0,                                  /* x, y position */
        width, height,                         /* size */
        1,                                     /* border width */
        BlackPixel(gui->display, gui->screen), /* border color */
        WhitePixel(gui->display, gui->screen)  /* background color */
    );

    XSelectInput(gui->display, gui->window, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);

    XMapWindow(gui->display, gui->window);

    gui->gc = XCreateGC(gui->display, gui->window, 0, NULL);

    return true;
}

void xgui_shutdown(XGui *gui)
{
    XFreeGC(gui->display, gui->gc);
    XDestroyWindow(gui->display, gui->window);
    XCloseDisplay(gui->display);
}

void xgui_set_draw_callback(XGui *gui, XGui_DrawCallback cb, void *userdata)
{
    gui->on_draw = cb;
    gui->userdata = userdata;
}

void xgui_set_key_callback(XGui *gui, XGui_KeyCallback cb, void *userdata)
{
    gui->on_key = cb;
    gui->userdata = userdata;
}

void xgui_set_mouse_callback(XGui *gui, XGui_MouseCallback cb, void *userdata)
{
    gui->on_mouse = cb;
    gui->userdata = userdata;
}

void xgui_run(XGui *gui)
{
    XEvent event;
    gui->running = true;

    while (gui->running)
    {
        XNextEvent(gui->display, &event);
        switch (event.type)
        {
        case Expose:
            if (gui->on_draw)
                gui->on_draw(gui, gui->userdata);
            break;
        case KeyPress:
            if (gui->on_key)
                gui->on_key(gui, event.xkey.keycode, gui->userdata);
            break;
        case ButtonPress:
            if (gui->on_mouse)
                gui->on_mouse(gui, event.xbutton.x, event.xbutton.y, (XGui_MouseButton)event.xbutton.button,
                              XGUI_MOUSE_PRESS, gui->userdata);
            break;

        case ButtonRelease:
            if (gui->on_mouse)
                gui->on_mouse(gui, event.xbutton.x, event.xbutton.y, (XGui_MouseButton)event.xbutton.button,
                              XGUI_MOUSE_RELEASE, gui->userdata);
            break;
        }
    }
}

void xgui_quit(XGui *gui)
{
    gui->running = false;
}

static unsigned long color_to_pixel(XGui *gui, XGui_Color color)
{
    XColor xcolor;
    xcolor.red = color.r * 257;
    xcolor.green = color.g * 257;
    xcolor.blue = color.b * 257;
    xcolor.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(gui->display, DefaultColormap(gui->display, gui->screen), &xcolor);
    return xcolor.pixel;
}

void xgui_draw_rect(XGui *gui, int x, int y, int width, int height, XGui_Color color)
{
    XSetForeground(gui->display, gui->gc, color_to_pixel(gui, color));
    XFillRectangle(gui->display, gui->window, gui->gc, x, y, width, height);
}