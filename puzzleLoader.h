#ifndef PuzzleLoader_HEADER
#define PuzzleLoader_HEADER

#define MAX_INDEX 1000000
#include "puzzle.h"

class PuzzleLoader {
    public:
        PuzzleLoader();

        int puzzle[N][N];

        bool loadPuzzle(int index);
        int loadRandomPuzzle();
    private:
};

#endif


