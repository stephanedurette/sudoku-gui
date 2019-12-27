#include "puzzle.h"
#include <stdio.h>

Sudoku::Sudoku() {
}

void Sudoku::initPuzzle(int _startingPuzzle[N][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            startingPuzzle[i][j] = _startingPuzzle[i][j];
            puzzle[i][j] = _startingPuzzle[i][j];
            row_set[i][j + 1] = false;
            col_set[i][j + 1] = false;
            box_set[i][j + 1] = false;
        }
    }

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            int pos = col + row * N;
            if (!_can_insert(pos)) {
                _insert_value(pos, startingPuzzle[row][col]);
            }
        }
    }
}

bool Sudoku::_can_insert(int position) {
    int row = position / N;
    int col = position % N;
    return (startingPuzzle[row][col] == 0);
}

bool Sudoku::_insert_value(int position, int value) {
    int row = position / N;
    int col = position % N;
    int box_index = _get_box_set_index(position);
    //is the insert valid
    if (row_set[row][value] || col_set[col][value] || box_set[box_index][value]) return false;
    //insert the number
    row_set[row][value] = true;
    col_set[col][value] = true;
    box_set[box_index][value] = true;
    puzzle[row][col] = value;

    return true;
}

void Sudoku::_reset_value(int position) {
    int row = position / N;
    int col = position % N;
    int value = puzzle[row][col];
    int box_index = _get_box_set_index(position);

    row_set[row][value] = false;
    col_set[col][value] = false;
    box_set[box_index][value] = false;
    puzzle[row][col] = 0;
}


int Sudoku::_get_box_set_index(int index) {
    int col = index % N;
    int row = index / N;
    return col / 3 + 3 * (row / 3);
}

bool Sudoku::solvePuzzle() {
    return _recursive_solve_puzzle(0);
}

bool Sudoku::_recursive_solve_puzzle(int position) {
    if (position == N * N) {
        for(int row = 0; row < N;row++){
            for(int col = 0; col < N;col++){
                solvedPuzzle[row][col] = puzzle[row][col];
            }
        }
        return true;
    }
    if (!_can_insert(position)) {
        return _recursive_solve_puzzle(position + 1);
    }
    for (int i = 1; i <= N; i++) {
        if (_insert_value(position, i)) {
            _recursive_solve_puzzle(position + 1);
            //if (_recursive_solve_puzzle(position + 1)) {
          //      return true;
         //   }
         //   else {
                _reset_value(position);
          //  }
        }
    }
    return false;
}

void Sudoku::printPuzzle() {
    printf("\n");
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%d ", puzzle[row][col]);
        }
        printf("\n");
    }
}

int Sudoku::getValueAt(int index)
{
    int col = index % N;
    int row = index / N;
    return puzzle[row][col];
}

int Sudoku::getSolvedValueAt(int index){
    int col = index % N;
    int row = index / N;
    return solvedPuzzle[row][col];
}
