#ifndef GAME_H
#define GAME_H


#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <atomic>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "player.h"
#include "window.h"
#include "queue.h"

using std::string;
using std::istringstream;
using std::thread;

class Game {
    const vector<string> COMMANDS = {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart", "hint", "rename", "bonus", "force"};
    const vector<string> PROHIB = {"restart", "hint", "norandom", "random"};
    Player* player1;
    Player* player2;
    int highScore = 0;
    Player* currentPlayer;
    Window* window;
    unsigned long turn_count;
    bool isGraphics;
    bool bonusEnabled;
    int seed;
    string file1, file2;
    int startLevel;
    istringstream ss;
    thread textThread;
    thread mainThread;
    std::atomic<bool> isRunning;
    public:
    Game(bool isGraphics, int seed, string file1, string file2, int startLevel, bool bonusEnabled);
    void runMainLoop();
    void startGame();
    void restart();
    string parseCommand();
    void textInput();
    void renderGame();
    void printGame();
    void endGame();
    ~Game();
};


#endif // !GAME_H