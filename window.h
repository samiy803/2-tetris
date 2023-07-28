#ifndef XWINDOW_H
#define XWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include "queue.h"


class Window {
    public:
    struct RenderData {
        std::string p1Board;
        std::string p2Board;
        int p1Score;
        int p2Score;
        int p1Level;
        int p2Level;
        std::string p1Next;
        std::string p2Next;
        int ROWS;
        int COLS;
    };
    bool quit;
    Window(Queue *q = nullptr, int width=1024, int height=680);  // Constructor; displays the window.
    ~Window();                              // Destructor; destroys the window.
    Window(const Window&) = delete;        // Disallow copy ctor.
    Window &operator=(const Window&) = delete; // Disallow copy assign.
    void darkMode(); // TODO figure this out
    void lightMode(); // TODO figure this out
    void startDisplay();
    void renderGame(RenderData *data);
    void drawGame();
    private:
    void handleInput(SDL_Event &e);
    int width, height;
    SDL_Window *w;
    SDL_GLContext glc;
    RenderData* renderData;
    Queue *q;
};

#endif // !XWINDOW_H