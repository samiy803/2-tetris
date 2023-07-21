#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "blockFactory.h"

class Player {
    Board gameboard;
    BlockFactory* blockFactory;
    int score;
    int level;
    int effect;
    public:
    Player();
    void setBlind();
    void setHeavy();
    void setForce(string block);
};

#endif // !PLAYER_H