#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    gameTime.setHMS(0,0,0);
    gameTimer=new QTimer(this);
    connect(gameTimer,SIGNAL(timeout()),this,SLOT(showTime()));
    isStarted=true;
    isStarted_1=true;
    ui->setupUi(this);
    gameArea=ui->widgetGameArea;
    setFixedSize(1000,1200);//设定主窗口大小
    setWindowTitle(tr("数独游戏"));//设计窗口标题
 //   QString styleSheet = "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, \
                          stop:0 rgba(230, 240, 255, 200), stop:1 rgba(230, 240, 255, 200));";

  //  this->setStyleSheet(styleSheet);
    myRegister=new RegisterDialog(this);//记录成绩页面
    myDifficulty=new Difficulty(this);//修改难度页面
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showTime()//时间
{
    static long long time_out=0;
    time_out++;
    gameTime=gameTime.addSecs(1);
    ui->timeLabel_2->setText(gameTime.toString("mm:ss"));
    mTime=gameTime.msecsSinceStartOfDay()/1000;
}
void MainWindow::on_beginButton_clicked()//开始/暂停/继续
{
    if (isStarted)
    {
        if(gameArea->sudokuBoard[0][0]==0)
        {
            gameArea->sudoku.refreashSudokuBoard();
            gameArea->sudoku.refreshPartlyBoard();
            for(int i = 0;i<9;i++)
            {
                for(int j =0;j<9;j++)
                {
                    gameArea->partlyBoard[i][j]=gameArea->sudoku.partlyBoard[i][j];
                    gameArea->sudokuBoard[i][j]=gameArea->sudoku.sudokuBoard[i][j];
                }
            }
        }
            gameArea->drawFixedRects = 1;
            gameArea->update();
            musicCheck_2=true;
            gameArea->emit musicStateChanged(musicCheck,musicCheck_2);
            isStarted = false; // 标记第一次点击已经触发
    }
    if(isStarted_1)
    {
        gameTimer->start(1000);
        isStarted_1=false;
        musicCheck_2=true;
        gameArea->emit musicStateChanged(musicCheck,musicCheck_2);
        ui->beginButton->setText("暂停");
    }
    else if(!isStarted_1)
    {
        gameTimer->stop();
        isStarted_1=true;
        musicCheck_2=false;
        gameArea->emit musicStateChanged(musicCheck,musicCheck_2);
        ui->beginButton->setText("继续");
    }


}

void MainWindow::on_pushButton_1_clicked()
{
    if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
            gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==1)
    {
        gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]=1;
        gameArea->scoreChange();
        showScore(mScore);
        gameArea->update();

    }
   else if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
            gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]!=1)
    {
        gameArea->wrongCondition=true;
       if(mScore>50)  mScore-=50;
        gameArea->update();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
            gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==2)
    {
        gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]=2;
        gameArea->scoreChange();
        showScore(mScore);
        gameArea->update();
    }
    else if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
             gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]!=2)
     {
         gameArea->wrongCondition=true;
         if(mScore>50) mScore-=50;
         showScore(mScore);
         gameArea->update();
     }
}


void MainWindow::on_pushButton_3_clicked()
{
    if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
            gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==3)
    {
        gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]=3;
         gameArea->scoreChange();
          showScore(mScore);
        gameArea->update();
    }
    else if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
             gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]!=3)
     {
         gameArea->wrongCondition=true;
         if(mScore>50)  mScore-=50;
          showScore(mScore);
         gameArea->update();
     }
}


void MainWindow::on_pushButton_4_clicked()
{
    if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
            gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==4)
    {
        gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]=4;
         gameArea->scoreChange();
          showScore(mScore);
        gameArea->update();
    }
    else if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
             gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]!=4)
     {
         gameArea->wrongCondition=true;
         if(mScore>50) mScore-=50;
         showScore(mScore);
         gameArea->update();
     }
}
void MainWindow::on_pushButton_5_clicked()
{
    if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
            gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==5)
    {
        gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]=5;
         gameArea->scoreChange();
          showScore(mScore);
        gameArea->update();
    }
    else if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
             gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]!=6)
     {
         gameArea->wrongCondition=true;
        if(mScore>50) mScore-=50;
         showScore(mScore);
         gameArea->update();
     }
}
void MainWindow::on_pushButton_6_clicked()
{
    if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
            gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==6)
    {
        gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]=6;
         gameArea->scoreChange();
          showScore(mScore);
        gameArea->update();
    }
    else if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
             gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]!=6)
     {
         gameArea->wrongCondition=true;
         if(mScore>50) mScore-=50;
         showScore(mScore);
         gameArea->update();
     }
}



void MainWindow::on_pushButton_7_clicked()
{
    if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
            gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==7)
    {
        gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]=7;
         gameArea->scoreChange();
         showScore(mScore);
        gameArea->update();
    }
    else if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
              gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]!=7)
      {
          gameArea->wrongCondition=true;
          if(mScore>50) mScore-=50;
          showScore(mScore);
          gameArea->update();
      }
}

void MainWindow::on_pushButton_8_clicked()
{
    if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
            gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==8)
    {
        gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]=8;
        gameArea->scoreChange();
         showScore(mScore);
        gameArea->update();
    }
    else if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
             gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]!=8)
     {
         gameArea->wrongCondition=true;
         if(mScore>50) mScore-=50;
         showScore(mScore);
         gameArea->update();
     }
}

void MainWindow::on_pushButton_9_clicked()
{
    if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
            gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==9)
    {
        gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]=9;
        gameArea->scoreChange();
        showScore(mScore);
        gameArea->update();
    }
    else if(gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]==0&&
             gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]!=9)
     {
         gameArea->wrongCondition=true;
         if(mScore>50) mScore-=50;
         showScore(mScore);
         gameArea->update();
     }
}

void MainWindow::showScore(int score)//显示分数
{
    ui->scoreLabel_2->setText((QString("%1").arg(score)));
    if(gameArea->finalFinish)
    {
        gameTimer->stop();
    }
    if(gameArea->finalFinish)
    {
       myRegister->show();
       myRegister->scoreShow();
    }
}

void MainWindow::on_reminderButton_clicked()//提示
{
    gameArea->partlyBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1]=gameArea->sudokuBoard[gameArea->gridIndex[0]-1][gameArea->gridIndex[1]-1];
    gameArea->update();
}

void MainWindow::on_newgameButton_clicked()//新一句
{
    gameTimer->stop();
    gameTime.setHMS(0,0,0,0);
    ui->timeLabel_2->setText(gameTime.toString("mm:ss"));
    isStarted=true;
    isStarted_1=true;
    gameArea->wrongCondition=gameArea->greatCondition=gameArea->goodCondition=gameArea->perfectCondition=0;
    gameArea->finalFinish=false;
    mScore=0;
    showScore(mScore);

    for(int i = 0 ;i<9;i++)
    {
        for(int j =0;j<9;j++)
        {
            gameArea->partlyBoard[i][j]=gameArea->sudokuBoard[i][j]=0;
        }
    }
    ui->beginButton->setText("开始");
    gameArea->update();
}


void MainWindow::on_pushButton_clicked()//显示记录成绩
{

        myRegister->myrank->show();

}


void MainWindow::on_pushButton_10_clicked()//难度选项
{
    myDifficulty->show();
}

void MainWindow::on_musicBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked)
    {
     musicCheck=true;
     gameArea->emit musicStateChanged(musicCheck,musicCheck_2);
    }
    else if(arg1==Qt::Unchecked)
    {
        musicCheck=false;
      gameArea->emit musicStateChanged(musicCheck,musicCheck_2);
    }
}
