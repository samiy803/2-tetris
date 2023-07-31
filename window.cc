/**
 * This code makes extensive of use of https://wiki.libsdl.org/SDL2/APIByCategory.
 * Do not approach this code without first reading the SDL2 documentation. Please do not 
 * modify this file unless you are confident you know what you are doing.
*/

#include "window.h"
#include "game.h"

using namespace std;

vector<shared_ptr<Window::AudioData>> Window::audioData = {};

Window::Window(Queue *q, bool bonusEnabled,int width, int height) :
    quit{false}, width{width}, height{height},
    renderData{nullptr}, q{q}, bonusEnabled{bonusEnabled}
{
    if (bonusEnabled) {
        loadAudio();
    }
    if (TTF_Init() < 0) {
        throw "TTF_Init failed to initialize";
    }
    reg = TTF_OpenFont("Tetris.ttf", 28);
    TTF_SetFontStyle(reg, TTF_STYLE_NORMAL);
    smaller = TTF_OpenFont("Tetris.ttf", 22);
    if (reg == nullptr || smaller == nullptr) {
        throw "TTF_OpenFont failed to load Sans.ttf";
    }
}

Window::~Window() {
    quit = true;
    if (bonusEnabled) {
        for (auto &data : audioData) {
            SDL_FreeWAV(data->buffer);
        }
    }
    TTF_CloseFont(reg);
    SDL_GL_DeleteContext(glc);
    SDL_DestroyWindow(w);
    SDL_Quit();
}

