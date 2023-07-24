#include "board.h"

string Board::toString() {
    char board[ROWS * COLS];
    for (int i = 0; i < ROWS * COLS; i++) {
        board[i] = ' ';
    }
    for (Block* block : blocks) {
        for (Position pos : block->getPositions()) {
            board[pos.x * COLS + pos.y] = block->c;
        }
    }
    string s = board;
    return s;
}

void Board::drop() {
    blocks.push_back(currentBlock);
    currentBlock = nullptr;
}