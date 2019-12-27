#include <windows.h> // for Sleep

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "puzzle.h"
#include "puzzleLoader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sp_LoadPuzzleIndex->setRange(1, MAX_INDEX);
    InitSquares();
    LoadPuzzle(1);
    inputsEnabled = true;
    creatingPuzzle = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::DisplayPuzzle() //edit this
{
    for(int i = 0; i < N*N; i++){
        QLineEdit *l = squares[i];
        int val = m_sudoku.getValueAt(i);
        l->setEnabled(val == 0);
        if (val == 0){
            l->setText("");
        } else {
            l->setText(QString::number(val));
        }
        l->setStyleSheet("color: black;");
    }
}

void MainWindow::LoadPuzzle(int index)
{
    ui->lbl_solved->setText("");
    if (m_puzzleLoader.loadPuzzle(index)){
        m_sudoku.initPuzzle(m_puzzleLoader.puzzle);
        m_sudoku.solvePuzzle();
        ui->sp_LoadPuzzleIndex->setValue(index);
        DisplayPuzzle();
    }
}

void MainWindow::InitSquares()
{
    foreach(QLineEdit *s, this->findChildren<QLineEdit*>()){
        if (s->objectName().length() > 3) continue; //omit the numeric updown
        QString iString = s->objectName().mid(1, 2);
        int index = iString.toInt();
        squares[index] = s;
        s->connect(s, SIGNAL(editingFinished()),this,SLOT(on_square_editingFinished()));
    }
}

bool MainWindow::recursiveSolvePuzzle(int position){
    int sleep_length;
    if (position == N*N){
        return true;
    }
    if(!squares[position]->isEnabled()){
        return recursiveSolvePuzzle(position + 1);
    }
    for (int i = 1; i <= N; i++){
        QCoreApplication::processEvents();
        sleep_length = ui->sld_solveSpeed->maximum() - ui->sld_solveSpeed->value();

        Sleep(sleep_length);
        squares[position]->setStyleSheet("color: red;");

        squares[position]->setText(QString::number(i));
        //Sleep(sleep_length);
        if (!m_sudoku._insert_value(position, i)) continue;
        squares[position]->setStyleSheet("color: green;");
        if (recursiveSolvePuzzle(position + 1)){
            return true;
        } else {
            m_sudoku._reset_value(position);
        }
    }
    QCoreApplication::processEvents();
    Sleep(sleep_length);
    squares[position]->setText("");
    squares[position]->setStyleSheet("color: black;");
    return false;
}


void MainWindow::on_btn_LoadRandomPuzzle_clicked()
{
    if (!inputsEnabled) return;
    int index = rand() % (MAX_INDEX) + 1;
    LoadPuzzle(index);
}

void MainWindow::on_btn_LoadPuzzle_clicked()
{
    if (!inputsEnabled) return;
    int index = ui->sp_LoadPuzzleIndex->value();
    LoadPuzzle(index);
}

void MainWindow::on_btn_CheckSolution_clicked()
{
    bool solvedFlag = true;
    if (!inputsEnabled) return;

    for(int i = 0; i < N*N; i++){
        QString valueString = squares[i]->text();
        if (!squares[i]->isEnabled()) continue;
        if (squares[i]->text() == ""){
            solvedFlag = false;
            continue;
        }
        int value = squares[i]->text().toInt();
        int correctValue = m_sudoku.getSolvedValueAt(i); //broken
        if (value == 0){
            squares[i]->setText("");
            squares[i]->setStyleSheet("color: black;");
            continue;
        }
        if (value != correctValue){
            squares[i]->setStyleSheet("color: red;");
            solvedFlag = false;
        } else {
            squares[i]->setEnabled(false);
        }
    }
    if (solvedFlag){
        ui->lbl_solved->setText("Puzzle Solved!");
    }
}

void MainWindow::on_btn_SolvePuzzle_clicked()
{
    if (!inputsEnabled) return;
    if(ui->chk_InstantSolve->isChecked()){
        for(int i = 0; i < N*N; i++){
            int correctValue = m_sudoku.getSolvedValueAt(i);
            squares[i]->setText(QString::number(correctValue));
        }
    } else {
        inputsEnabled = false;
        recursiveSolvePuzzle(0);
        inputsEnabled = true;
    }
}


void MainWindow::on_square_editingFinished()
{
    int index = (sender()->objectName().mid(1, 2)).toInt();
    squares[index]->setStyleSheet("color:black;");
}

void MainWindow::on_btn_CreatePuzzle_clicked()
{
    if (!creatingPuzzle){
        creatingPuzzle = true;

        ui->btn_LoadPuzzle->setEnabled(false);
        ui->btn_SolvePuzzle->setEnabled(false);
        ui->btn_CheckSolution->setEnabled(false);
        ui->btn_LoadRandomPuzzle->setEnabled(false);

        ui->btn_CreatePuzzle->setText("Finish Creating Puzzle");

        for(int i = 0; i < N*N;i++){
            squares[i]->setText("");
            squares[i]->setEnabled(true);
            squares[i]->setStyleSheet("color:black;");
        }
    } else {
        bool validFlag = true;
        int count = 0; //must be 17
        int empty[N][N];
        for(int i = 0; i < N*N;i++){ empty[i / N][i % N] = 0; }
        m_sudoku.initPuzzle(empty);

        for(int i = 0; i < N*N; i++){
            QString str = squares[i]->text();

            if (str == "" || str == "0") continue;
            count++;
            int value = str.toInt();
            //empty[i / N][i % N] = value;
            if (value < 1 || value > 9 || !m_sudoku._insert_value(i, value)){
                squares[i]->setStyleSheet("color:red;");
                validFlag = false;
                continue;
            }
        }
        if (count < 17){
            ui->lbl_solved->setText("Enter at least 17 clues");
            validFlag = false;
        }
        if (validFlag){
            creatingPuzzle = false;
            ui->btn_LoadPuzzle->setEnabled(true);
            ui->btn_SolvePuzzle->setEnabled(true);
            ui->btn_CheckSolution->setEnabled(true);
            ui->btn_LoadRandomPuzzle->setEnabled(true);

            for(int i = 0; i < N*N; i++){
                if (squares[i]->text() == "0" || squares[i]->text() == ""){
                    squares[i]->text() = "";
                    empty[i / N][i % N] = 0;
                } else {
                    squares[i]->setEnabled(false);
                    empty[i / N][i % N] = squares[i]->text().toInt();
                }
            }
            m_sudoku.initPuzzle(empty);
            m_sudoku.solvePuzzle();
            ui->btn_CreatePuzzle->setText("Create Puzzle");
            //set starting values of puzzle
        }
    }
}
