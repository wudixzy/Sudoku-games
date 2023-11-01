#include "sudoku.h"
int level=1;
bool Sudoku::checkSquare(QVector<QVector<int>>& board, int x, int y, int num)
{
    int startRow = x - x % 3;
    int startCol = y - y % 3;

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::checkRow(QVector<QVector<int>>& board, int x, int num)
{
    for (int y = 0; y < 9; y++)
    {
        if (board[x][y] == num)
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::checkColumn(QVector<QVector<int>>& board, int y, int num)
{
    for (int x = 0; x < 9; x++)
    {
        if (board[x][y] == num)
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::isValid(QVector<QVector<int>>& board, int x, int y, int num) //检验该数字是否可填
{
    return checkSquare(board, x, y, num) &&
        checkRow(board, x, num) &&
        checkColumn(board, y, num);
}

bool Sudoku::solveSudoku(QVector<QVector<int>>& board) //存在局限，若[0,0]格子出现问题则无法回溯，因此利用返回值在generateSudoku中加入检查
{


    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if (board[x][y] == 0)
            {
                for (int num = 1; num <= 9; num++)
                {
                    if (isValid(board, x, y, num))
                    {
                        board[x][y] = num;
                        if (solveSudoku(board))
                        {
                            return true;
                        }
                        board[x][y] = 0; // 回溯，撤销填充的数字
                    }
                }
                return false;
            }
        }
    }
    return true;
}
bool Sudoku::solveSudoku_2(QVector<QVector<int>>& board) //版本二：仅计算是否有解，不直接填充进原棋盘
{
    QVector<QVector<int>>midBoard(9,QVector<int>(9,0));
    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            midBoard[i][j] = board[i][j];
        }
    }
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            if (midBoard[x][y] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(midBoard, x, y, num)) {
                        midBoard[x][y] = num;
                        if (solveSudoku(midBoard)) {
                            return true;
                        }
                        midBoard[x][y] = 0; // 回溯，撤销填充的数字
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void Sudoku::generateSudokuBoard(QVector<QVector<int>>& board)//生成完整棋盘
{
    srand(time(0));
    for (int i = 0; i < 11; i++)//经测试，先填入11个格子是出现解概率与计算量较为平衡的数字
    {

        int x = rand() % 9;
        int y = rand() % 9;
        int num = rand() % 9 + 1;
        if (board[x][y] != 0)
        {
            i--;
            continue;
        }
        if (isValid(board, x, y, num))
        {
            board[x][y] = num;
        }
    }
    if (!solveSudoku(board))generateSudokuBoard(board);//利用递归解决无解问题

}

void Sudoku::generatePartlyBoard(QVector <QVector<int>>& board, QVector<QVector<int>>& partlyBoard, int level = 1)//生成填空棋盘
{
    srand(time(0));
    for (int i = 0;i < 41 - level * 3;i++)
    {
        int x = rand() % 9;
        int y = rand() % 9;
        partlyBoard[x][y] = board[x][y];
    }
    if (!solveSudoku_2(partlyBoard))
    {
        for (int i = 0;i < 9;i++)
        {
            for (int j = 0;j < 9;j++)
            {
                partlyBoard[i][j] = 0;
            }
        }
        generatePartlyBoard(board, partlyBoard, level);
    }
}


Sudoku::Sudoku()
{
   // QVector<QVector<int>>sudokuBoard(9,QVector<int>(9,0));
     //QVector<QVector<int>>partlyBoard(9,QVector<int>(9,0));
    //下方代码有问题
     sudokuBoard.resize(9);
     for (int i = 0; i < 9; i++)
     {
            sudokuBoard[i].resize(9);

     }
     for(int i =0;i<9;i++)
      {
            for(int j =0;j<9;j++)
            {
                sudokuBoard[i][j]=0;
            }
       }
        // 初始化数独棋盘
     partlyBoard.resize(9);
        for (int i = 0; i < 9; i++)
        {
            partlyBoard[i].resize(9);

        }
        for(int i=0;i<9;i++)
        {
            for(int j =0;j<9;j++)
            {
                partlyBoard[i][j]=0;
            }
        }
            //初始化填空棋盘

   generateSudokuBoard(sudokuBoard); // 计算出完整数独棋盘
   generatePartlyBoard(sudokuBoard, partlyBoard, level);//计算出挖空棋盘
}
void Sudoku::refreashSudokuBoard()
{
    for(int i=0;i<9;i++)
    {
        for(int j = 0;j<9;j++)
        {
            sudokuBoard[i][j]=partlyBoard[i][j]=0;
        }
    }
    generateSudokuBoard(sudokuBoard);
}
void Sudoku::refreshPartlyBoard()
{
    generatePartlyBoard(sudokuBoard,partlyBoard,level);
}
Sudoku::~Sudoku()
{}
