#ifndef OACPROYECTO_MENUWINDOW_H
#define OACPROYECTO_MENUWINDOW_H

#include <QMainWindow>
#include <MenuWindow.h>

namespace Ui {
    class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget* parent = nullptr);
    ~MenuWindow();

private:
    Ui::MenuWindow* ui;
};

#endif 