void Window::startDisplay() {
    w = nullptr;
    unsigned int window_flags = SDL_WINDOW_OPENGL;

    unsigned long init_flags = SDL_INIT_VIDEO;

    if (bonusEnabled) {
        init_flags |= SDL_INIT_AUDIO;
    }

    if (SDL_Init(init_flags) < 0) {
        throw "SDL could not initialize! SDL_Error: " + string(SDL_GetError());
    }
    w = SDL_CreateWindow("Biquadris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, window_flags);

    if (w == nullptr) {
        throw "Window could not be created! SDL_Error: " + string(SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

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
                handleInput(e, bonusEnabled);
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
            glVertex2f(-1 + borderX + (offset.x + renderData->COLS - 2.5) * blockWidth, 1 - borderY - (2.5 + offset.y) * blockHeight - boardHeight);
            glVertex2f(-1 + borderX + (offset.x + renderData->COLS - 1.5) * blockWidth, 1 - borderY - (2.5 + offset.y) * blockHeight - boardHeight);
            glVertex2f(-1 + borderX + (offset.x + renderData->COLS - 1.5) * blockWidth, 1 - borderY - (1.5 + offset.y) * blockHeight - boardHeight);
            glVertex2f(-1 + borderX + (offset.x + renderData->COLS - 2.5) * blockWidth, 1 - borderY - (1.5 + offset.y) * blockHeight - boardHeight);
            glEnd();
        }
    }

    if (renderData->p2Next) {
        // Draw player 2 next block
        for (auto offset : renderData->p2Next->getOffsets()) {
            setColor(renderData->p2Next->c);
            glBegin(GL_QUADS);
            glVertex2f(borderX + (renderData->COLS - 1 + offset.x) * blockWidth, 1 - borderY - (2.5 + offset.y) * blockHeight - boardHeight);
            glVertex2f(borderX + (renderData->COLS - 2 + offset.x) * blockWidth, 1 - borderY - (2.5 + offset.y) * blockHeight - boardHeight);
            glVertex2f(borderX + (renderData->COLS - 2 + offset.x) * blockWidth, 1 - borderY - (1.5 + offset.y) * blockHeight - boardHeight);
            glVertex2f(borderX + (renderData->COLS - 1 + offset.x) * blockWidth, 1 - borderY - (1.5 + offset.y) * blockHeight - boardHeight);
            glEnd();
        }
    }

    drawBG();

    float temp = (width - boardWidth*width - borderX*width);
    drawText(reg, "Player 1", borderX*width/2, (boardHeight + 2*borderY)*height/2);
    drawText(smaller, "Level   " + to_string(renderData->p1Level), borderX*width/2, (boardHeight + 3.5*borderY)*height/2);
    drawText(smaller, "Score  " + to_string(renderData->p1Score), borderX*width/2, (boardHeight + 4.5*borderY)*height/2);

    drawText(reg, "Player 2", (borderX + boardWidth)*width/2 + temp, (boardHeight + 2*borderY)*height/2);
    drawText(smaller, "Level   " + to_string(renderData->p2Level), (borderX + boardWidth)*width/2 + temp, (boardHeight + 3.5*borderY)*height/2);
    drawText(smaller, "Score  " + to_string(renderData->p2Score), (borderX + boardWidth)*width/2 + temp, (boardHeight + 4.5*borderY)*height/2);

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
    else if (curChar == 'i') {
        glColor3f(0, 0.5, 0.5);
    }
    else if (curChar == 'j') {
        glColor3f(0, 0, 0.5);
    }
    else if (curChar == 'l') {
        glColor3f(0.5, 0.25, 0);
    }
    else if (curChar == 'o') {
        glColor3f(0.5, 0.5, 0);
    }
    else if (curChar == 's') {
        glColor3f(0, 0.5, 0);
    }
    else if (curChar == 'z') {
        glColor3f(0.5, 0, 0);
    }
    else if (curChar == 't') {
        glColor3f(0.25, 0, 0.5);
    }
    else {
        glColor3f(0,0,0);
    }
}

void Window::handleInput(SDL_Event &e, bool bonusEnabled) {
    if (!bonusEnabled) return;
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
    else if(e.key.keysym.sym == SDLK_a) {
        q->push("counterclockwise");
    }
    else if (e.key.keysym.sym == SDLK_d) {
        q->push("clockwise");
    }
    else if (e.key.keysym.sym == SDLK_SPACE) {
        q->push("drop");
    }
    else if (e.key.keysym.sym == SDLK_UP) {
        q->push("clockwise");
    }
}

void Window::loadAudio() {
    shared_ptr<Window::AudioData> drop(new Window::AudioData());
    if (SDL_LoadWAV("audio/drop.wav", &drop->spec, &drop->buffer, &drop->length) == NULL) {
        bonusEnabled = false;
        std::cout << "Error loading drop.wav" << std::endl;
    }

    drop->spec.callback = Window::audioCallback;
    drop->spec.userdata = drop.get();
    drop->currentBuffer = drop->buffer;
    drop->remaining = drop->length;

    audioData.push_back(drop);
}

// Why so complicated?
// https://wiki.libsdl.org/SDL2/SDL_AudioSpec#callback
void Window::audioCallback(void *userdata, Uint8 *stream, int len) {
    AudioData *audio = (AudioData *) userdata;
    if (audio->remaining == 0) {
        return;
    }
    // Don't copy more than we have left
    len = (len > audio->remaining ? audio->remaining : len);
    SDL_memcpy(stream, audio->currentBuffer, len);
    audio->currentBuffer += len;
    audio->remaining -= len;
}

void Window::playDrop() {
    if (!bonusEnabled) return;
    if (SDL_OpenAudio(&audioData[0]->spec, NULL) < 0) {
        bonusEnabled = false;
        std::cout << "Error opening audio device" << std::endl;
        return;
    }

    SDL_PauseAudio(0);

    while (audioData[0]->remaining > 0) {
        SDL_Delay(10);
    }

    SDL_CloseAudio();

    // Reset the buffer
    audioData[0]->currentBuffer = audioData[0]->buffer;
    audioData[0]->remaining = audioData[0]->length;
}

void Window::drawBG() {
    float blockWidth = 0.068359375;
    float blockHeight = 0.068359375*width/height;
    float boardWidth = blockWidth * renderData->COLS;
    float boardHeight = blockHeight * renderData->ROWS;
    float borderX = (2 - 2*boardWidth - 0.2)/4.0;
    float borderY = 0.05 * width/height;

    // Draw grid for player 1
    setColor('*');
    glBegin(GL_LINES);
    for (int i = 0; i <= renderData->COLS; i++) {
        glVertex2f(-1 + borderX + i * blockWidth, 1 - borderY);
        glVertex2f(-1 + borderX + i * blockWidth, 1 - borderY - boardHeight);
    }
    for (int i = 0; i <= renderData->ROWS; i++) {
        glVertex2f(-1 + borderX, 1 - borderY - i * blockHeight);
        glVertex2f(-1 + borderX + boardWidth, 1 - borderY - i * blockHeight);
    }

    // Draw grid for player 2
    
    for (int i = 0; i <= renderData->COLS; i++) {
        glVertex2f(1 - borderX - i * blockWidth, 1 - borderY);
        glVertex2f(1 - borderX - i * blockWidth, 1 - borderY - boardHeight);
    }

    for (int i = 0; i <= renderData->ROWS; i++) {
        glVertex2f(1 - borderX, 1 - borderY - i * blockHeight);
        glVertex2f(1 - borderX - boardWidth, 1 - borderY - i * blockHeight);
    }

    glEnd();
}

void Window::drawText(TTF_Font *reg, string text, int x, int y, bool center) {
    if (!reg) return;

    glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0.0, (GLdouble)width, (GLdouble)height, 0.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    SDL_Surface *sFont = TTF_RenderText_Blended(reg, text.c_str(), {255, 255, 255, 0});

    glPixelStorei(GL_UNPACK_ROW_LENGTH, sFont->pitch / sFont->format->BytesPerPixel);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0,0); glVertex2f(x - center*sFont->w/2, y - center*sFont->h/2);
        glTexCoord2f(1,0); glVertex2f(x + sFont->w - center*sFont->w/2, y - center*sFont->h/2);
        glTexCoord2f(1,1); glVertex2f(x + sFont->w - center*sFont->w/2, y + sFont->h - center*sFont->h/2);
        glTexCoord2f(0,1); glVertex2f(x - center*sFont->w/2, y + sFont->h - center*sFont->h/2);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopAttrib();
    

    glDeleteTextures(1, &texture);
    SDL_FreeSurface(sFont);

}

void Window::setQueue(Queue *q) {
    this->q = q;
}