#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "xwindow.h"
#include <string>

using std::string;

class Game {
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    XWindow* window;
    unsigned long turn_count;
    bool isGraphics;
    int seed;
    string file1, file2;
    int startLevel;
    public:
    Game(bool isGraphics, int seed, string file1, string file2, int startLevel);
    void runMainLoop();
    void restart();
};


#endif // !GAME_H