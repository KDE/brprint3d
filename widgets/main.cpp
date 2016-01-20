#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "colorslider.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	QWidget *window = new QWidget();
	QVBoxLayout *layout = new QVBoxLayout();
	QLabel *l1 = new QLabel("Mouse Enabled");

	ColorSlider *colorSlider1 = new ColorSlider();

    QGradientStops gradient;
    gradient << qMakePair(0,QColor(Qt::blue))
             << qMakePair(0.25,QColor(Qt::green))
             << qMakePair(0.5,QColor(Qt::yellow))
             << qMakePair(1,QColor(Qt::red));

    colorSlider1->setMin(10);
    colorSlider1->setMax(100);
    colorSlider1->setGradient(gradient);
    colorSlider1->setPixmap(QPixmap(":/Icons/Icons/bed.png"),true);

	ColorSlider *colorSlider2 = new ColorSlider();

    gradient << qMakePair(0,QColor(Qt::blue))
             << qMakePair(0.25,QColor(Qt::green))
             << qMakePair(0.5,QColor(Qt::yellow))
             << qMakePair(1,QColor(Qt::red));

	QLabel *l2 = new QLabel("Mouse not enabled");
    colorSlider2->setMin(10);
    colorSlider2->setMax(100);
    colorSlider2->setGradient(gradient);
    colorSlider2->setPixmap(QPixmap(":/Icons/Icons/bed.png"),false);
	colorSlider2->setHandlerMovementEnabled(false);

	layout->addWidget(l1);
	layout->addWidget(colorSlider1);
	layout->addWidget(l2);
	layout->addWidget(colorSlider2);
	window->setLayout(layout);
	window->show();

    return app.exec();
}
