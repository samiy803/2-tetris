/**
 * This code makes extensive of use of https://wiki.libsdl.org/SDL2/APIByCategory.
 * Do not approach this code without first reading the SDL2 documentation. Please do not 
 * modify this file unless you are confident you know what you are doing.
*/

#include "window.h"
#include "game.h"

using namespace std;

Window::Window(Queue *q, int width, int height) : quit{false}, width{width}, height{height}, renderData{nullptr}, q{q} {}

Window::~Window() {
    quit = true;
    SDL_GL_DeleteContext(glc);
    SDL_DestroyWindow(w);
    SDL_Quit();
}

void Window::startDisplay() {
    w = nullptr;
    unsigned int window_flags = SDL_WINDOW_OPENGL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw "SDL could not initialize! SDL_Error: " + string(SDL_GetError());
    }
    w = SDL_CreateWindow("Biquadris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, window_flags);

    if (w == nullptr) {
        throw "Window could not be created! SDL_Error: " + string(SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

    SDL_GL_SetSwapInterval(1);

    glc = SDL_GL_CreateContext(w);

    if (glc == nullptr) {
        throw "OpenGL context could not be created! SDL_Error: " + string(SDL_GetError());
    }

    glClearColor(0.2, 0.2, 0.2, 1);
    glViewport(0, 0, width, height);

    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                handleInput(e);
            }
        }
        if (renderData) {
            drawGame();
            delete renderData;
            renderData = nullptr;
        }
    }
}

void Window::renderGame(RenderData *data) {
    renderData = data;
}
void Window::drawGame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // renderData->p1Board is a string of length COLS * ROWS

    float blockWidth = 0.068359375;
    float blockHeight = 0.068359375*width/height;
    float boardWidth = blockWidth * renderData->COLS;
    float boardHeight = blockHeight * renderData->ROWS;
    float borderX = (2 - 2*boardWidth - 0.2)/4.0;
    float borderY = 0.05 * width/height;

    for (int i = 0; i < renderData->ROWS; i++) {
        for (int j = 0; j < renderData->COLS; j++) {
            char curChar = renderData->p1Board[i * renderData->COLS + j];

            // Draw player 1 board
            setColor(curChar);
            glBegin(GL_QUADS);
            glVertex2f(-1 + borderX + j * blockWidth, 1 - borderY -i * blockHeight);
            glVertex2f(-1 + borderX + (j + 1) * blockWidth, 1 - borderY - i * blockHeight);
            glVertex2f(-1 + borderX + (j + 1) * blockWidth, 1 - borderY - (i + 1) * blockHeight);
            glVertex2f(-1 + borderX + j * blockWidth, 1 - borderY - (i + 1) * blockHeight);
            glEnd();

            // Draw player 2 board
            curChar = renderData->p2Board[i * renderData->COLS + j];
            setColor(curChar);
            glBegin(GL_QUADS);
            glVertex2f(1 - borderX - (renderData->COLS - j) * blockWidth, 1 - borderY - i * blockHeight);
            glVertex2f(1 - borderX - (renderData->COLS - (j + 1)) * blockWidth, 1 - borderY - i * blockHeight);
            glVertex2f(1 - borderX - (renderData->COLS - (j + 1)) * blockWidth, 1 - borderY - (i + 1) * blockHeight);
            glVertex2f(1 - borderX - (renderData->COLS - j) * blockWidth, 1 - borderY - (i + 1) * blockHeight);
            glEnd();
        }
    }

    if (renderData->p1Next) {
        // Draw player 1 next block
        for (auto offset : renderData->p1Next->getOffsets()) {
            setColor(renderData->p1Next->c);
            glBegin(GL_QUADS);
            glVertex2f(-1 + borderX + (1 + offset.x) * blockWidth, 1 - borderY - (3 + offset.y) * blockHeight - boardHeight);
            glVertex2f(-1 + borderX + (2 + offset.x) * blockWidth, 1 - borderY - (3 + offset.y) * blockHeight - boardHeight);
            glVertex2f(-1 + borderX + (2 + offset.x) * blockWidth, 1 - borderY - (2 + offset.y) * blockHeight - boardHeight);
            glVertex2f(-1 + borderX + (1 + offset.x) * blockWidth, 1 - borderY - (2 + offset.y) * blockHeight - boardHeight);
            glEnd();
        }
    }

    if (renderData->p2Next) {
        // Draw player 2 next block
        for (auto offset : renderData->p2Next->getOffsets()) {
            setColor(renderData->p2Next->c);
            glBegin(GL_QUADS);
            glVertex2f(1 - borderX - (renderData->COLS - 1 + offset.x) * blockWidth, 1 - borderY - (3 + offset.y) * blockHeight - boardHeight);
            glVertex2f(1 - borderX - (renderData->COLS - 2 + offset.x) * blockWidth, 1 - borderY - (3 + offset.y) * blockHeight - boardHeight);
            glVertex2f(1 - borderX - (renderData->COLS - 2 + offset.x) * blockWidth, 1 - borderY - (2 + offset.y) * blockHeight - boardHeight);
            glVertex2f(1 - borderX - (renderData->COLS - 1 + offset.x) * blockWidth, 1 - borderY - (2 + offset.y) * blockHeight - boardHeight);
            glEnd();
        }
    }

    SDL_GL_SwapWindow(w);

}


void Window::setColor(char curChar) {
    if (curChar == 'I') {
        glColor3f(0, 1, 1);
    }
    else if (curChar == 'J') {
        glColor3f(0, 0, 1);
    }
    else if (curChar == 'L') {
        glColor3f(1, 0.5, 0);
    }
    else if (curChar == 'O') {
        glColor3f(1, 1, 0);
    }
    else if (curChar == 'S') {
        glColor3f(0, 1, 0);
    }
    else if (curChar == 'Z') {
        glColor3f(1, 0, 0);
    }
    else if (curChar == 'T') {
        glColor3f(0.5, 0, 1);
    }
    else if (curChar == '*') {
        glColor3f(1, 1, 1);
    }
    else {
        glColor3f(0,0,0);
    }
}

void Window::handleInput(SDL_Event &e) {
    if (!q) return;
    if (e.type != SDL_KEYDOWN) return;
    if (e.key.keysym.sym == SDLK_DOWN) {
        q->push("down");
    }
    else if (e.key.keysym.sym == SDLK_RIGHT) {
        q->push("right");
    }
    else if (e.key.keysym.sym == SDLK_LEFT) {
        q->push("left");
    }
    else if (e.key.keysym.sym == SDLK_UP) {
        q->push("clockwise");
    }
    else if (e.key.keysym.sym == SDLK_SPACE) {
        q->push("drop");
    }
}