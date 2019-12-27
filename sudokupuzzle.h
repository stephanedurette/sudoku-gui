#ifndef SUDOKUPUZZLE_H
#define SUDOKUPUZZLE_H
#define N 9

#include <QObject>

class SudokuPuzzle : public QObject
{
    Q_OBJECT
public:
    explicit SudokuPuzzle(QObject *parent = nullptr);

private:
    int starting_puzzle[N][N];
    int puzzle[N][N];
    bool row_set[N][N + 1];
    bool col_set[N][N + 1];
    bool box_set[N][N + 1];
signals:

};

#endif // SUDOKUPUZZLE_H
