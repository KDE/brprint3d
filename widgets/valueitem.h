#ifndef VALUEITEM_H
#define VALUEITEM_H
#include <QGraphicsTextItem>
#include <QIntValidator>
#include <QMessageBox>
#include <QKeyEvent>
#include <iostream>

class valueItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    explicit valueItem();
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    void _value(int v);
};

#endif // VALUEITEM_H
