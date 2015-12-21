/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 Copyright (C) 2015 BRPrint3D Authors

 This file is part of the BRPrint3D project

 BRPrint3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 BRPrint3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with BRPrint3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/

#include <QGraphicsView>
#include <QGradient>

class QGraphicsSimpleTextItem;

/* Base class for a ColorSlider, you can set the min, max and color gradient
 * and retrieve them */
class ColorSlider : public QGraphicsView {
    Q_OBJECT
    Q_PROPERTY(int min READ min WRITE setMin NOTIFY minValueChanged);
    Q_PROPERTY(int max READ max WRITE setMax NOTIFY maxValueChanged);
    Q_PROPERTY(int currentValue READ currentValue WRITE setCurrentValue NOTIFY currentValueChanged);
    Q_PROPERTY(QGradient gradient READ gradient WRITE setGradient NOTIFY gradientChanged);
    
public:
    ColorSlider(QWidget *parent = 0);
    void setMin(int min);
    void setMax(int max);
    void setCurrentValue(int curr);
    void setGradient(const QGradient& gradient);

    QGradient gradient() const;
    int min() const;
    int max() const;
    int currentValue() const;

protected:
    virtual void resizeEvent(QResizeEvent* event);

signals:
    void currentValueChanged(int currValue);
    void minValueChanged(int minValue);
    void maxValueChanged(int maxValue);
    void gradientChanged(QGradient gradient);

private:
    void setupViewFlags();

    int m_min;
    int m_max;
    int m_currentValue;
    QGradient m_gradient;

    QGraphicsSimpleTextItem *_minText;
    QGraphicsSimpleTextItem *_maxText;
    QGraphicsSimpleTextItem *_currText;
};