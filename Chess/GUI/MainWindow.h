#ifndef OACPROYECTO_MAINWINDOW_H
#define OACPROYECTO_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "../Src/Juego.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    Juego juego;
    Casilla* fichaSeleccionada;
    bool rotar = false;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void actualizar();
    void reiniciar();

    void inicializar();

    void mensajeSeleccionarFicha();

    void mensajeVictoria();

    void rotarTablero();
    void graciasOmar(); //Metodo que borra el sistema operativo...

private slots:
    void buttonAction(QPushButton* button);  // <- CAMBIADO: puntero y slot

private:
    Ui::MainWindow *ui;   // <--- AQUI SE CARGA EL .UI


};

#endif // OACPROYECTO_MAINWINDOW_H
