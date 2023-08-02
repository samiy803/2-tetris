#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "queue.h"
#include "window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <atomic>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <memory>


class Game {
    const std::vector<std::string> COMMANDS = { "left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart", "hint", "rename", "bonus", "force" };
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    int highScore = 0;
    Player* currentPlayer;
    std::unique_ptr<Window> window;
    unsigned long turn_count;
    bool isGraphics;
    bool bonusEnabled;
    int seed;
    std::string file1, file2;
    int startLevel;
    std::istringstream ss;
    std::thread textThread;
    std::thread mainThread;
    std::atomic<bool> isRunning;

public:
    Game(bool isGraphics, int seed, std::string file1, std::string file2, int startLevel, bool bonusEnabled);
    void runMainLoop();
    void startGame();
    void restart();
    std::string parseCommand();
    void textInput();
    void renderGame();
    void printGame();
    void endGame();
    ~Game();
};

#endif // !GAME_H
