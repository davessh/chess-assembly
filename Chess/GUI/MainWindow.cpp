// MainWindow.cpp
#include "MainWindow.h"
#include "ui_Tablero.h"
#include <QPushButton>
#include <QPixmap>
#include <QGridLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(780,700);

    this->setStyleSheet(
        "QMainWindow { background-color: #A67C52; }"
    );


    ui->contenedor->setStyleSheet(
        "QWidget#contenedor { "
        "   border-image: url(:/imagenes/fondo.jpg) 0 0 0 0 stretch stretch; "
        "}"
    );
    // Para labelBlack
    ui->labelBlack->setStyleSheet(
        "QLabel#labelBlack { "
        "color: black; "
        "background: transparent; "
        "border: 1px solid beige; "
        "}"
    );

    // Para labelWhite
    ui->labelWhite->setStyleSheet(
        "QLabel#labelWhite { "
        "color: white; "
        "background: transparent; "
        "border: 1px solid beige; "
        "}"
    );




    inicializar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inicializar()
{
    QGridLayout* gridTablero = ui->tablero;

    if (!gridTablero) {
        qDebug() << "Error: No se encontró el gridLayout 'tablero'";
        return;
    }

    QLayoutItem* item;
    while ((item = gridTablero->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // Tamaño fijo para cada casilla
    int tamañoCasilla = 80;

    gridTablero->setSpacing(0);

for (int fila = 0; fila < 8; fila++) {
    for (int columna = 0; columna < 8; columna++) {

        QPushButton* casilla = new QPushButton();

        casilla->setFixedSize(tamañoCasilla, tamañoCasilla);
        casilla->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        // Alternar imágenes según la posición
        if ((fila + columna) % 2 == 0) {
            // Casilla clara
            casilla->setStyleSheet(
                "QPushButton { "
                "   background-image: url(:/imagenes/texturaMaderaClara.jpg); "
                "   background-position: center; "
                "   background-repeat: no-repeat; "
                "   border: 3px solid transparent; "
                "   padding: 0px; "
                "   margin: 0px; "
                "}"
                "QPushButton:hover { "
                "   border: 3px solid #FFD700; "
                "   background-color: rgba(255, 255, 100, 50); "
                "}"
            );
        } else {
            // Casilla oscura
            casilla->setStyleSheet(
                "QPushButton { "
                "   background-image: url(:/imagenes/texturaMaderaOscura.jpg); "
                "   background-position: center; "
                "   background-repeat: no-repeat; "
                "   border: 3px solid transparent; "
                "   padding: 0px; "
                "   margin: 0px; "
                "}"
                "QPushButton:hover { "
                "   border: 3px solid #FFD700; "
                "   background-color: rgba(255, 255, 100, 50); "
                "}"
            );
        }

        // Guardar posición en el botón (para uso futuro)
        casilla->setProperty("fila", fila);
        casilla->setProperty("columna", columna);

        // Agregar la casilla al gridLayout
        gridTablero->addWidget(casilla, fila, columna);
    }
}

    qDebug() << "Tablero 8x8 inicializado correctamente";


}

void MainWindow::actualizar()
{
    // Por implementar después
}

void MainWindow::reiniciar()
{
    // Simplemente reinicializar (que ya limpia el contenido)
    inicializar();
}

void MainWindow::mensajeSeleccionarFicha()
{
    // Por implementar después
}

void MainWindow::mensajeVictoria()
{
    // Por implementar después
}

void MainWindow::rotarTablero()
{
    // Por implementar después
}