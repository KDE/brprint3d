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
, _slider(new QGraphicsRectItem())
, _pixmap(new pixmapItem())
, _input(new valueItem())
, _background(new QGraphicsRectItem())
{
    setScene(new QGraphicsScene());
    setupViewFlags();
    setupHandler();
    setupSlider();
    setupInput();
    /* create a somewhat retangular shape for the scene */
    setSceneRect(0,0,100,25);
    scene()->addItem(_pixmap);
    scene()->addItem(_minText);
    scene()->addItem(_slider);
    scene()->addItem(_maxText);
    scene()->addItem(_currText);
    scene()->addItem(_handler);
    scene()->addItem(_background);
    scene()->addItem(_input);
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

void ColorSlider::setGradient(const QGradientStops& gradient)
{
    if (m_gradient == gradient)
        return;

    m_gradient = gradient;
    QLinearGradient  currGradient(0, 0, _slider->boundingRect().width(), 0);
    currGradient.setStops(m_gradient);
    _slider->setBrush(QBrush(currGradient));
    emit gradientChanged(gradient);
}

void ColorSlider::setPixmap(QPixmap pixmap, bool isButton)
{
    _pixmap->setPixmap(pixmap);
    _pixmap->setIsButton(isButton);
}

/*void ColorSlider::mouseMoveEvent(QMouseEvent *event)
{   QPointF mapScene = mapToScene(event->pos());
    QPointF mapItem = _slider->mapFromScene(mapScene);
    int currPos = mapItem.x();
    int _max = _slider->pos().x()+_slider->boundingRect().width(), _min = _slider->pos().x();
    int delta = _max - _min;
    if(handlerMove && (event->buttons() & Qt::LeftButton)){
        if( (currPos < (_slider->pos().x() + _slider->boundingRect().width())) && currPos > (_slider->pos().x())){
            _handler->setX(currPos);
            int currValue = ((float)(currPos - _min)/delta)*100;
            _currText->setText(QString::number(currValue)) ;
			_currText->setX(_handler->pos().x() - _currText->boundingRect().width() / 2);
            setCurrentValue(currPos);
        }
    }
}

void ColorSlider::mousePressEvent(QMouseEvent *event)
{
    handlerMove = true;
}

void ColorSlider::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && handlerMove){
        handlerMove = false;
    }
}
*/
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

QGradientStops ColorSlider::gradient() const
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
        setMouseTracking(false);
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

void ColorSlider::setupSlider()
{
    _slider->setPen(QPen(QBrush(Qt::black), 1));
}

void ColorSlider::setupInput()
{
    _input->setX(sceneRect().width() - _input->boundingRect().width());
    _input->setY((sceneRect().height() / 2) - (_input->boundingRect().height() / 2));
}

void ColorSlider::resizeEvent(QResizeEvent* event)
{
	/* Positionings:
	 * First is the Pixmap
	 * on the bottom left, between the slider and the pixmap, it's the minimum value
	 * on the bottom right, between the slider till the end of the widget, it's the maximum value.
	 * handler is above the slider
	 * current text is above the slider.
	 *
	 * be careful when editing this.
	 */

	int spacing = 4; //TODO: we need to find an resolution independent way to do that.

	QGraphicsView::resizeEvent(event);
    setSceneRect(0, 0, event->size().width(), event->size().height());

    _pixmap->setX(0);
    _pixmap->setY((sceneRect().height() / 2) - (_pixmap->boundingRect().height() / 2));

    _minText->setX(_pixmap->pos().x() + _pixmap->boundingRect().width());
    _minText->setY(_pixmap->pos().y() + _pixmap->boundingRect().height() + 2);

	_slider->setRect(0, 0,
    /* width  */	sceneRect().width() -  _pixmap->boundingRect().width() - _input->boundingRect().width() - spacing,
	/* height */	_pixmap->boundingRect().height());

    _slider->setX(_pixmap->pos().x() + _pixmap->boundingRect().width() + spacing);
    _slider->setY(_pixmap->pos().y());

    _maxText->setX(_slider->pos().x() + _slider->boundingRect().width() - _maxText->boundingRect().width());
    _maxText->setY(_minText->pos().y());

    _handler->setX(_slider->pos().x());
    _handler->setY(_slider->pos().y() - _handler->boundingRect().height());

    _currText->setX(_handler->pos().x() - _currText->boundingRect().width() / 2);
    _currText->setY(_handler->pos().y() - _handler->boundingRect().height() - (spacing *2));

    _input->setX(sceneRect().width() - _input->boundingRect().width());
    _input->setY((sceneRect().height() / 2) - (_input->boundingRect().height() / 2));

    _background->setRect(_input->boundingRect());
    _background->setPen(QPen(Qt::black));
    _background->setX(_input->pos().x());
    _background->setY(_input->pos().y());
    QLinearGradient currGradient(0, 0, _slider->boundingRect().width(), 0);
    currGradient.setStops(m_gradient);
    _slider->setBrush(QBrush(currGradient));
}
