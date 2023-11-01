#include "gamearea.h"
#include<QTime>
#define RECT_COLUMES    11
#define RECT_ROWS   11
#define RECT_WIDTH  80
#define RECT_HEIGHT 80
int mScore=0;
int mTime=0;
bool musicCheck=false;
bool musicCheck_2=true;
 //QVector<QVector<int>>gridNumbers(9,QVector<int>(9,0));
GameArea::GameArea(QWidget *parent):QWidget (parent), drawFixedRects(false)//构造函数
{

    level=1;
    mScore=0;
    mTime=0;
    musicCheck=0;
    //音乐功能
    backMusicPlayer=new QMediaPlayer;
    backMusicPlayer->setMedia(QUrl::fromLocalFile("D:/Qt_practice/myGame/backMusic.mp3"));
    backMusicPlayer->setVolume(50);
    connect(this,&GameArea::musicStateChanged,this,&GameArea::toggleMusic);
    wrongMusic=new QSoundEffect;
    rightMusic=new QSoundEffect;
    wrongMusic->setSource(QUrl::fromLocalFile("D:/Qt_practice/myGame/wrongMusic.wav"));
    rightMusic->setSource(QUrl::fromLocalFile("D:/Qt_practice/myGame/rightMusic.wav"));
    wrongMusic->setVolume(1.0);
    rightMusic->setVolume(1.0);
    //下方均为图片显示功能，利用定时器完成
    wrongPixTime=new QTimer(this);
    connect(wrongPixTime,&QTimer::timeout,this,&GameArea::HandlewrongPixtime);

    goodPixTime=new QTimer(this);
    greatPixTime=new QTimer(this);
    perfectPixTime=new QTimer(this);
    finishPixTime=new QTimer(this);
     connect(goodPixTime,&QTimer::timeout,this,&GameArea::HandlegoodPixtime);
     connect(greatPixTime,&QTimer::timeout,this,&GameArea::HandlegreatPixtime);
     connect(perfectPixTime,&QTimer::timeout,this,&GameArea::HandleperfectPixtime);
    connect(finishPixTime,&QTimer::timeout,this,&GameArea::HandlefinishPixtime);
    finishCondition=false;
    finalFinish=false;
    wrongCondition=false;
    goodCondition=false;
    greatCondition=false;
    perfectCondition=false;
    gridIndex[0]=gridIndex[1]=NULL;
    sudokuBoard.resize(9);//设置大小
    for(int i = 0;i<9;i++)
    {
        sudokuBoard[i].resize(9);
    }
    for(int i = 0;i<9;i++)
    {
        for(int j =0;j<9;j++)
        {
           sudokuBoard[i][j]=sudoku.sudokuBoard[i][j];//完成完整棋盘的填充
           //gridNumbers[i][j]=i*9+j+1;
        }
    }
    partlyBoard.resize(9);
    for(int i = 0;i<9;i++)
    {
         partlyBoard[i].resize(9);
    }
    for(int i = 0;i<9;i++)
    {
        for(int j =0;j<9;j++)
        {
            partlyBoard[i][j]=sudoku.partlyBoard[i][j];//完成挖空棋盘的填充
           //gridNumbers[i][j]=i*9+j+1;
        }
    }
    mScore = 0;
    setMinimumSize(RECT_COLUMES*RECT_WIDTH,RECT_ROWS*RECT_HEIGHT);
    connect(this, &GameArea::gridClicked, this, &GameArea::handleGridClick);
}
void GameArea::DrawBigRects()//绘制大九宫格边框
{
    QPainter painter(this);//定义本窗体的画笔
    QPen pen;
    pen.setBrush(QColor(245,245,245));//设置画笔颜色
    pen.setWidth(6);
    pen.setJoinStyle(Qt::RoundJoin);//设置画笔圆角连接
    painter.setPen(pen);//定义边框颜色和类型
    for(int i=0;i<RECT_COLUMES;i++)//遍历游戏区域
    {
        for(int j=0;j<RECT_ROWS;j++)
        {
            if(i==0||i==RECT_COLUMES-1||j==0||j==RECT_ROWS-1){}
            else if((i-1)%3==0&&(j-1)%3==0)
            {
                pen.setStyle(Qt::SolidLine);
                pen.setBrush(QColor(0,0,0));

                pen.setWidth(6);
                painter.setPen(pen);
                painter.drawRect(i*RECT_HEIGHT,j*RECT_WIDTH,RECT_WIDTH*3,RECT_HEIGHT*3);
            }
            //描粗大九宫格边框(不知道为什么左边细右边粗，在下方再次描了一次，粗细均匀了,amazing)
        }
    }
}
void GameArea::DrawBKRects()//绘制小边框以及实现颜色加深效果
{
    QPainter painter(this);//定义本窗体的画笔
    QPen pen;
    pen.setBrush(QColor(245,245,245));//设置画笔颜色
    pen.setWidth(3);
    pen.setJoinStyle(Qt::RoundJoin);//设置画笔圆角连接
    painter.setPen(pen);//定义边框颜色和类型
    for(int i=0;i<RECT_COLUMES;i++)//遍历游戏区域
    {
        for(int j=0;j<RECT_ROWS;j++)
        {

            if(i==0||i==RECT_COLUMES-1||j==0||j==RECT_ROWS-1)//画出大大九宫格边框
            {/*
                pen.setStyle(Qt::NoPen);//方块无边框
                painter.setBrush(QColor(230, 240, 255));
                pen.setBrush(QColor(0,0,0));
                painter.setPen(pen);
                painter.drawRect(i*RECT_HEIGHT,j*RECT_WIDTH,RECT_WIDTH,RECT_HEIGHT);
            */
             }



            else
            {
                if((i-1)%3==0&&(j-1)%3==0)//再次描大九宫格边框
                {
                    pen.setStyle(Qt::SolidLine);
                    pen.setBrush(QColor(0,0,0));
                    painter.setBrush(QColor(250,250,250));
                    pen.setWidth(6);
                    painter.setPen(pen);
                    painter.drawRect(i*RECT_HEIGHT,j*RECT_WIDTH,RECT_WIDTH*3,RECT_HEIGHT*3);
                }

                    pen.setWidth(3);
                    pen.setStyle(Qt::SolidLine);
                    pen.setBrush(QColor(0,0,0));
                    painter.setBrush(QColor(250,250,250));
                    painter.setPen(pen);
                    painter.drawRect(i*RECT_HEIGHT,j*RECT_WIDTH,RECT_WIDTH,RECT_HEIGHT);//画小格边框

            }
            if(gridIndex[0]>=1&&gridIndex[0]<=9&&gridIndex[1]>=0&&gridIndex[1]<=9)//点击之后的颜色加深效果
            {
                pen.setWidth(3);
                pen.setStyle(Qt::SolidLine);
                pen.setBrush(QColor(0,0,0));
                painter.setBrush(QColor(180,200,255));
                painter.setPen(pen);
                painter.drawRect((gridIndex[1])*RECT_HEIGHT,(gridIndex[0])*RECT_WIDTH,RECT_WIDTH,RECT_HEIGHT);//所点击方格颜色最深


                pen.setWidth(3);
                pen.setStyle(Qt::SolidLine);
                pen.setBrush(QColor(0,0,0));
                painter.setBrush(QColor(230,240,255));
                painter.setPen(pen);
                for(int i=0;i<9;i++)//方格所在行列颜色加深
                {
                    if(i+1!=gridIndex[0])painter.drawRect((gridIndex[1])*RECT_HEIGHT,(i+1)*RECT_WIDTH,RECT_WIDTH,RECT_HEIGHT);
                    if(i+1!=gridIndex[1])painter.drawRect((i+1)*RECT_HEIGHT,(gridIndex[0])*RECT_WIDTH,RECT_WIDTH,RECT_HEIGHT);
                }
            }




        }
       /* for(int i =1;i<=7;i+=3)//有误代码，错误已经忘记力
        {
            for(int j =1;j<=7;j+=3)
            {
                 pen.setStyle(Qt::SolidLine);
                 pen.setBrush(QColor(0,0,0));
                 painter.setBrush(QColor(245,245,245));
                 pen.setWidth(6);
                 painter.setPen(pen);
                 painter.drawRect(i*RECT_HEIGHT,j*RECT_WIDTH,RECT_WIDTH*3,RECT_HEIGHT*3);
            }

        }
        */


    }
    DrawBigRects();
}
/*void GameArea::DrawFixedRects(int number)//一开始准备用含参的函数
{
    QFont font;
    QPainter painter(this);
    font.setPixelSize(20); // 设置字体大小
    painter.setFont(font); // 设置字体

    QBrush brush;
    brush.setColor(QColor(Qt::black));
    brush.setStyle(Qt::Dense5Pattern);
    painter.setBrush(brush); // 定义填充的颜色或格式
    painter.setPen(QPen(QColor(Qt::black), 2)); // 定义边框的颜色和宽度

    //QRect rect(0, 0, RECT_WIDTH, RECT_HEIGHT); // 创建绘制方块的矩形

    FixItems.Draw(painter, 0,0,RECT_WIDTH,RECT_HEIGHT); // 调用 mFixItems 对象的 Draw 方法绘制已固定的方块
}
*/

