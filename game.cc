#include "game.h"

Game::Game(bool isGraphics, int seed, string file1, string file2, int startLevel) : isGraphics{isGraphics}, seed{seed}, file1{file1}, file2{file2}, startLevel{startLevel} {
    player1 = new Player();
    player2 = new Player();
    currentPlayer = player1;
    turn_count = 0;
    window = isGraphics ? new XWindow() : nullptr;
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

    }
}