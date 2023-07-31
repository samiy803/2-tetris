/**
 * This code makes extensive of use of https://wiki.libsdl.org/SDL2/APIByCategory.
 * Do not approach this code without first reading the SDL2 documentation. Please do not 
 * modify this file unless you are confident you know what you are doing.
*/

#include "window.h"
#include "game.h"

using namespace std;

vector<shared_ptr<Window::AudioData>> Window::audioData = {}; // Static member initialization


/**
 * Constructor for Window.
 * 
 * @param bonusEnabled Whether or not to enable bonus features.
 * @param width The width of the window. Defaults to 1024.
 * @param height The height of the window. Defaults to 768.
*/
Window::Window(bool bonusEnabled,int width, int height) :
    quit{false}, bonusEnabled{bonusEnabled}, width{width}, height{height}, renderData{nullptr}
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

/**
 * Destructor for Window. Frees all memory allocated by the window.
*/
Window::~Window() {
    quit = true;
    if (bonusEnabled) {
        for (auto &data : audioData) {
            SDL_FreeWAV(data->buffer);
        }
    }
    TTF_CloseFont(reg);
    TTF_CloseFont(smaller);
    SDL_GL_DeleteContext(glc);
    SDL_DestroyWindow(w);
    SDL_Quit();
}

/**
 * Opens the window and starts the SDL event loop. This function will not return until the window is closed.
*/
void Window::startDisplay() {
    w = nullptr;

    unsigned long init_flags = SDL_INIT_VIDEO;

    if (bonusEnabled) {
        init_flags |= SDL_INIT_AUDIO;
    }

    if (SDL_Init(init_flags) < 0) {
        throw "SDL could not initialize! SDL_Error: " + string(SDL_GetError());
    }
    w = SDL_CreateWindow("Biquadris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    if (w == nullptr) {
        throw "Window could not be created! SDL_Error: " + string(SDL_GetError());
    }

    // This does nothing on macOS? Possibly required on other platforms.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Max FPS is 1. -1 allows for vsync if the monitor supports it!!
    SDL_GL_SetSwapInterval(1);

    glc = SDL_GL_CreateContext(w);

    if (glc == nullptr) {
        throw "OpenGL context could not be created! SDL_Error: " + string(SDL_GetError());
    }

    // Grey background
    glClearColor(0.1, 0.1, 0.1, 1);

    // Window size, duh
    glViewport(0, 0, width, height);

    // add the menu buttons
    addButtons();

    // SDL event loop
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) {
                handleInput(e);
            }
        }
        if (renderData.get()) {
            drawGame();
            renderData.reset();
        }
    }
}

/**
 * Adds render data to the window. This function is called by the game when it wants to update the window.
*/
void Window::renderGame(shared_ptr<RenderData> data) {
    renderData = data;
}

/**
 * Draws the renderData to the window.
*/
void Window::drawGame() {
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawBoards();
    drawNext();
    drawBG();
    drawStats();
    drawMenu();

    SDL_GL_SwapWindow(w);

}

/**
 * Draws the next block for each player. This function is called by drawGame.
*/
void Window::drawNext() {
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
}

/**
 * Draws the game stats for each player and the highscore. This function is called by drawGame.
*/
void Window::drawStats() {
    float temp = (width - boardWidth*width - borderX*width);
    drawText(reg, "Player 1", borderX*width/2, (boardHeight + 2*borderY)*height/2);
    drawText(smaller, "Level   " + to_string(renderData->p1Level), borderX*width/2, (boardHeight + 3.5*borderY)*height/2);
    drawText(smaller, "Score  " + to_string(renderData->p1Score), borderX*width/2, (boardHeight + 4.5*borderY)*height/2);

    drawText(reg, "Player 2", (borderX + boardWidth)*width/2 + temp, (boardHeight + 2*borderY)*height/2);
    drawText(smaller, "Level   " + to_string(renderData->p2Level), (borderX + boardWidth)*width/2 + temp, (boardHeight + 3.5*borderY)*height/2);
    drawText(smaller, "Score  " + to_string(renderData->p2Score), (borderX + boardWidth)*width/2 + temp, (boardHeight + 4.5*borderY)*height/2);
    drawText(reg, "Highscore  " + to_string(renderData->highScore), (borderX + boardWidth)*width/2, height - borderY*height);
}

/**
 * Sets the color for OpenGL to draw the blocks. This function is called by drawGame.
*/
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

/**
 * Input handler for the window. This function is called by the main window event loop.
*/
void Window::handleInput(SDL_Event &e) {
    if (!bonusEnabled) return;
    if (!q) return;
    if (e.type == SDL_KEYDOWN )  {
        // https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html
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
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        // x1 = 435, y1 = 175, x2 = 590, y2 = 213
        int x, y;
        SDL_GetMouseState(&x, &y);
        cout << x << " " << y << endl;
        if (x >= 435 && x <= 590 && y >= 175 && y <= 213) {
            q->push("restart");
        }
    }
    cout << e.type << endl;
}

