#include "game.h"
#include <cassert>
#include <sstream>
#include <string>

using namespace std;

Game::Game(bool isGraphics, int seed, string file1, string file2, int startLevel, bool bonusEnabled)
    : isGraphics { isGraphics }
    , bonusEnabled { bonusEnabled }
    , seed { seed }
    , file1 { file1 }
    , file2 { file2 }
    , startLevel { startLevel }
{
    player1 = make_unique<Player>(file1);
    player2 = make_unique<Player>(file2);
    this->seed = seed;
    this->startLevel = startLevel;
    currentPlayer = player1.get();
    turn_count = 0;
    if (isGraphics) {
        window =  make_unique<Window>(bonusEnabled);
        window->setQueue(player1->q.get());
    }
}

void Game::restart()
{
    player1 = make_unique<Player>(file1);
    player2 = make_unique<Player>(file2);
    player1->setLevel(startLevel);
    player2->setLevel(startLevel);
    player1->blockFactory->setSeed(seed);
    player2->blockFactory->setSeed(seed + 1);
    player1->gameBoard.currentBlock = player1->blockFactory->getNext(player1->effect);
    player2->gameBoard.currentBlock = player2->blockFactory->getNext(player2->effect);
    player1->gameBoard.nextBlock = player1->blockFactory->getNext(player1->effect);
    player2->gameBoard.nextBlock = player2->blockFactory->getNext(player2->effect);
    currentPlayer = player1.get();
    turn_count = 0;
    printGame();
    if (isGraphics) {
        renderGame();
        window->setQueue(player1->q.get());
    }
}

void Game::renderGame()
{
    if (!isGraphics)
        return;
    unique_ptr<Window::RenderData> d(new Window::RenderData { player1->gameBoard.toString(true, bonusEnabled),
        player2->gameBoard.toString(true, bonusEnabled),
        player1->score, player2->score,
        player1->level, player2->level,
        (currentPlayer == player1.get()) ? player1->gameBoard.nextBlock.get() : nullptr,
        (currentPlayer == player2.get()) ? player2->gameBoard.nextBlock.get() : nullptr,
        player1->gameBoard.ROWS, player1->gameBoard.COLS,
        highScore });
    window->renderGame(std::move(d));
}

void Game::startGame()
{
    if (turn_count != 0)
        return;
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
    if (isGraphics) {
        window->startDisplay();
    }
    else {
        mainThread.join();
    }
}

void Game::printGame()
{
    assert(player1 != nullptr);
    assert(player2 != nullptr);
    assert(currentPlayer != nullptr);
    assert(player1->gameBoard.COLS == player2->gameBoard.COLS);
    assert(player1->gameBoard.ROWS == player2->gameBoard.ROWS);
    string player1Board = player1->gameBoard.toString(true);
    string player2Board = player2->gameBoard.toString(true);
    assert(player1Board.length() == player2Board.length());
    cout << "\t  "
         << "Highscore: " << highScore << endl;
    cout << "-----------------------------------" << endl;
    cout << "Level:\t" << player1->level << "\t\t"
         << "Level:\t" << player2->level << endl;
    cout << "Score:\t" << player1->score << "\t\t"
         << "Score:\t" << player2->score << endl;
    cout << "-----------\t\t-----------" << endl;
    for (int i = 0; i < player1->gameBoard.ROWS; ++i) {
        cout << player1Board.substr(i * player1->gameBoard.COLS, player1->gameBoard.COLS) << "\t\t" << player2Board.substr(i * player2->gameBoard.COLS, player2->gameBoard.COLS) << endl;
    }
    cout << "-----------\t\t-----------" << endl;
    cout << "Next:\t\t\tNext:" << endl;
    if (currentPlayer == player1.get()) {
        player1->gameBoard.nextBlock->printBlock(true);
    } else if (currentPlayer == player2.get()) {
        player2->gameBoard.nextBlock->printBlock(false);
    }
}

void Game::textInput()
{
    string command;
    while (isRunning) {
        cin >> command;
        std::istringstream ss { command };
        int multiplier;

        if (ss >> multiplier) {
            if (multiplier < 0) {
                multiplier = 1;
            }
        } else {
            multiplier = 1;
        }

        ss >> command;

        int count = 0;
        string match;
        for (auto& c : COMMANDS) {
            if (c.substr(0, command.length()) == command) {
                count++;
                match = c;
            }
        }
        if (count == 1) {
            command = match;
        }

        Queue* q = (currentPlayer == player1.get() ? player1->q.get() : player2->q.get());

        if (command == "quit") {
            q->push("quit");
            break; // break out of while loop
        }

        if (command == "norandom" || command == "sequence") {
            string filename;
            cin >> filename;
            q->push(command); // push the command and filename to the queue
            q->push(filename);
            continue; 
        }


        if (command == "random" || command == "restart" || command == "hint") {
            q->push(command); // multipliers don't work for these commands
            continue;
        }

        for (int i = 0; i < multiplier; ++i) {
            q->push(command); // push the command to the queue multiplier times
        }
    }
}

