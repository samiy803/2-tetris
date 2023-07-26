#include "board.h"
#include <map>

string Board::toString(bool includeCurrentBlock) {
    char board[ROWS * COLS];
    for (int i = 0; i < ROWS * COLS; i++) {
        board[i] = ' ';
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

bool Board::validBoard() {

    // Check for overlap
    vector<Position> positions;

    for (Position pos : currentBlock->getPositions()) {
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