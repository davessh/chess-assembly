#include "MenuWindow.h"
#include "ui_MenuWindow.h"
#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"

MenuWindow::MenuWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    this->setFixedSize(780, 540);

    ui->centralwidget->setStyleSheet(
        "QWidget#centralwidget {"
        "    border-image: url(:/imagenes/fondoAjedrez.jpg) 0 0 0 0 stretch stretch;"
        "}"
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                stop:0 #F5DEB3, stop:0.5 #D2B48C, stop:1 #C19A6B);"
        "    color: #5D4037;"
        "    border: 3px solid #A0826D;"
        "    border-radius: 10px;"
        "    padding: 15px 30px;"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "    text-shadow: 1px 1px 2px rgba(255, 255, 255, 0.5);"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                stop:0 #FAEBD7, stop:0.5 #DEB887, stop:1 #D2B48C);"
        "    border: 3px solid #8B7355;"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                stop:0 #D2B48C, stop:0.5 #C19A6B, stop:1 #A0826D);"
        "    padding-top: 17px;"
        "    padding-bottom: 13px;"
        "}"
    );

    connect(ui->gameButton, &QPushButton::clicked, this, [this]() {
        MainWindow* juego = new MainWindow();
        juego->show();
        this->close();
        });

    connect(ui->exitButton, &QPushButton::clicked, []() {
        QApplication::quit();
        });
}

MenuWindow::~MenuWindow()
{
    delete ui;
}