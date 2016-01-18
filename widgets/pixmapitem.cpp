#include "pixmapitem.h"

pixmapItem::pixmapItem()
{

}

void pixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mousePressEvent(event);
    if(_isButton){
       // emit startHeat(true);
    }
}

void pixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
//This function set the style if this pixmap have actions like a button
void pixmapItem::setIsButton(bool b)
{
  _isButton = b;
}
