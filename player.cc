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

void Player::setLevel(int level)
{
    cout << level << endl;
    if (level < 0 || level > 4)
        return;
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
                for (auto &block : gameBoard.blocks) {
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
        for (auto &block : gameBoard.blocks) {
            block->shiftDown(i);
        }
    }

    if (size >= 2) {
        while(1){
            string effectinput;
            cout << "Apply Effect: " << endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(cin, effectinput);
            cout << effectinput << endl;
            istringstream iss{effectinput};
            string firstword;
            if(firstword == "blind"){ 
                triggereffect = 3;
                break;
            }else if(firstword == "heavy"){
                triggereffect = 2;
                break;
            }else if(firstword == "force"){
                string block;
                iss >> block;
                if(block == "I"){
                    triggereffect = 5;
                    break;
                }else if(block == "J"){
                    triggereffect = 7;
                    break;
                }else if(block == "L"){
                    triggereffect = 11;
                    break;
                }else if(block == "O"){
                    triggereffect = 13;
                    break;
                }else if(block == "S"){
                    triggereffect = 17;
                    break;
                }else if(block == "T"){
                    triggereffect = 19;
                    break;
                }else if(block == "Z"){
                    triggereffect = 23;
                    break;
                }else{
                    cout << "Invalid block" << endl;
                }
            }
            else{
                cout << "Invalid Effect" << endl;
            }
        }
        
    }
    cout << triggereffect << endl;
    score += gameBoard.gc();

    return size > 0;
}

Player::~Player()
{
}
