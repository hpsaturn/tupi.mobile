#include <QApplication>
#include "tupmainwindow.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    TupMainWindow window;
    window.showMaximized();
    return app.exec();
}
