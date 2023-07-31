#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "blockFactory.h"
#include "level0Factory.h"
#include "level1Factory.h"
#include "level2Factory.h"
#include "level3Factory.h"
#include "level4Factory.h"

/**
 * Prime factorization of effects:
 * 1: none
 * 2: blind
 * 3: heavy
 * 5,7,11,13,17,19,23: force I, J, L, O, S, T, Z respectively
*/

class Player {
    friend class Game; // Game should have to access to Player's privates
    Board gameBoard;
    BlockFactory* blockFactory;
    int score;
    int level;
    int effect;
    int seed;
    string filename;
    public:
    Player(string filename = "", int score = 0, int level = 0, int effect = 1);
    void setBlind(bool blind);
    void setHeavy(bool heavy);
    void setForce(string block);
    void setLevel(int level);
    void clearRow();
    ~Player();
};

#endif // !PLAYER_H