void Game::runMainLoop()
{

    while (isRunning) {

        // Check if game is over
        if (!player1->gameBoard.validBoard()) {
            cout << "Player 2 wins!" << endl;
            restart();
            continue;
        } else if (!player2->gameBoard.validBoard()) {
            cout << "Player 1 wins!" << endl;
            restart();
            continue;
        }

        cout << (player1.get() == currentPlayer ? "Player 1" : "Player 2") << "'s turn" << endl;
        string command = (player1.get() == currentPlayer ? player1->q : player2->q)->pop();

        if (command == "left") {
            currentPlayer->gameBoard.left();
        } else if (command == "right") {
            currentPlayer->gameBoard.right();
        } else if (command == "down") {
            currentPlayer->gameBoard.down();
        } else if (command == "clockwise") {
            currentPlayer->gameBoard.clockwise();
        } else if (command == "counterclockwise") {
            currentPlayer->gameBoard.counterClockwise();
        } else if (command == "drop") {
            currentPlayer->gameBoard.drop(); // next block is now nullptr
            currentPlayer->gameBoard.nextBlock = currentPlayer->blockFactory->getNext(currentPlayer->effect); // no longer nullptr
            if (currentPlayer->clearRow() && isGraphics)
                window->playSound(2);
            else if (isGraphics)
                window->playSound(0);
            highScore = currentPlayer->score > highScore ? currentPlayer->score : highScore;
            currentPlayer = currentPlayer == player1.get() ? player2.get() : player1.get();
            window->setQueue(currentPlayer->q.get());
            turn_count++;
        } else if (command == "levelup") {
            currentPlayer->setLevel(currentPlayer->level + 1);
        } else if (command == "leveldown") {
            currentPlayer->setLevel(currentPlayer->level - 1);
        } else if (command == "I") {
            currentPlayer->gameBoard.currentBlock = make_unique<IBlock>(Position{0, 0}, currentPlayer->effect);
        } else if (command == "J") {
            currentPlayer->gameBoard.currentBlock = make_unique<JBlock>(Position{0, 0}, currentPlayer->effect);
        } else if (command == "L") {
            currentPlayer->gameBoard.currentBlock = make_unique<LBlock>(Position{0, 0}, currentPlayer->effect);
        } else if (command == "O") {
            currentPlayer->gameBoard.currentBlock = make_unique<OBlock>(Position{0, 0}, currentPlayer->effect);
        } else if (command == "S") {
            currentPlayer->gameBoard.currentBlock = make_unique<SBlock>(Position{0, 0}, currentPlayer->effect);
        } else if (command == "T") {
            currentPlayer->gameBoard.currentBlock = make_unique<TBlock>(Position{0, 0}, currentPlayer->effect);
        } else if (command == "Z") {
            currentPlayer->gameBoard.currentBlock = make_unique<ZBlock>(Position{0, 0}, currentPlayer->effect);
        } else if (command == "restart") {
            restart();
            continue;
        } else if (command == "quit") {
            endGame();
            break;
        } else if (command == "sequence") {
            cerr << "Sequence not implemented yet" << endl;
        } else if (command == "random") {
            currentPlayer->blockFactory->setRandom(true);
        } else if (command == "norandom") {
            string filename = (player1.get() == currentPlayer ? player1->q : player2->q)->pop();
            currentPlayer->blockFactory->setRandom(false, filename);
            cout << "Sequence set to " << filename << endl;
        } else if (command == "hint") {
            cerr << "Hint not implemented yet" << endl;
        }

        if (isGraphics) {
            renderGame();
        }

        printGame();
    }
}

void Game::endGame()
{
    if (isGraphics)
        window->quit = true;
    isRunning = false;
    try {
        if (textThread.joinable())
            textThread.join();
        if (mainThread.joinable())
            mainThread.join();
    } catch (...) {
        // Many things can go wrong here, especially if the mutex is still locked
        // We don't care about any of them, the game is over and we just want to kill the threads
    }
}

Game::~Game()
{
    endGame();
}