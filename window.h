#ifndef XWINDOW_H
#define XWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include <vector>
#include <memory>
#include "queue.h"
#include "position.h"
#include "block.h"


class Window {
    public:
    struct RenderData {
        std::string p1Board;
        std::string p2Board;
        int p1Score;
        int p2Score;
        int p1Level;
        int p2Level;
        Block* p1Next;
        Block* p2Next;
        int ROWS;
        int COLS;
    };
    struct AudioData {
        Uint32 length;
        Uint32 remaining;
        Uint8 *buffer;
        Uint8 *currentBuffer;
        SDL_AudioSpec spec;
    };
    bool quit;
    Window(Queue *q = nullptr, bool audioEnabled = true, int width=1024, int height=768);  // Constructor; displays the window.
    ~Window();                              // Destructor; destroys the window.
    Window(const Window&) = delete;        // Disallow copy ctor.
    Window &operator=(const Window&) = delete; // Disallow copy assign.
    void darkMode(); // TODO figure this out
    void lightMode(); // TODO figure this out
    void startDisplay();
    void renderGame(RenderData *data);
    void drawGame();
    void playDrop();
    bool audioEnabled;
    private:
    void handleInput(SDL_Event &e);
    void setColor(char c);
    void loadAudio();
    static void audioCallback(void *userdata, Uint8 *stream, int len);
    std::vector<Position> getOffsets(char block);
    int width, height;
    SDL_Window *w;
    SDL_GLContext glc;
    RenderData* renderData;
    Queue *q;
    static vector<std::shared_ptr<AudioData>> audioData;
};

#endif // !XWINDOW_H