#include <QApplication>
#include <QResource>
#include "tupmainwindow.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    QResource::registerResource("images.qrc");
    TupMainWindow window;
    window.showMaximized();
    return app.exec();
}
