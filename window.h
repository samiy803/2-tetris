#ifndef XWINDOW_H
#define XWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include <thread>


class Window {
    friend class Game;
    int width, height;
    SDL_Window *w;
    SDL_GLContext glc;

    public:
    Window(int width=500, int height=500);  // Constructor; displays the window.
    ~Window();                              // Destructor; destroys the window.
    Window(const Window&) = delete;        // Disallow copy ctor.
    Window &operator=(const Window&) = delete; // Disallow copy assign.
    void darkMode(); // TODO figure this out
};

#endif // !XWINDOW_H