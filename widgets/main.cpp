#include <QApplication>
#include "colorslider.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ColorSlider colorSlider;
    colorSlider.show();
    return app.exec();
}