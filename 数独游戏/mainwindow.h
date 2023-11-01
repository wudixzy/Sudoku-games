#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"difficulty.h"
#include <QMainWindow>
#include"sudoku.h"
#include"gamearea.h"
#include <rankingdialog.h>
#include <registerdialog.h>
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QLabel>
#include <QPixmap>
#include<QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
extern bool musicCheck;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     //void updateGameArea();
    Difficulty* myDifficulty;
    void showScore(int score);
    void showRegister();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_beginButton_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_reminderButton_clicked();

    void showTime();


    void on_newgameButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_10_clicked();

    void on_musicBox_stateChanged(int arg1);

private:
    QTimer* gameTimer;
    QTime gameTime;
    bool isStarted_1;
    bool isStarted;
    GameArea* gameArea;
    Ui::MainWindow *ui;
     QLabel wrongLabel;
     RegisterDialog* myRegister;
  //  Sudoku sudoku; // Sudoku 类的实例
};
#endif // MAINWINDOW_H
