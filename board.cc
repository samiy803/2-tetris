#include "board.h"

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

void Board::drop() {
    blocks.push_back(currentBlock);
    currentBlock = nextBlock;
    nextBlock = nullptr;
}