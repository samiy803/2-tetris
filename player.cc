#include "player.h"

Player::Player(string filename, int score, int level, int effect) : score{score}, level{level}, effect{effect}, filename{filename} {
    switch (level) {
        case 0:
            blockFactory = new Level0Factory(filename);
            break;
        default:
            throw "Invalid level";
            break;
    }
}

void Player::setBlind(bool blind) {
    if (blind && effect % 2)
        effect *= 2;
    else if (!blind && !(effect % 2))
        effect /= 2;
}

void Player::setHeavy(bool heavy) {
    if (heavy && effect % 3)
        effect *= 3;
    else if (!heavy && !(effect % 3))
        effect /= 3;
}

void Player::setForce(string block) {
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


void Player::setLevel(int level) {
    this->level = level;
    delete blockFactory;
    switch (level) {
        case 0:
            blockFactory = new Level0Factory(filename);
            break;
        default:
            throw "Invalid level";
            break;
    }
}

void Player::clearRow() {
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
                    rows.push_back(i);
                }
            }
        }
    }

    for (int i : rows) {
        for (auto block : gameBoard.blocks) {
            block->shiftDown(i);
        }
    }

    gameBoard.gc();
}


Player::~Player() {
    delete blockFactory;
}