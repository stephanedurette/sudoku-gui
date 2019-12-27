#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

#include "puzzleLoader.h"
#include "puzzle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void DisplayPuzzle();
    void LoadPuzzle(int index);
    void InitSquares();




private:
    Ui::MainWindow *ui;
    bool recursiveSolvePuzzle(int position);

    PuzzleLoader m_puzzleLoader;
    Sudoku m_sudoku;
    QLineEdit *squares[N * N];
    bool inputsEnabled;
    bool creatingPuzzle;

public slots:
    void on_square_editingFinished();

private slots:
    void on_btn_LoadRandomPuzzle_clicked();
    void on_btn_LoadPuzzle_clicked();
    void on_btn_CheckSolution_clicked();
    void on_btn_SolvePuzzle_clicked();

    void on_btn_CreatePuzzle_clicked();
};
#endif // MAINWINDOW_H
