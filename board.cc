#include "board.h"
#include <map>
#include <cmath>
#include <iostream>
#include <memory>
#include "level0Factory.h"

string Board::toString(bool includeCurrentBlock, bool ghost) {
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

void Board::left() {
    currentBlock->left();
    if (!validBoard()) {
        currentBlock->right();
    }
}

void Board::right() {
    currentBlock->right();
    if (!validBoard()) {
        currentBlock->left();
    }
}

void Board::down() {
    currentBlock->down();
    if (!validBoard()) {
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