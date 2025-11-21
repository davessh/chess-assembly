#include <QApplication>
#include "../GUI/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("Chess");
    w.show();

    return app.exec();  // bucle de eventos de Qt
}