#ifndef Sudoku_HEADER
#define Sudoku_HEADER
#define N 9

class Sudoku {
    public:
        Sudoku();
        void initPuzzle(int _startingPuzzle[N][N]);
        bool solvePuzzle();
        void printPuzzle();
        int getValueAt(int index);
        int getSolvedValueAt(int index);
        bool _insert_value(int position, int value);
        void _reset_value(int position);

    private:
        int startingPuzzle[N][N];
        int puzzle[N][N];
        int solvedPuzzle[N][N];
        bool row_set[N][N + 1];
        bool col_set[N][N + 1];
        bool box_set[N][N + 1];

        bool _can_insert(int position);
        int _get_box_set_index(int index);
        bool _recursive_solve_puzzle(int position);

};

#endif
