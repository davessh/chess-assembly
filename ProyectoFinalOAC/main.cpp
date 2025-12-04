#include "MenuWindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MenuWindow* w = new MenuWindow();  
    w->show();
    return a.exec();
}