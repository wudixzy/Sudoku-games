#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QWidget>
#include "qvector.h"
#include "qpoint.h"
#include "qpainter.h"

enum ITEM_TYPE
{
    ITEM_1,
    ITEM_2,
    ITEM_3,
    ITEM_4,
    ITEM_5,
    ITEM_6,
    ITEM_7,
    ITEM_8,
    ITEM_9,
};

class Item
{
public:
    Item(){};
    Item(ITEM_TYPE t,int Startx,int Starty);
    ~Item(void){};

    void Draw(QPainter& painter,int nStartX,int nStartY,int nw,int nH);
private:
    QPoint mPoints;
    QPoint mPos;
    ITEM_TYPE mType;
};

#endif // ITEM_H