void GameArea::DrawFixedRects()
{
    QFont font;
    QPainter painter(this);
    font.setPointSize(20); // 设置字体大小
    font.setBold(true); // 设置字体加粗
    font.setWeight(QFont::Bold); // 设置字体粗细

    painter.setFont(font);

    QBrush brush;
    brush.setColor(QColor(Qt::black));
    brush.setStyle(Qt::SolidPattern); // 使用实心填充
    painter.setBrush(brush);
    painter.setPen(QPen(QColor(Qt::black), 2));

    // 绘制中间9x9方格中的数字
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            // 计算方格的位置
            int startX = RECT_WIDTH + j * RECT_WIDTH;
            int startY = RECT_HEIGHT + i * RECT_HEIGHT;

            // 绘制数字
            if (partlyBoard[i][j] != 0)
                painter.drawText(QRect(startX, startY, RECT_WIDTH, RECT_HEIGHT),
                                 Qt::AlignCenter, QString::number(partlyBoard[i][j]));
        }
    }
}
void GameArea::paintEvent(QPaintEvent *)
{


        QPainter painter(this);

        if(drawFixedRects)
        {
            DrawBKRects();
            DrawFixedRects();
        }
        if (!drawFixedRects)//防止重复绘图
        {
            DrawBKRects();
        }

        if(wrongCondition)
        {
            DrawWrong();
            wrongMusicshow();
        }
        if(goodCondition)DrawGood();
        if(greatCondition)DrawGreat();
        if(perfectCondition)DrawPerfect();

       // if(finishCondition)DrawFinish();
}

