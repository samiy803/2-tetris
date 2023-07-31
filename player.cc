#include "player.h"
#include "queue.h"
#include <cmath>
#include <iostream>

using namespace std;

Player::Player(string filename, int score, int level, int effect)
    : score { score }
    , level { level }
    , effect { effect }
    , filename { filename }
{
    switch (level) {
    case 0:
        blockFactory = new Level0Factory(filename);
        break;
    default:
        throw "Invalid level";
        break;
    }
    score = 0;
    q = new Queue();
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

void Player::setLevel(int level)
{
    cout << level << endl;
    if (level < 0 || level > 4)
        return;
    this->level = level;
    gameBoard.level = level;
    delete blockFactory;
    switch (level) {
    case 0:
        blockFactory = new Level0Factory(filename);
        break;
    case 1:
        blockFactory = new Level1Factory();
        break;
    case 2:
        blockFactory = new Level2Factory();
        break;
    case 3:
        blockFactory = new Level3Factory();
        break;
    case 4:
        blockFactory = new Level4Factory();
        score5turnsago = score;
        break;
    default:
        throw "Invalid level";
        break;
    }
}

bool Player::clearRow()
{
    string board = gameBoard.toString(false);

    vector<int> rows;

    for (int i = 0; i < Board::ROWS; ++i) {
        for (int j = 0; j < Board::COLS; ++j) {
            if (board[i * Board::COLS + j] == ' ') {
                break;
            }
            if (j == Board::COLS - 1) {
                for (auto block : gameBoard.blocks) {
                    block->deleteRow(i);
                }
                rows.push_back(i);
            }
        }
    }
    int size = rows.size();
    if (size > 0) {
        score += pow(size + level, 2);
    }

    for (int i : rows) {
        for (auto block : gameBoard.blocks) {
            block->shiftDown(i);
        }
    }

    score += gameBoard.gc();

    return size > 0;
}

Player::~Player()
{
    delete blockFactory;
}