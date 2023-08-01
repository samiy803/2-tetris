#include "board.h"
#include <map>
#include <cmath>
#include <iostream>
#include <memory>
#include "level0Factory.h"

string Board::toString(bool includeCurrentBlock, bool ghost, bool blind) {
    char board[ROWS * COLS];
    for (int i = 0; i < ROWS * COLS; i++) {
        board[i] = ' ';
    }
    if (ghost) {
        // Make a copy of the current block and store it in a unique_ptr
        Block* ghostBlock = currentBlock->clone();

        blocks.push_back(ghostBlock);

        // Move the ghost block down until it hits something
        while (validBoard(false)) {
            ghostBlock->down();
        }
        ghostBlock->up();

        blocks.pop_back();

        // Draw the ghost block in lowercase
        for (Position pos : ghostBlock->getPositions()) {
            board[pos.y * COLS + pos.x] = tolower(ghostBlock->c);
        }

    }
    for (Block* block : blocks) {
        for (Position pos : block->getPositions()) {
            board[pos.y * COLS + pos.x] = block->c;
        }
    }
    if (includeCurrentBlock) {
        for (Position pos : currentBlock->getPositions()) {
            board[pos.y * COLS + pos.x] = currentBlock->c;
        }
    }
    if(blind){
        for(int rows = 3; rows < 12; rows++){
            for(int cols = 3; cols < 9; cols++){
                board[rows * COLS + cols] = '?';
            }
        }
    }
    string s = board;
    return s;
}

bool Board::validBoard(bool includeCurrentBlock) {
    // Check for overlap
    vector<Position> positions;

    if (includeCurrentBlock) {
            for (Position pos : currentBlock->getPositions()) {
            if (pos.x < 0 || pos.x >= Board::COLS || pos.y < 0 || pos.y >= Board::ROWS) {
                return false;
            }
            positions.push_back(pos);
        }
    }

    for (Block* block : blocks) {
        for (Position pos : block->getPositions()) {
            if (pos.x < 0 || pos.x >= Board::COLS || pos.y < 0 || pos.y >= Board::ROWS) {
                return false;
            }
            for (Position p : positions) {
                if (p == pos) {
                    return false;
                }
            }
            positions.push_back(pos);
        }
    }
    return true;
}

void Board::left(bool heavyeffect) {
    currentBlock->left();
    if(level == 3 || level == 4){
        currentBlock->down();
    }
    if(heavyeffect) {
        currentBlock->down();
    }
    if (!validBoard()) {
        if(level == 4 || level == 3){
            currentBlock->up();
        }
        if(heavyeffect){
            currentBlock->up();
        }
        currentBlock->right();
    }
}

void Board::right(bool heavyeffect) {
    currentBlock->right();
    if(level == 3 || level == 4){
        currentBlock->down();
    }
    if(heavyeffect) {
        currentBlock->down();
    }
    if (!validBoard()) {
        if(level == 4 || level == 3){
            currentBlock->up();
        }
        if(heavyeffect){
            currentBlock->up();
        }
        currentBlock->left();
    }
}

void Board::down(bool heavyeffect) {
    currentBlock->down();
    if(level == 3 || level == 4){
        currentBlock->down();
    }
    if(heavyeffect) {
        currentBlock->down();
    }
    if (!validBoard()) {
        if(level == 4 || level == 3){
            currentBlock->up();
        }
        if(heavyeffect){
            currentBlock->up();
        }
        currentBlock->up();
    }
}

void Board::clockwise() {
    currentBlock->clockwise();
    if (!validBoard()) {
        currentBlock->counterClockwise();
    }
}

void Board::counterClockwise() {
    currentBlock->counterClockwise();
    if (!validBoard()) {
        currentBlock->clockwise();
    }
}

void Board::drop() {
    while(validBoard()){
        currentBlock->down();
    }
    currentBlock->up();

    blocks.push_back(currentBlock);
    currentBlock = nextBlock;
    nextBlock = nullptr;
}

void Board::dropStar(){
    STARBlock* starblock = new STARBlock(Position{5, 0}, 0, 0, 4);
    Block* temp = currentBlock;
    currentBlock = starblock;
    while(validBoard()){
        currentBlock->down();
    }
    currentBlock->up();
    blocks.push_back(currentBlock);
    currentBlock = temp;
}

int Board::gc() {
    for (auto it = blocks.begin(); it != blocks.end();) {
        if ((*it)->getOffsets().size() == 0) {
            delete *it;
            int scoreAddition = pow(((*it)->startingLevel + 1), 2);
            it = blocks.erase(it);
            return scoreAddition;
            it = blocks.erase(it);
        }
        else {
            ++it;
        }
    }
    return 0;
}