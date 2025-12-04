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

    QPushButton* obtenerCasillaGrafica(int fila, int columna);

    void fijarHover(QPushButton* button);
    void restaurarHover(QPushButton* button);

    void inicializar();

    TipoPieza mensajeSeleccionarFicha(Color colorPieza);


    void mensajeVictoria(Color ganador);

    void mensajeEmpate();


    void mostrarTurnoActual(Color turno);

    void graciasOmar(); //Metodo que borra el sistema operativo...

    void marcarJacke(QPushButton* button);

    void desmarcarJacke(QPushButton* button);

private slots:
    void buttonAction(QPushButton* button);

private:
    Ui::MainWindow *ui;


};

#endif // OACPROYECTO_MAINWINDOW_H
