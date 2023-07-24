#include "player.h"

Player::Player(int score, int level, int effect) : score{score}, level{level}, effect{effect} {
    switch (level) {
        case 0:
            blockFactory = new Level0Factory();
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
            blockFactory = new Level0Factory();
            break;
        default:
            throw "Invalid level";
            break;
    }
}


Player::~Player() {
    delete blockFactory;
}