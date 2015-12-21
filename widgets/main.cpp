#include <QApplication>
#include "colorslider.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ColorSlider colorSlider;
    colorSlider.setMin(10);
    colorSlider.setMax(100);
    colorSlider.show();
    return app.exec();
}