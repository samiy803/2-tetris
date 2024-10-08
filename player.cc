#include "player.h"
#include "queue.h"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

Player::Player(string filename, int score, int level, int effect)
    : score { score }
    , level { level }
    , effect { effect }
    , filename { filename }
{
    BlockFactory* bf;
    switch (level) {
    case 0:
        bf = new Level0Factory(filename);
        break;
    case 1:
        bf = new Level1Factory();
        break;
    case 2:
        bf = new Level2Factory();
        break;
    case 3:
        bf = new Level3Factory();
        break;
    case 4:
        bf = new Level4Factory();
        break;
    default:
        throw "Invalid level";
        break;
    }
    score = 0;
    blockFactory = unique_ptr<BlockFactory>(bf);
    q = make_unique<Queue>();
}

void Player::setBlind(bool blind)
{
    if (blind && effect % 2)
        effect *= 2;
    else if (!blind && !(effect % 2))
        effect /= 2;
}

void Player::setHeavy(bool heavy)
{
    if (heavy && effect % 3)
        effect *= 3;
    else if (!heavy && !(effect % 3))
        effect /= 3;
}

void Player::setForce(string block)
{
    int prime;
    switch (block[0]) {
    case 'I':
        prime = 5;
        break;
    case 'J':
        prime = 7;
        break;
    case 'L':
        prime = 11;
        break;
    case 'O':
        prime = 13;
        break;
    case 'S':
        prime = 17;
        break;
    case 'T':
        prime = 19;
        break;
    case 'Z':
        prime = 23;
        break;
    default:
        prime = 1;
        break;
    }
    if (effect % prime)
        effect *= prime;
    else
        effect /= prime;
}

bool Player::setLevel(int level)
{
    if (level < 0 || level > 4)
        return false;
    this->level = level;
    gameBoard.level = level;
    BlockFactory *bf;
    switch (level) {
    case 0:
        bf = new Level0Factory(filename);
        break;
    case 1:
        bf = new Level1Factory();
        break;
    case 2:
        bf = new Level2Factory();
        break;
    case 3:
        bf = new Level3Factory();
        break;
    case 4:
        bf = new Level4Factory();
        score5turnsago = score;
        break;
    default:
        throw "Invalid level";
        break;
    }
    blockFactory = unique_ptr<BlockFactory>(bf);
    return true;
}

int Player::clearRow()
{
    string board = gameBoard.toString(false);

    vector<int> rows;

    for (int i = 0; i < Board::ROWS; ++i) {
        for (int j = 0; j < Board::COLS; ++j) {
            if (board[i * Board::COLS + j] == ' ') {
                break;
            }
            if (j == Board::COLS - 1) {
                for (auto &block : gameBoard.blocks) {
                    block->deleteRow(i);
                }
                rows.push_back(i);
            }
        }
    }
    int size = (unsigned int) rows.size();
    if (size > 0) {
        score += pow<int, int>(size + level, 2);
    }

    for (int i : rows) {
        for (auto &block : gameBoard.blocks) {
            block->shiftDown(i);
        }
    }

    score += gameBoard.gc();

    return size;
}

Player::~Player()
{
}
