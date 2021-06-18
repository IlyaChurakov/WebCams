#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(QApplication::applicationName() + "_" + QLocale::system().name());


    MainWindow w;
    w.show();
    return a.exec();
}
