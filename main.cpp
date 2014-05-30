#include <QtGui/QApplication>
#include "brprint3d.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    brprint3d brprint3d;
    brprint3d.show();
    return app.exec();
}
