#include <iostream>
#include "game.h"

#define SEQUENCE_1 "sequence1.txt"
#define SEQUENCE_2 "sequence2.txt"

using namespace std;

int main(int argc, char* argv[]) {
    bool isGraphics = true;
    int seed;
    int startLevel = 0;
    string file1 = SEQUENCE_1;
    string file2 = SEQUENCE_2;
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == "-text") {
            isGraphics = false;
        }
        if (argv[i] == "-seed" && i + 1 < argc) {
            try {
                seed = stoi(argv[i + 1]);
            }
            catch (...) {
                cerr << "Fatal error, invalid seed: " << argv[i + 1] << endl;
            }
        }
        if (argv[i] == "-scriptfile1" && i + 1 < argc) {
            file1 = argv[i + 1];
        }
        if (argv[i] == "-scriptfile2" && i + 1 < argc) {
            file2 = argv[i + 1];
        }
        if (argv[i] == "-startlevel" && i + 1 < argc) {
            try {
                startLevel = stoi(argv[i + 1]);
            }
            catch (...) {
                cerr << "Fatal error, invalid start level: " << argv[i + 1] << endl;
            }
        }
    }

    Game* game;
    try {
        game = new Game(isGraphics, seed, file1, file2, startLevel);
    }
    catch (...) {
        cerr << "Fatal error, could not create game. Contact DMK for more info" << endl;
    }
    game->runMainLoop();
    delete game;
    return 0;
}