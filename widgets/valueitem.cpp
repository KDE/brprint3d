#include "valueitem.h"
#include <QDebug>

valueItem::valueItem()
{
    setTextInteractionFlags(Qt::TextEditable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setPlainText("0  ");
}

void valueItem::keyPressEvent(QKeyEvent *event)
{
	// Finish editing when user press enter or return.
	if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
		setTextInteractionFlags(Qt::NoTextInteraction);
        emit _value(toPlainText().toInt());
		event->accept();
		return;
	}

	// TODO: Fix the values, those shouldn't be hardcoded.
	QIntValidator validator(0,100,this);

	// save current value of the text, unedited.
	QString currText = toPlainText();

	// edit the current value of the text
	QGraphicsTextItem::keyPressEvent(event);

	// get the new current value for validation.
	QString newCurrent = toPlainText();
	int unused = 0;

	// if invalid, get back to the old, valid, value.
	if (validator.validate(newCurrent, unused) == QValidator::Invalid) {
        setPlainText(currText);
	}
}

void valueItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsTextItem::mouseDoubleClickEvent(event);
    setTextInteractionFlags(Qt::TextEditable);
    setPlainText(QString());
}