/**
 * Draws the game boards. This function is called by drawGame.
*/
void Window::drawBoards() {
    // Draw both boards
    for (int i = 0; i < renderData->ROWS; i++) {
        for (int j = 0; j < renderData->COLS; j++) {
            // Player 1
            char curChar = renderData->p1Board[i * renderData->COLS + j];
            setColor(curChar);
            glBegin(GL_QUADS);
                glVertex2f(-1 + borderX + j * blockWidth, 1 - borderY -i * blockHeight);
                glVertex2f(-1 + borderX + (j + 1) * blockWidth, 1 - borderY - i * blockHeight);
                glVertex2f(-1 + borderX + (j + 1) * blockWidth, 1 - borderY - (i + 1) * blockHeight);
                glVertex2f(-1 + borderX + j * blockWidth, 1 - borderY - (i + 1) * blockHeight);
            glEnd();

            // Player 2
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
}

/**
 * Loads the audio files. This function is called by the constructor.
*/
void Window::loadAudio() {
    shared_ptr<Window::AudioData> drop(new Window::AudioData());
    if (SDL_LoadWAV("audio/drop.wav", &drop->spec, &drop->buffer, &drop->length) == NULL) {
        bonusEnabled = false;
        std::cout << "Error loading drop.wav" << std::endl;
        return;
    }

    drop->spec.callback = Window::audioCallback;
    drop->spec.userdata = drop.get();
    drop->currentBuffer = drop->buffer;
    drop->remaining = drop->length;

    audioData.push_back(drop);
}

/**
 * Callback function for audio. This function is called by SDL when it needs more audio data.
 * @param userdata The audio data to play
 * @param stream The audio stream to copy to
 * @param len How much data to copy
 * @see https://wiki.libsdl.org/SDL2/SDL_AudioSpec#callback
*/
void Window::audioCallback(void *userdata, Uint8 *stream, int len) {
    AudioData *audio = (AudioData *) userdata; // Cast to AudioData

    if (audio->remaining == 0) {
        return; // No more samples
    }
    // Don't copy more than we have left
    len = (len > audio->remaining ? audio->remaining : len);

    // SDL_memcpy is the same as normal memcpy, but
    // adds some SDL ~sauce~ to make it platform independent
    SDL_memcpy(stream, audio->currentBuffer, len);
    audio->currentBuffer += len; // Advance the buffer
    audio->remaining -= len; // Decrease the number of samples left
}

/**
 * Plays the drop sound.
*/
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

/**
 * Draws the background and grid. This function is called by drawGame.
*/
void Window::drawBG() {
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

/**
 * Converts the string to an SDL surface, then to an OpenGL texture, then draws it.
 * @param font The font to use
 * @param text The text to draw
 * @param x The x coordinate to draw at
 * @param y The y coordinate to draw at
 * @param center Whether to center the text at the given coordinates. If false, the text will be drawn at the top left corner, otherwise it will be centered. Defaults to false.
*/
void Window::drawText(TTF_Font *font, string text, int x, int y, bool center) {
    if (!font) return;

    // Enter 2D mode for texturing
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)width, (GLdouble)height, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
    // I swear normalized device coordinates are the worst thing ever. Possibly worse than
    // the imperial system. No, nevermind, nothing is worse than the imperial system.


    // Blend the alpha channel of the text into the background
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Make a texture from the text
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // https://wiki.libsdl.org/SDL2_ttf/TTF_RenderText_Blended
    SDL_Surface *sFont = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255, 0});

    // SDL has some very strange behavior with the pitch
    // This tells OpenGL to use the correct pitch
    // More info: https://stackoverflow.com/a/25772201
    glPixelStorei(GL_UNPACK_ROW_LENGTH, sFont->pitch / sFont->format->BytesPerPixel);


    // Set texture parameters to avoid artifacts when scaling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Upload the texture to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

    // Specify the texture coordinates
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0,0); glVertex2f(x - center*sFont->w/2, y - center*sFont->h/2);
        glTexCoord2f(1,0); glVertex2f(x + sFont->w - center*sFont->w/2, y - center*sFont->h/2);
        glTexCoord2f(1,1); glVertex2f(x + sFont->w - center*sFont->w/2, y + sFont->h - center*sFont->h/2);
        glTexCoord2f(0,1); glVertex2f(x - center*sFont->w/2, y + sFont->h - center*sFont->h/2);
    }
    glEnd();

    // Exit 2D mode
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();

    // We're done with blending
    glDisable(GL_BLEND);
    
    // Free the texture and surface
    glDeleteTextures(1, &texture);
    SDL_FreeSurface(sFont);

}

/**
 * Set the queue to use to add commands from the window. Should be used by the game to switch between players.
 * @param q The queue to use
*/
void Window::setQueue(Queue *q) {
    this->q = q;
}

/**
 * Draw the buttons in the center of the screen.
*/
void Window::drawMenu() {
    for (auto button : buttons) {
        setColor(' ');

        // Draw the buttons
        glBegin(GL_QUADS);
        {
            glVertex2f(button.x, -button.y);
            glVertex2f(button.x + button.w, -button.y);
            glVertex2f(button.x + button.w, -button.y - button.h);
            glVertex2f(button.x, -button.y - button.h);
        }
        glEnd();

        setColor('*');

        drawText(smaller, button.text.at(button.state), ((button.x + button.w/2)/2 + 0.5)*width, ((button.y + button.h/2)/2 + 0.5)*height, true);
    }

}

void Window::addButtons() {
    buttons.push_back({-0.1, -0.8, 0.2, 0.1, {"lvl up"}});
    buttons.push_back({-0.1, -0.65, 0.2, 0.1, {"lvl dwn"}});
    buttons.push_back({-0.1, -0.5, 0.2, 0.1, {"Restart", "Restart"}});
    buttons.push_back({-0.1, -0.5, 0.2, 0.1, {"LIGHT", "DARK", "ZEN"}});
    buttons.push_back({-0.1, 0.2, 0.2, 0.1, {"Quit", "Quit?"}});
}