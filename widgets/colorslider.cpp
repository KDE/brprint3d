#include "colorslider.h"

ColorSlider::ColorSlider(QWidget *parent) : QGraphicsView(parent)
{

}

void ColorSlider::setMin(int min)
{
    if (m_min == min)
        return;
    m_min = min;
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
