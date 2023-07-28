/**
 * This code makes extensive of use of https://wiki.libsdl.org/SDL2/APIByCategory.
 * Do not approach this code without first reading the SDL2 documentation. Please do not 
 * modify this file unless you are confident you know what you are doing.
*/

#include "window.h"

using namespace std;

Window::Window(int width, int height) : width{width}, height{height} {
    return;
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    glc = SDL_GL_CreateContext(w);
}

Window::~Window() {
    SDL_DestroyWindow(w);
    SDL_Quit();
}