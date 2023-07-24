#include "game.h"

using std::cerr;
using std::endl;

Game::Game(bool isGraphics, int seed, string file1, string file2, int startLevel) : isGraphics{isGraphics}, seed{seed}, file1{file1}, file2{file2}, startLevel{startLevel} {
    player1 = new Player();
    player2 = new Player();
    // don't know if this is right
    this->seed = seed;
    this->startLevel = startLevel;
    currentPlayer = player1;
    turn_count = 0;
    window = isGraphics ? new XWindow() : nullptr;
}

string Game::parseCommand(){
    // implement
    return "";
}

void Game::restart() {
    delete player1;
    delete player2;
    delete window;
    player1 = new Player();
    player2 = new Player();
    currentPlayer = player1;
    turn_count = 0;
    if (isGraphics) {
        window = new XWindow();
    }
    else {
        window = nullptr;
    }
}

void Game::runMainLoop() {
    while (true) {
        // Parse command
        string command = parseCommand();

        if (command == "left") {
            currentPlayer->gameBoard.currentBlock->left();
        }
        else if (command == "right") {
            currentPlayer->gameBoard.currentBlock->right();
        }
        else if (command == "down") {
            currentPlayer->gameBoard.currentBlock->down();
        }
        else if (command == "clockwise") {
            currentPlayer->gameBoard.currentBlock->clockwise();
        }
        else if (command == "counterclockwise") {
            currentPlayer->gameBoard.currentBlock->counterClockwise();
        }
        else if (command == "drop") {
            currentPlayer->gameBoard.drop();
        }
        else if (command == "levelup") {
            currentPlayer->setLevel(currentPlayer->level + 1);
        }
        else if (command == "leveldown") {
            currentPlayer->setLevel(currentPlayer->level - 1);
        }
        else if (command == "I") {
            currentPlayer->setForce("I");
        }
        else if (command == "J") {
            currentPlayer->setForce("J");
        }
        else if (command == "L") {
            currentPlayer->setForce("L");
        }
        else if (command == "O") {
            currentPlayer->setForce("O");
        }
        else if (command == "S") {
            currentPlayer->setForce("S");
        }
        else if (command == "T") {
            currentPlayer->setForce("T");
        }
        else if (command == "Z") {
            currentPlayer->setForce("Z");
        }
        else if (command == "restart") {
            restart();
        }
        else if (command == "hint") {
            cerr << "Hint not implemented yet" << endl;
        }
    }
}