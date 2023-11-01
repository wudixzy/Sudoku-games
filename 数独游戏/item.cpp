#include "item.h"
#include<QTime>
Item::Item(ITEM_TYPE t,int x, int y)
{
    mPos=QPoint(x,y);
    mType = t;
}
void Item::Draw(QPainter &painter,int nStartX,int nStartY,int nW,int nH)
{
    QPoint pt=mPoints;
    painter.drawRect(QRect(nStartX+pt.x()*nW,nStartY+pt.y()*nH,nW,nH));
}
