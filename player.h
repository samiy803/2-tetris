#ifndef PLAYER_H
#define PLAYER_H

#include "blockFactory.h"
#include "board.h"
#include "level0Factory.h"
#include "level1Factory.h"
#include "level2Factory.h"
#include "level3Factory.h"
#include "level4Factory.h"
#include "queue.h"

/**
 * Prime factorization of effects:
 * 1: none
 * 2: heavy
 * 3: blind
 * 5,7,11,13,17,19,23: force I, J, L, O, S, T, Z respectively
 */

class Player {
    friend class Game; // Game should have to access to Player's privates
    Board gameBoard;
    std::unique_ptr<BlockFactory> blockFactory;
    int score;
    int score5turnsago;
    int level;
    int effect;
    int seed;
    std::string filename;
    std::unique_ptr<Queue> q;

public:
    Player(std::string filename = "", int score = 0, int level = 0, int effect = 1);
    void setBlind(bool blind);
    void setHeavy(bool heavy);
    void setForce(std::string block);
    void setLevel(int level);
    bool clearRow();
    ~Player();
};

#endif // !PLAYER_H
