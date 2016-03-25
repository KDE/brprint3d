#include <QtGui/QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("KDE");

    QCoreApplication::setOrganizationDomain("kde.org");

    QCoreApplication::setApplicationName("brprint3d");

    return app.exec();
}
