#ifndef SUDOKU_H
#define SUDOKU_H
#include <cstdlib>
#include<ctime>
#include <QObject>
#include <QWidget>
#include<QVector>
extern int level;
class Sudoku
{
private:

public:
    QVector<QVector<int>>sudokuBoard;
    QVector<QVector<int>>partlyBoard;

    bool checkSquare(QVector<QVector<int>>& board, int x, int y, int num);
    bool checkRow(QVector<QVector<int>>& board, int x, int num);
    bool checkColumn(QVector<QVector<int>>& board, int y, int num) ;
    bool isValid(QVector<QVector<int>>& board, int x, int y, int num);
    bool solveSudoku(QVector<QVector<int>>& board);
    bool solveSudoku_2(QVector<QVector<int>>& board);
    void generateSudokuBoard(QVector<QVector<int>>& board);
    void generatePartlyBoard(QVector <QVector<int>>& board, QVector<QVector<int>>& partlyBoard, int level );
    void refreashSudokuBoard();
    void refreshPartlyBoard();
    Sudoku();
    ~Sudoku();
};

#endif // SUDOKU_H
