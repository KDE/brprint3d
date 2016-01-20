#include "colorslider.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGradient>
#include <QResizeEvent>
#include <QGraphicsProxyWidget>

ColorSlider::ColorSlider(QWidget *parent) : QGraphicsView(parent)
, _minText(new QGraphicsSimpleTextItem())
, _maxText(new QGraphicsSimpleTextItem())
, _currText(new QGraphicsSimpleTextItem())
, _handler(new QGraphicsPolygonItem())
, _slider(new QGraphicsRectItem())
, _pixmap(new QGraphicsPixmapItem())
, _input(new valueItem())
, _background(new QGraphicsRectItem())
, _handlerMovementEnabled(true)
, _button(new QToolButton())
{
    setScene(new QGraphicsScene());
    setupViewFlags();
    setupHandler();
    setupSlider();
    setupInput();
    /* create a somewhat retangular shape for the scene */
    setSceneRect(0,0,100,25);
    _proxy = scene()->addWidget(_button);
    scene()->addItem(_minText);
    scene()->addItem(_slider);
    scene()->addItem(_maxText);
    scene()->addItem(_currText);
    scene()->addItem(_handler);
    scene()->addItem(_background);
    scene()->addItem(_input);
    connect(_input,&valueItem::_value,this,&ColorSlider::setValue);
}

bool ColorSlider::handlerMovementEnabled() const
{
	return _handlerMovementEnabled;
}

void ColorSlider::setHandlerMovementEnabled(bool enabled)
{
	if (_handlerMovementEnabled == enabled)
		return;
	_handlerMovementEnabled = enabled;
	emit handlerMovementEnabledChanged(enabled);
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

void ColorSlider::setPixmap(QPixmap pixmap, bool b)
{
    _button->setIcon(QIcon(pixmap));
    if(!b){
        _button->setEnabled(false);
    }
}

void ColorSlider::mouseMoveEvent(QMouseEvent *event)
{
	if (!_handlerMovementEnabled)
		return;

    if(handlerMove && (event->buttons() & Qt::LeftButton)){
		QPointF event_scene_pos = mapToScene(event->pos());
		QPointF event_item_pos = _slider->mapFromScene(event_scene_pos);

		int width = _slider->boundingRect().width();

		if(_slider->contains(QPointF(event_item_pos.x(), 1))){
			_handler->setX(event_scene_pos.x());
			double valuePercent = (100 * event_item_pos.x() / _slider->boundingRect().width()) / 100;
			int value = valuePercent * (max() - min()) + min();
			_currText->setText(QString::number(value)) ;
			_currText->setX(_handler->pos().x() - _currText->boundingRect().width() / 2);
			setCurrentValue(value);
		}
	}
}

void ColorSlider::mousePressEvent(QMouseEvent *event)
{
	if (_handlerMovementEnabled)
		handlerMove = true;
}

void ColorSlider::mouseReleaseEvent(QMouseEvent *event)
{
	if (!_handlerMovementEnabled)
		return;

    if(event->button() == Qt::LeftButton && handlerMove){
        handlerMove = false;
    }
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

void ColorSlider::setValue(int value)
{
	int delta = max() - min();
	double percent = (((value - min()) * 100) / delta) / 100.0; // get the percentage in fraction mode( 50% = 0.5, 100% = 1.0)
	double currX = _slider->boundingRect().width() * percent + _slider->pos().x();

	_handler->setX(currX);
	_currText->setText(QString::number(value));
	_currText->setX(_handler->pos().x() - _currText->boundingRect().width() / 2);
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

    _proxy->setX(0);
    _proxy->setY((sceneRect().height() / 2) - (_proxy->boundingRect().height() / 2) - spacing);

    _minText->setX(_proxy->pos().x() + _proxy->boundingRect().width());
    _minText->setY(_proxy->pos().y() + _proxy->boundingRect().height());
    _slider->setRect(0, 0,
    /* width  */	sceneRect().width() -  _proxy->boundingRect().width() - _input->boundingRect().width() - spacing,
    /* height */	_proxy->boundingRect().height() / 2);

    _slider->setX(_proxy->pos().x() + _proxy->boundingRect().width() + spacing);
    _slider->setY((sceneRect().height() / 2) - (_proxy->boundingRect().height() / 2) + spacing);

    _maxText->setX(_slider->pos().x() + _slider->boundingRect().width() - _maxText->boundingRect().width());
    _maxText->setY(_minText->pos().y());

    _handler->setX(_slider->pos().x());
    _handler->setY(_slider->pos().y() - _handler->boundingRect().height());

    _currText->setX(_handler->pos().x() - _currText->boundingRect().width() / 2);
    _currText->setY(_handler->pos().y() - _handler->boundingRect().height() - spacing);

    _input->setX(sceneRect().width() - _input->boundingRect().width() + spacing);
    _input->setY((sceneRect().height() / 2) - (_input->boundingRect().height() / 2) - spacing);

    _background->setRect(_input->boundingRect());
    _background->setPen(QPen(Qt::black));
    _background->setX(_input->pos().x());
    _background->setY(_input->pos().y());
    QLinearGradient currGradient(0, 0, _slider->boundingRect().width(), 0);
    currGradient.setStops(m_gradient);
    _slider->setBrush(QBrush(currGradient));
}
