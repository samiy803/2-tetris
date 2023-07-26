#include "game.h"
#include <cassert>
#include <string>

using namespace std;

Game::Game(bool isGraphics, int seed, string file1, string file2, int startLevel, bool audio) : isGraphics{isGraphics}, seed{seed}, file1{file1}, file2{file2}, startLevel{startLevel} {
    player1 = new Player(file1);
    player2 = new Player(file2);
    this->seed = seed;
    this->startLevel = startLevel;
    currentPlayer = player1;
    turn_count = 0;
    q = new Queue();
    window = isGraphics ? new Window(q, audio) : nullptr;
}

// FIXME
void Game::restart() {
    delete player1;
    delete player2;
    delete window;
    player1 = new Player();
    player2 = new Player();
    currentPlayer = player1;
    turn_count = 0;
    if (isGraphics) {
        window = new Window();
    }
    else {
        window = nullptr;
    }
}

void Game::renderGame() {
    Window::RenderData *d = new Window::RenderData{ player1->gameBoard.toString(true),
                                                    player2->gameBoard.toString(true),
                                                    player1->score, player2->score,
                                                    player1->level, player2->level,
                                                    player1->gameBoard.nextBlock,
                                                    player2->gameBoard.nextBlock,
                                                    player1->gameBoard.ROWS, player1->gameBoard.COLS};
    window->renderGame(d);
}

void Game::startGame() {
    if (turn_count != 0) return;
    player1->setLevel(startLevel);
    player2->setLevel(startLevel);
    player1->blockFactory->setSeed(seed);
    player2->blockFactory->setSeed(seed + 1);
    player1->gameBoard.currentBlock = player1->blockFactory->getNext(player1->effect);
    player2->gameBoard.currentBlock = player2->blockFactory->getNext(player2->effect);
    player1->gameBoard.nextBlock = player1->blockFactory->getNext(player1->effect);
    player2->gameBoard.nextBlock = player2->blockFactory->getNext(player2->effect);

    isRunning = true;
    printGame();
    renderGame();
    textThread = thread(&Game::textInput, this);
    mainThread = thread(&Game::runMainLoop, this);
    if (isGraphics)
        window->startDisplay();
    else
        mainThread.join();
}

void Game::printGame() {
    assert(player1 != nullptr);
    assert(player2 != nullptr);
    assert(currentPlayer != nullptr);
    assert(player1->gameBoard.COLS == player2->gameBoard.COLS);
    assert(player1->gameBoard.ROWS == player2->gameBoard.ROWS);
    string player1Board = player1->gameBoard.toString(true);
    string player2Board = player2->gameBoard.toString(true);
    assert(player1Board.length() == player2Board.length());
    cout << "Level:\t" << player1->level << "\t\t" << "Level:\t" << player2->level << endl;
    cout << "Score:\t" << player1->score << "\t\t" << "Score:\t" << player2->score << endl;
    cout << "-----------\t\t-----------" << endl;
    for (int i = 0; i < player1->gameBoard.ROWS; ++i) {
        cout << player1Board.substr(i * player1->gameBoard.COLS, player1->gameBoard.COLS) << "\t\t" << player2Board.substr(i * player2->gameBoard.COLS, player2->gameBoard.COLS) << endl;
    }
    cout << "-----------\t\t-----------" << endl;
    cout << "Next:\t\t\tNext:" << endl;
    if(currentPlayer == player1){
        cout << player1->gameBoard.nextBlock->c << endl;
    } 
    else if(currentPlayer == player2){
        cout << player1->gameBoard.nextBlock->c << endl;
    }
}

void Game::textInput() {
    string command;
    while (isRunning) {
        cin >> command;
        q->push(command);
        if (command == "quit") {
            break;
        }
    }
}

void Game::runMainLoop() {

    bool playDrop = false;

    while (isRunning) {
        string command = q->pop();

        if (command == "left") {
            currentPlayer->gameBoard.left();
        }
        else if (command == "right") {
            currentPlayer->gameBoard.right();
        }
        else if (command == "down") {
            currentPlayer->gameBoard.down();
        }
        else if (command == "clockwise") {
            currentPlayer->gameBoard.clockwise();
        }
        else if (command == "counterclockwise") {
            currentPlayer->gameBoard.counterClockwise();
        }
        else if (command == "drop") {
            currentPlayer->gameBoard.drop(); // next block is now nullptr
            currentPlayer->gameBoard.nextBlock = currentPlayer->blockFactory->getNext(currentPlayer->effect); // no longer nullptr
            currentPlayer->clearRow();
            currentPlayer = currentPlayer == player1 ? player2 : player1;
            turn_count++;
            playDrop = true;
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
        else if (command == "quit") {
            endGame();
            break;
        }
        else if (command == "sequence") {
            cerr << "Sequence not implemented yet" << endl;
        }
        else if (command == "random") {
            cerr << "Random not implemented yet" << endl;
        }
        else if (command == "norandom") {
            string filename;
            cin >> filename;
            cerr << "Norandom not implemented yet" << endl;
        }
        else if (command == "hint") {
            cerr << "Hint not implemented yet" << endl;
        }

        if (isGraphics) {
            renderGame();
        }

        printGame();
        
        if (playDrop) {
            playDrop = false;
            if (isGraphics) {
                window->playDrop();
            }
        }
    }
}

void Game::endGame() {
    if (isGraphics)
        window->quit = true;
    isRunning = false;
    try {
        if (textThread.joinable())
            textThread.join();
        if (mainThread.joinable())
            mainThread.join();
    } catch(...) {
        // Many things can go wrong here, especially if the mutex is still locked
        // We don't care about any of them, the game is over and we just want to kill the threads
    }
}

Game::~Game() {
    delete player1;
    delete player2;
    delete q;
    if (isGraphics)
        delete window;
}