#ifndef XWINDOW_H
#define XWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
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
        int highScore;
    };
    struct AudioData {
        Uint32 length;
        Uint32 remaining;
        Uint8 *buffer;
        Uint8 *currentBuffer;
        SDL_AudioSpec spec;
    };
    struct Button {
        int x,y,w,h,state;
        std::string text;
        Button(int x, int y, int w, int h, std::string text) : x(x), y(y), w(w), h(h), state(0), text(text) {}
    };
    bool quit;
    bool bonusEnabled;
    Window(bool bonusEnabled = false, int width=1024, int height=768);  // Constructor; displays the window.
    ~Window();                                                          // Destructor; destroys the window.
    Window(const Window&) = delete;                                     // Disallow copy ctor.
    Window &operator=(const Window&) = delete;                          // Disallow copy assign.
    void darkMode(); // TODO figure this out
    void lightMode(); // TODO figure this out
    void startDisplay();
    void renderGame(std::shared_ptr<RenderData> renderData);
    void drawGame();
    void playDrop();
    void setQueue(Queue *q);
    private:
    const float blockWidth = 0.068359375;
    // These need to be defined here because they rely on COLS and ROWS
    #define blockHeight (blockWidth * width / height)
    #define boardWidth (blockWidth * renderData->COLS)
    #define boardHeight (blockHeight * renderData->ROWS)
    #define borderX ((2 - 2*boardWidth - 0.2)/4.0)
    #define borderY (0.05 * width / height)
    int width, height;
    SDL_Window *w;
    SDL_GLContext glc;
    TTF_Font *reg;
    TTF_Font *smaller;
    std::shared_ptr<RenderData> renderData;
    Queue *q;
    static vector<std::shared_ptr<AudioData>> audioData;
    vector<Button> buttons;

    // Drawing functions
    void drawBG();
    void drawText(TTF_Font *font, std::string text, int x, int y, bool center = false);
    void drawMenu();
    void drawNext();
    void drawStats();
    void drawBoards();

    // Helper functions
    void handleInput(SDL_Event &e);
    void setColor(char c);
    void loadAudio();
    static void audioCallback(void *userdata, Uint8 *stream, int len);
    std::vector<Position> getOffsets(char block);
};

#endif // !XWINDOW_H