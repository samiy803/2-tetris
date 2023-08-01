#include "constants.h"
#include "game.h"
#include <iostream>
#include <memory>
#include <thread>

using namespace std;

int main(int argc, char* argv[])
{
    bool isGraphics = true;
    bool bonusEnabled = false;
    int seed;
    int startLevel = 0;
    string file1 = SEQUENCE_1;
    string file2 = SEQUENCE_2;
    for (int i = 1; i < argc; ++i) {
        if (TEXT_ARG == argv[i]) {
            isGraphics = false;
        }
        if (BONUS_ARG == argv[i]) {
            bonusEnabled = true;
        }
        if (SEED_ARG == argv[i] && i + 1 < argc) {
            try {
                seed = stoi(argv[i + 1]);
            } catch (...) {
                cerr << "Fatal error, invalid seed: " << argv[i + 1] << endl;
            }
        }
        if (SCRIPT_1 == argv[i] && i + 1 < argc) {
            file1 = argv[i + 1];
        }
        if (SCRIPT_2 == argv[i] && i + 1 < argc) {
            file2 = argv[i + 1];
        }
        if (START_LEVEL == argv[i] && i + 1 < argc) {
            try {
                startLevel = stoi(argv[i + 1]);
            } catch (...) {
                cerr << "Fatal error, invalid start level: " << argv[i + 1] << endl;
            }
        }
    }

    try {
        std::unique_ptr<Game> game = std::make_unique<Game>(isGraphics, seed, file1, file2, startLevel, bonusEnabled);
        game->startGame();
    } catch (...) {
        cerr << "Fatal error, could not create game. Contact DMK for more info" << endl;
        return 1;
    }

    return 0;
}