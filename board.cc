#include "board.h"
#include "level0Factory.h"
#include <cmath>
#include <iostream>
#include <map>
#include <memory>

using namespace std;

string Board::toString(bool includeCurrentBlock, bool ghost, bool blind)
{
    char board[ROWS * COLS + 1];
    for (int i = 0; i < ROWS * COLS; i++) {
        board[i] = ' ';
    }
    if (ghost) {
        // Make a copy of the current block and store it in a unique_ptr
        unique_ptr<Block> ghostBlock = currentBlock->clone();

        blocks.push_back(unique_ptr<Block>(ghostBlock.get())); // Copy the ghost block into the blocks vector

        // Move the ghost block down until it hits something
        while (validBoard(false)) {
            ghostBlock->down();
        }
        ghostBlock->up();

        // Draw the ghost block in lowercase
        for (Position pos : ghostBlock->getPositions()) {
            board[pos.y * COLS + pos.x] = tolower(ghostBlock->c);
        }

        blocks.pop_back();
        ghostBlock.release(); // Release the ghost block from the unique_ptr since it already got freed when it was popped
    }
    for (auto &block : blocks) {
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
    board[ROWS * COLS] = '\0';
    string s = board;
    return s;
}

bool Board::validBoard(bool includeCurrentBlock)
{
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

    for (auto &block : blocks) {
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

void Board::left(bool heavyEffect) {
    currentBlock->left();
    if (level == 3 || level == 4) {
        currentBlock->down();
    }
    if(heavyEffect) {
        currentBlock->down();
    }
    if (!validBoard()) {
        if (level == 4 || level == 3) {
            currentBlock->up();
        }
        if(heavyEffect){
            currentBlock->up();
        }
        currentBlock->right();
    }
}

void Board::right(bool heavyEffect) {
    currentBlock->right();
    if (level == 3 || level == 4) {
        currentBlock->down();
    }
    if(heavyEffect) {
        currentBlock->down();
    }
    if (!validBoard()) {
        if (level == 4 || level == 3) {
            currentBlock->up();
        }
        if(heavyEffect){
            currentBlock->up();
        }
        currentBlock->left();
    }
}

void Board::down(bool heavyEffect) {
    currentBlock->down();
    if (level == 4 || level == 3) {
        currentBlock->down();
    }
    if (!validBoard()) {
        if (level){
            currentBlock->up();
        }
        currentBlock->up();
    }
}

void Board::clockwise()
{
    currentBlock->clockwise();
    if (level == 4 || level == 3) {
        currentBlock->down();
    }
    if (!validBoard()) {
        if (level == 4 || level == 3) {
            currentBlock->up();
        }
        currentBlock->counterClockwise();
    }
}

void Board::counterClockwise()
{
    currentBlock->counterClockwise();
    if (level == 4 || level == 3) {
        currentBlock->down();
    }
    if (!validBoard()) {
        if (level == 4 || level == 3) {
            currentBlock->up();
        }
        currentBlock->clockwise();
    }
}

void Board::drop()
{
    while (validBoard()) {
        currentBlock->down();
    }
    currentBlock->up();

    blocks.push_back(std::move(currentBlock));
    currentBlock = std::move(nextBlock);
    nextBlock.release();
}

// function to drop Star block
void Board::dropStar()
{
    unique_ptr<Block> sb = make_unique<StarBlock>();

    blocks.push_back(unique_ptr<Block>(sb.get()));

    while (validBoard(false)) {
        sb->down();
    }
    sb->up();
    sb.release();
}

int Board::gc()
{
    int scoreAddition = 0;
    for (auto it = blocks.begin(); it != blocks.end();) {
        if ((*it)->getOffsets().size() == 0) {
            scoreAddition += pow<int, int>(((*it)->startingLevel + 1), 2);
            it = blocks.erase(it);
        } else {
            ++it;
        }
    }
    if (scoreAddition > 0)
        return scoreAddition;
    else
        return 0;
}

Board::Board() : turn_count(0), level(0) {}
