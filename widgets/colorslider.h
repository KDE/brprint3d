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
#include "valueitem.h"
#include "pixmapitem.h"

class QGraphicsSimpleTextItem;

/* Base class for a ColorSlider, you can set the min, max and color gradient
 * and retrieve them */
class ColorSlider : public QGraphicsView {
    Q_OBJECT
    Q_PROPERTY(int min READ min WRITE setMin NOTIFY minValueChanged);
    Q_PROPERTY(int max READ max WRITE setMax NOTIFY maxValueChanged);
    Q_PROPERTY(int currentValue READ currentValue WRITE setCurrentValue NOTIFY currentValueChanged);
    Q_PROPERTY(QGradientStops gradient READ gradient WRITE setGradient NOTIFY gradientChanged);

public:
    ColorSlider(QWidget *parent = 0);
    void setMin(int min);
    void setMax(int max);
    void setCurrentValue(int curr);
    void setGradient(const QGradientStops &gradient);
    void setPixmap(QPixmap pixmap,bool isButton);

    QGradientStops gradient() const;
    int min() const;
    int max() const;
    int currentValue() const;

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void currentValueChanged(int currValue);
    void minValueChanged(int minValue);
    void maxValueChanged(int maxValue);
    void gradientChanged(QGradientStops gradient);

private:
    void setupViewFlags();
    void setupHandler();
    void setupSlider();
    void setupInput();
    void setValue(int value);
    bool handlerMove;
    int m_min;
    int m_max;
    int m_currentValue;
    QGradientStops m_gradient;

    QGraphicsSimpleTextItem *_minText;
    QGraphicsSimpleTextItem *_maxText;
    QGraphicsSimpleTextItem *_currText;
    QGraphicsPolygonItem *_handler;
    QGraphicsRectItem *_slider;
    pixmapItem *_pixmap;
    valueItem *_input;
    QGraphicsRectItem *_background;
};
