#include "board.h"
#include <map>

using std::map;

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
    if(!includeCurrentBlock){
        for(Position pos : nextBlock->getPositions()){
            board[pos.y * COLS + pos.x] = currentBlock->c;
        }
    }
    string s = board;
    return s;
}

bool Board::validBoard() {

    // Check for overlap
    map<Position, int> positions;

    for (Block* block : blocks) {
        for (Position pos : block->getPositions()) {
            if (pos.x < 0 || pos.x >= Board::COLS || pos.y < 0 || pos.y >= Board::ROWS) {
                return false;
            }
            if (positions.find(pos) != positions.end()) {
                return false;
            }
            positions[pos] = 1;
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
    blocks.push_back(currentBlock);
    currentBlock = nextBlock;
    nextBlock = nullptr;
}