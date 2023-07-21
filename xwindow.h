#ifndef XWINDOW_H
#define XWINDOW_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "game.h"

typedef unsigned long Pixel;

typedef XImage Image;

class XWindow {
    Display *d;
    Drawable w;
    GC gc;
    enum color {Black = 0, White, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};
    Pixel colours[10];
    int width, height;

    public:
    XWindow(int width=500, int height=500);  // Constructor; displays the window.
    ~XWindow();                              // Destructor; destroys the window.
    XWindow(const XWindow&) = delete;        // Disallow copy ctor.
    XWindow &operator=(const XWindow&) = delete; // Disallow copy assign.
    void darkMode(); // TODO figure this out
    void drawGame(Game game);
};

#endif // !XWINDOW_H