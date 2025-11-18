#ifndef OACPROYECTO_MAINWINDOW_H
#define OACPROYECTO_MAINWINDOW_H

#include <QMainWindow>

#include "../Src/Juego.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void actualizar();
    void reiniciar();

    void inicializar();

    void mensajeSeleccionarFicha();

    void mensajeVictoria();

    void rotarTablero();


private:
    Ui::MainWindow *ui;   // <--- AQUI SE CARGA EL .UI
    Juego juego;
};

#endif // OACPROYECTO_MAINWINDOW_H
