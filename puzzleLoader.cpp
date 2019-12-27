#include "puzzleLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

PuzzleLoader::PuzzleLoader() {
    srand(time(NULL));
}

bool PuzzleLoader::loadPuzzle(int index) {
    if (index < 1 || index > MAX_INDEX) return false;

    FILE* fp;
    fopen_s(&fp, "allpuzzles.txt", "r");
    if (fp == NULL) return false;

    char puzzleLine[512];
    for (int i = 0; i < index; i++) {
        fgets(puzzleLine, 512, fp);
    }
    int i = 0;
    while (puzzleLine[i] != ',') {
        int row = i / N;
        int col = i % N;
        puzzle[row][col] = (int)(puzzleLine[i++] - '0');
    }
    return true;
}

int PuzzleLoader::loadRandomPuzzle() {
    int index = rand() % (MAX_INDEX + 1);
    loadPuzzle(index);
    return index;
}

