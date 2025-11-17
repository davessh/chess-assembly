#ifndef TABLEROWIDGET_H
#define TABLEROWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class TableroInterfaz : public QWidget {
    Q_OBJECT

public:
    explicit TableroWidget(QWidget *parent = nullptr);

private:
    QGridLayout *layoutTablero;
    QPushButton *casillas[8][8];

    void crearTablero();
};

#endif // TABLEROWIDGET_H
BLEROINTERFAZ_H