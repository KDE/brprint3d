#include "colorslider.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGradient>
#include <QResizeEvent>
#include <QDebug>

ColorSlider::ColorSlider(QWidget *parent) : QGraphicsView(parent)
, _minText(new QGraphicsSimpleTextItem())
, _maxText(new QGraphicsSimpleTextItem())
, _currText(new QGraphicsSimpleTextItem())
, _handler(new QGraphicsPolygonItem())
{
    setScene(new QGraphicsScene());
    setupViewFlags();
    setupHandler();

    /* create a somewhat retangular shape for the scene */
    setSceneRect(0,0,100,25);
    scene()->addItem(_minText);
    scene()->addItem(_maxText);
    scene()->addItem(_currText);
    scene()->addItem(_handler);
}

void ColorSlider::setMin(int min)
{
    if (m_min == min)
        return;
    m_min = min;

    /* Try to position the minText on the left/center of the dialog */
    QFontMetrics fm(font());
    _minText->setText(QString::number(m_min));
    const int height = fm.height();
    _minText->setX(0);
    _minText->setY((sceneRect().height() / 2) - (height / 2));

    emit minValueChanged(min);
}

void ColorSlider::setMax(int max)
{
    if (m_max == max)
        return;
    m_max = max;

    QFontMetrics fm(font());
    _maxText->setText(QString::number(m_max));
    const int height = fm.height();
    const int width = fm.width(_maxText->text());
    _maxText->setX(sceneRect().width() - width);
    _maxText->setY((sceneRect().height() / 2) - (height / 2));
    emit maxValueChanged(max);
}

void ColorSlider::setCurrentValue(int curr)
{
    if (m_currentValue == curr)
        return;
    m_currentValue = curr;
    emit currentValueChanged(curr);
}

void ColorSlider::setGradient(const QGradient& gradient)
{
    if (m_gradient == gradient)
        return;
    m_gradient = gradient;
    emit gradientChanged(gradient);
}

int ColorSlider::min() const
{
    return m_min;
}

int ColorSlider::max() const
{
    return m_max;
}

int ColorSlider::currentValue() const
{
    return m_currentValue;
}

QGradient ColorSlider::gradient() const
{
    return m_gradient;
}

void ColorSlider::setupViewFlags()
{
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene()->setItemIndexMethod(QGraphicsScene::NoIndex);
        setOptimizationFlags(QGraphicsView::DontSavePainterState);
        setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        setMouseTracking(true);
}

void ColorSlider::setupHandler()
{   QPolygonF p;
    p.append(QPointF(-5,0));
    p.append(QPointF(0,-10));
    p.append(QPointF(5,0));
    p.append(QPointF(-5,0));
    _handler->setPolygon(p);
    QBrush brush(Qt::black);
    _handler->setBrush(brush);
    _handler->setRotation(180);

}

void ColorSlider::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
    setSceneRect(0, 0, event->size().width(), event->size().height());

    QFontMetrics fm(font());
    const int height = fm.height();
    _minText->setX(0);
    _minText->setY((sceneRect().height() / 2) - (height / 2));

    const int width = fm.width(_maxText->text());
    _maxText->setX(sceneRect().width() - width);
    _maxText->setY((sceneRect().height() / 2) - (height / 2));

    _handler->setX(50);
    _handler->setY((sceneRect().height() / 2) - (_handler->boundingRect().height()/2)-10);
}
