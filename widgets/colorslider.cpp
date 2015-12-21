#include "colorslider.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGradient>

ColorSlider::ColorSlider(QWidget *parent) : QGraphicsView(parent)
, _minText(new QGraphicsSimpleTextItem())
, _maxText(new QGraphicsSimpleTextItem())
, _currText(new QGraphicsSimpleTextItem())
{
    setScene(new QGraphicsScene());

    /* create a somewhat retangular shape for the scene */
    setSceneRect(0,0,100,25);
    scene()->addItem(_minText);
    scene()->addItem(_maxText);
    scene()->addItem(_currText);
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
