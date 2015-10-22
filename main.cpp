#include "brprint3d.h"
#include <QApplication>
#include <Windows/loading.h>
#include <QTranslator>
#include <QSettings>
#include <QFontDatabase>
#include <QDebug>
#include <QLocale>
#include <QStyleFactory>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("BrPrint 3D Solutions");

    QCoreApplication::setOrganizationDomain("www.br-print3d.com.br");

    QCoreApplication::setApplicationName("Br-Print3D");

    //DEFININDO FONTE

    QString fontPath = ":/Fonts/Ubuntu-R.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId != -1)
    {
        QFont font("MyFont");
        app.setFont(font);
    }
/*
    QTranslator translator;
    QLocale locale;
    QString lang = QLocale::languageToString(locale.language());

    if(lang=="Portuguese")
    {
      translator.load(":/Translations/PT_portuguese.qm");
      app.installTranslator(&translator);

    }
    else
    {
        translator.load(":/Translations/EN_english.qm");
        app.installTranslator(&translator);

    }*/
    BrPrint3D w;

    w.show();
    w.init();


    return app.exec();
}