void GameArea::mousePressEvent(QMouseEvent *event)//计算坐标，发出点击信号
{
    int x = event->x();
    int y = event->y();

    int col = x / RECT_WIDTH;
    int row = y / RECT_HEIGHT;//计算坐标

    if (col >= 1 && col <= 9 && row >= 1 && row <= 9)
    {

        gridIndex[0]=row;
        gridIndex[1]=col;
        emit gridClicked(gridIndex);
    }
}
void GameArea::handleGridClick(int index[2])
{
    // 处理方格点击事件，根据方格索引执行你想要的操作
    qDebug() << "Grid clicked:" << "("<<index[0]<<","<<index[1]<<")";
    update();
}
void GameArea::DrawFinish()//结束动画
{
    QPainter painter(this);
    finishPix.load("D:/Qt_practice/myGame/finish.jpg");
    painter.drawPixmap(3*RECT_WIDTH,3*RECT_HEIGHT,5*RECT_WIDTH,5*RECT_HEIGHT,finishPix);

        finishPixTime->start(1000);
}
void GameArea::HandlefinishPixtime()
{
    finishCondition=false;
    finishPixTime->stop();
    update();
}
void GameArea::DrawWrong() //错误动画
{
    QPainter painter(this);
    wrongPix.load("D:/Qt_practice/myGame/wrong.jpg");

    painter.drawPixmap(3*RECT_WIDTH,3*RECT_HEIGHT,5*RECT_WIDTH,5*RECT_HEIGHT,wrongPix);

        wrongPixTime->start(800);
}
void GameArea::HandlewrongPixtime()
{
    wrongCondition=false;
    wrongPixTime->stop();
    update();
}
void GameArea::DrawGood()//单行/单列/单九宫格完成动画
{
    QPainter painter(this);
    goodPix.load("D:/Qt_practice/myGame/good.jpg");
    painter.drawPixmap(3*RECT_WIDTH,3*RECT_HEIGHT,5*RECT_WIDTH,5*RECT_HEIGHT,goodPix);
    goodPixTime->start(800);
}
void GameArea::HandlegoodPixtime()
{
    goodCondition=false;
    goodPixTime->stop();
    update();
}
void GameArea::DrawGreat()//行列/行九/列九完成动画
{
    QPainter painter(this);
    greatPix.load("D:/Qt_practice/myGame/great.jpg");

    painter.drawPixmap(3*RECT_WIDTH,3*RECT_HEIGHT,5*RECT_WIDTH,5*RECT_HEIGHT,greatPix);

    greatPixTime->start(800);
}
void GameArea::HandlegreatPixtime()
{
    greatCondition=false;
    greatPixTime->stop();
    update();
}
void GameArea::DrawPerfect()//行列九完成动画
{
    QPainter painter(this);
    perfectPix.load("D:/Qt_practice/myGame/perfect.jpg");

        painter.drawPixmap(3*RECT_WIDTH,3*RECT_HEIGHT,5*RECT_WIDTH,5*RECT_HEIGHT,perfectPix);

        perfectPixTime->start(800);
}
void GameArea::HandleperfectPixtime()
{
    perfectCondition=false;
    perfectPixTime->stop();
    update();
}
void GameArea::boardChange()//困难模式特色设计：使棋盘顺时针旋转90度
{
    int midBoard[9][9];
     for (int i = 0;i < 9;i++)
       {
           for (int j = 0;j < 9;j++)
           {
               midBoard[j][9 - 1 - i] = sudokuBoard[i][j];
           }
       }
       for (int i = 0;i < 9;i++)
       {
           for (int j = 0;j < 9;j++)
           {
               sudokuBoard[i][j] = midBoard[i][j];
           }
       }
       for (int i = 0;i < 9;i++)
         {
             for (int j = 0;j < 9;j++)
             {
                 midBoard[j][9 - 1 - i] = partlyBoard[i][j];
             }
         }
         for (int i = 0;i < 9;i++)
         {
             for (int j = 0;j < 9;j++)
             {
                 partlyBoard[i][j] = midBoard[i][j];
             }
         }
}
bool GameArea::scoreChange()//计算＋显示分数改变 后续加上了判定是否完成的功能
{
    int Square=2,Column=2,Row=2;
    if(partlyBoard[gridIndex[0]-1][gridIndex[1]-1]==sudokuBoard[gridIndex[0]-1][gridIndex[1]-1])mScore+=50;
    for(int i =0;i<9;i++)
    {
        if(partlyBoard[i][gridIndex[1]-1]==0)Row=1;
        if(partlyBoard[gridIndex[0]-1][i]==0)Column=1;
    }
    int startRow = gridIndex[0]-1 - (gridIndex[0]-1) % 3;
    int startCol = gridIndex[1]-1 - (gridIndex[1]-1) % 3;

    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startCol; j < startCol + 3; j++)
        {
            if (partlyBoard[i][j] == 0)
            {
                Square=1;
            }
        }
    }
    int addScore=200*Square*Column*Row;
    if(level==3&&addScore>=400)boardChange();
    if(addScore==400)
    {
        goodCondition=true;
        update();
    }
    else if(addScore==800)
    {
        greatCondition=true;
        update();
    }
    else if(addScore==1600)
    {
        perfectCondition=true;
        update();
    }

    mScore=mScore-200+addScore;
    bool check=true;
    //判断是否完成
    for(int i =0;i<9;i++)
    {
        for(int j =0;j<9;j++)
        {
            if(partlyBoard[i][j]!=sudokuBoard[i][j])
            {
                check=false;
                break;
            }

        }
    }
    if(check)
    {
        finishCondition=finalFinish=true;
        musicCheck_2=false;
        mScore=mScore-mTime;
        update();

    }
 /*   if(level==3&&!check&&addScore>200)
    {
        boardChange();
    }
 */
    rightMusicshow();
    return true;
}
void GameArea::backMusic()//背景音乐
{
      if(musicCheck&&musicCheck_2)
      {
          backMusicPlayer->play();
          connect(backMusicPlayer,&QMediaPlayer::mediaStatusChanged,this,&GameArea::onMediaStatusChanged);
          //实现背景音乐循环播放
      }
      else backMusicPlayer->pause();
}
void GameArea::rightMusicshow()//因为正确时会造成分数改变，因此在scoreChange中调用了本函数
{
   if(musicCheck&&musicCheck_2)rightMusic->play();
}
void GameArea::wrongMusicshow()
{
   if(musicCheck&&musicCheck_2) wrongMusic->play();
}
void GameArea::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::EndOfMedia)
    {
        backMusicPlayer->setPosition(0);
        backMusicPlayer->play();
    }
}
void GameArea::toggleMusic(bool check,bool check_2)//一开始设计有问题，导致后续信号发送在mainwindow函数中发生
{
    if(check&& check_2)backMusicPlayer->play();
    else backMusicPlayer->pause();
}
