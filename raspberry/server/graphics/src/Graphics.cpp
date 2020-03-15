#include <Graphics.h>
#include <QApplication>
#include <QLabel>

int graphics(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QLabel hello("Hello world!");

    hello.show();
    return app.exec();
}