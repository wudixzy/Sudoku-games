#ifndef GAMEAREA_H
#define GAMEAREA_H
#include<QDebug>
#include <QObject>
#include <QWidget>
#include<QTime>
#include<QTimer>
#include <QSound>
#include<QMediaPlayer>
#include<QSoundEffect>
#include<QSoundEffect>
#include"item.h"
#include"sudoku.h"
#include <QMouseEvent>
extern int mTime;//用时
extern int mScore;//得分
extern bool musicCheck;
extern bool musicCheck_2;//用于控制暂停音乐
class GameArea:public QWidget
{
    Q_OBJECT
public:
    QVector<QVector<int>>sudokuBoard;
    QVector<QVector<int>> partlyBoard;
    int gridIndex[2];//目前选中的方格
    bool finalFinish;
    bool drawFixedRects;
    bool finishCondition;
    bool wrongCondition;
    bool goodCondition;
    bool greatCondition;
    bool perfectCondition;
    Sudoku sudoku;
    void checkFinish();
    void boardChange();
    void rightMusicshow();
    void wrongMusicshow();
    void musicShow();
    void backMusic();
    explicit GameArea(QWidget *parent=nullptr);//构造函数
    void DrawBKRects();//画背景
    void DrawBigRects();// 将中心9*9区域分为3*3的大区域
    void BeginGame();//开始游戏
    void PauseGame(bool Gamestatus);//暂停游戏
    void NewGame();//新开始一局游戏
    void Reminder();//提示
    void DrawFixedRects();//画已经固定的方块
    void CreatShadow();//选中方块时各个方向的阴影，提示计算
    void mousePressEvent(QMouseEvent *event);
    void DrawWrong(); //错误动画
    void DrawGood();
    void DrawGreat();
    void DrawPerfect();
    void DrawFinish();
    bool scoreChange();//分数变动
public slots:
    void handleGridClick(int index[]);

private slots:
    void toggleMusic(bool check,bool check_2);
    void HandlefinishPixtime();
    void HandlewrongPixtime();
    void HandlegoodPixtime();
    void HandlegreatPixtime();
    void HandleperfectPixtime();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
signals:
    void musicStateChanged(bool check,bool check_2);
    void gridClicked(int index[]);
    void sigUpdateScore(int nScore);//游戏分数信号
    void sigUdateTimeEslape(int tPlayed);//游戏时间信息
    void sigudRanking();//更新排行榜信号
protected:
   void paintEvent(QPaintEvent *event);//绘图事件

private:


   QTimer* wrongPixTime;
   QTimer* goodPixTime;
   QTimer* greatPixTime;
   QTimer* perfectPixTime;
   QTimer* finishPixTime;
   int bigWidth;//大格边框宽度
   QPixmap finishPix;
   QPixmap wrongPix;
   QPixmap goodPix;
   QPixmap greatPix;
   QPixmap perfectPix;
   Item FixItems;//已经固定数字的格子
   Item ChosenItems;//目前选中的格子
   QTime playTime;//游戏时间
   QMediaPlayer* backMusicPlayer;
   QSoundEffect* wrongMusic;
   QSoundEffect* rightMusic;

};

#endif // GAMEAREA_H
