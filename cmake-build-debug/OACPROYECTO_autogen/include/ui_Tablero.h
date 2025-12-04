/********************************************************************************
** Form generated from reading UI file 'Tablero.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLERO_H
#define UI_TABLERO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMenu;
    QAction *actionNew_Game;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *contenedor;
    QHBoxLayout *horizontalLayout;
    QGridLayout *tablero;
    QWidget *stats;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelBlack;
    QLabel *labelWhite;
    QMenuBar *menubar;
    QMenu *menuJuego;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1236, 766);
        actionMenu = new QAction(MainWindow);
        actionMenu->setObjectName("actionMenu");
        actionNew_Game = new QAction(MainWindow);
        actionNew_Game->setObjectName("actionNew_Game");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        contenedor = new QWidget(centralwidget);
        contenedor->setObjectName("contenedor");
        sizePolicy.setHeightForWidth(contenedor->sizePolicy().hasHeightForWidth());
        contenedor->setSizePolicy(sizePolicy);
        contenedor->setAutoFillBackground(false);
        horizontalLayout = new QHBoxLayout(contenedor);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName("horizontalLayout");
        tablero = new QGridLayout();
        tablero->setObjectName("tablero");

        horizontalLayout->addLayout(tablero);

        stats = new QWidget(contenedor);
        stats->setObjectName("stats");
        verticalLayout_2 = new QVBoxLayout(stats);
        verticalLayout_2->setObjectName("verticalLayout_2");
        labelBlack = new QLabel(stats);
        labelBlack->setObjectName("labelBlack");
        labelBlack->setStyleSheet(QString::fromUtf8("background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                            stop:0 #8B4513, stop:0.3 #7A3F1E, stop:0.6 #8B4513, stop:1 #5C3317);\n"
"border: 2px solid #4B2E1E;\n"
"border-radius: 10px;\n"
"\n"
"\n"
""));

        verticalLayout_2->addWidget(labelBlack);

        labelWhite = new QLabel(stats);
        labelWhite->setObjectName("labelWhite");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelWhite->sizePolicy().hasHeightForWidth());
        labelWhite->setSizePolicy(sizePolicy1);
        labelWhite->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"                                  stop:0 #d2b48c, stop:1 #deb887);  /* Gradiente madera suave */\n"
"border: 2px solid #a0522d;  /* Borde marr\303\263n oscuro */\n"
"border-radius: 10px;\n"
"\n"
"\n"
""));
        labelWhite->setScaledContents(true);

        verticalLayout_2->addWidget(labelWhite);


        horizontalLayout->addWidget(stats);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addWidget(contenedor);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1236, 33));
        menuJuego = new QMenu(menubar);
        menuJuego->setObjectName("menuJuego");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuJuego->menuAction());
        menuJuego->addAction(actionNew_Game);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionMenu->setText(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        actionNew_Game->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        labelBlack->setText(QString());
        labelWhite->setText(QString());
        menuJuego->setTitle(QCoreApplication::translate("MainWindow", "Game Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLERO_H
