#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H
#include <QGraphicsPixmapItem>
#include <QGraphicsEffect>

class pixmapItem : public QGraphicsPixmapItem
{

public:
    pixmapItem();
    void setIsButton(bool b);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool _isButton;

/*signals:
    void startHeat(bool b);*/
};

#endif // PIXMAPITEM_H
