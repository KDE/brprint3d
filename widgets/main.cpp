#include <QApplication>
#include "colorslider.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ColorSlider colorSlider;

    QGradientStops gradient;
    gradient << qMakePair(0,QColor(Qt::blue))
             << qMakePair(0.25,QColor(Qt::green))
             << qMakePair(0.5,QColor(Qt::yellow))
             << qMakePair(1,QColor(Qt::red));

    colorSlider.setMin(10);
    colorSlider.setMax(100);
    colorSlider.setGradient(gradient);
    colorSlider.setPixmap(QPixmap(":/Icons/Icons/bed.png"),true);
    colorSlider.show();
    return app.exec();
}
