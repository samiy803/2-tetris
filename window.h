#ifndef XWINDOW_H
#define XWINDOW_H

#include "block.h"
#include "position.h"
#include "queue.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <string>
#include <vector>
/**
 * @brief The Window class is responsible for displaying the game.
 * 
 * Note to marker: A lot of raw pointers are used here because SDL is a C library and doesn't
 *  support smart pointers. It does not make sense to use smart pointers and then have to
 * cast them to raw pointers to pass them to SDL functions. The only exception is the
 * unique_ptr<RenderData> in renderGame, which is passed to drawGame, which is a member
 * function of Window, so it is safe to use a smart pointer. Same for audio.
*/
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
        Uint8* buffer;
        Uint8* currentBuffer;
        SDL_AudioSpec spec;
    };
    struct Button {
        double x, y, w, h;
        int state;
        std::vector<std::string> text;
        Button(double x, double y, double w, double h, std::vector<std::string> text, int state = 0)
            : x { x }
            , y { y }
            , w { w }
            , h { h }
            , state { state }
            , text { text }
        {
        }
    };
    bool quit;
    bool bonusEnabled;
    Window(bool bonusEnabled = false, int width = 1024, int height = 820); // Constructor; displays the window.
    ~Window(); // Destructor; destroys the window.
    Window(const Window&) = delete; // Disallow copy ctor.
    Window& operator=(const Window&) = delete; // Disallow copy assign.
    void startDisplay();
    void renderGame(std::unique_ptr<RenderData> renderData);
    void drawGame();
    void playSound(int i);
    void setQueue(Queue* q);

private:
    const float blockWidth = 0.06180339887; // (1 - golden ratio)/10 because golden ratio is cool af
// These need to be defined here because they rely on COLS and ROWS
#define blockHeight (blockWidth * width / height)
#define boardWidth (blockWidth * renderData->COLS)
#define boardHeight (blockHeight * renderData->ROWS)
#define borderX ((2 - 2 * boardWidth - 0.2) / 4.0)
#define borderY (0.05 * width / height)
    int width, height;
    SDL_Window* w;
    SDL_GLContext glc;
    TTF_Font* reg;
    TTF_Font* smaller;
    std::unique_ptr<RenderData> renderData;
    Queue* q;
    static std::vector<std::unique_ptr<AudioData>> audioData;
    std::vector<Button> buttons;
    std::string current_theme;

    // Colors!!
    enum Color {
        BLACK = 0,
        WHITE,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        MAGENTA,
        CYAN,
        PURPLE,
        DARK_GREY,
        BROWN,
        NUM_COLORS
    };
    const float NORMAL_COLORS[NUM_COLORS][3] = {
        {0xef / 255.0, 0xef / 255.0, 0xf4 / 255.0}, // WHITE
        {0.0, 0.0, 0.0}, // BLACK
        {1.0, 0.0, 0.0}, // RED
        {0.0, 1.0, 0.0}, // GREEN
        {0.0, 0.0, 1.0}, // BLUE
        {1.0, 1.0, 0.0}, // YELLOW
        {1.0, 0.0, 1.0}, // MAGENTA
        {0.0, 1.0, 1.0}, // CYAN
        {0.5, 0.0, 0.5}, // PURPLE
        {210 / 255.0, 211 / 255.0, 219 / 255.0}, // DARK_GREY
        {160/255.0, 82/255.0, 45/255.0} // BROWN
    };

    const float DARKMODE_COLORS[NUM_COLORS][3] = {
        {0.0, 0.0, 0.0}, // BLACK
        {1.0, 1.0, 1.0}, // WHITE
        {1.0, 0.0, 0.0}, // RED
        {0.0, 1.0, 0.0}, // GREEN
        {0.0, 0.0, 1.0}, // BLUE
        {1.0, 1.0, 0.0}, // YELLOW
        {1.0, 0.0, 1.0}, // MAGENTA
        {0.0, 1.0, 1.0}, // CYAN
        {1, 0.75, 0.4}, // PURPLE
        {0.1, 0.1, 0.1}, // DARK_GREY
        {139 / 255.0, 69/255.0, 19/255.0 } // BROWN
    };

    const float DRACULA_COLORS[NUM_COLORS][3] = {
        {0x21 / 255.0, 0x22 / 255.0, 0x2c / 255.0}, // BLACK
        {248.0 / 255.0, 248.0 / 255.0, 242.0 / 255.0}, // WHITE
        {1.0, 85.0 / 255.0, 85.0 / 255.0}, // RED
        {80.0 / 255.0, 250.0 / 255.0, 123.0 / 255.0}, // GREEN
        {1.0, 184.0 / 255.0, 108.0 / 255.0}, // BLUE, but actually orange because I like it better
        {241.0 / 255.0, 250.0 / 255.0, 140.0 / 255.0}, // YELLOW
        {255.0 / 255.0, 121.0 / 255.0, 198.0 / 255.0}, // MAGENTA
        {139.0 / 255.0, 233.0 / 255.0, 253.0 / 255.0}, // CYAN
        {189.0 / 255.0, 147.0 / 255.0, 249.0 / 255.0}, // PURPLE
        {40.0 / 255.0, 42.0 / 255.0, 54.0 / 255.0}, // DARK_GREY, but not really
        {160/255.0, 82/255.0, 45/255.0} // BROWN
    };

    typedef float ColorArray[NUM_COLORS][3];

    // Drawing functions
    void drawBG();
    void drawText(TTF_Font* font, std::string text, int x, int y, bool center = false);
    void drawMenu();
    void drawNext();
    void drawStats();
    void drawBoards();

    // Helper functions
    void handleInput(SDL_Event& e);
    void setColor(char c);
    void loadAudio();
    static void audioCallback(void* userdata, Uint8* stream, int len);
    void addButtons();
    std::vector<Position> getOffsets(char block);
    const ColorArray* getColorArray();
};

#endif // !XWINDOW_H
