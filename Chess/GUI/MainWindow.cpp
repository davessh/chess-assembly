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

    juego.iniciar();
    fichaSeleccionada = nullptr;


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
    actualizar();
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
        connect(casilla, &QPushButton::clicked, this,
                            [this, casilla]() { buttonAction(casilla); });

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

void MainWindow::buttonAction(QPushButton* button)
{
    if (!button) return;

    int fila = button->property("fila").toInt();
    int columna = button->property("columna").toInt();

    qDebug() << "Click en casilla fila:" << fila << "columna:" << columna;


}

void MainWindow::actualizar()
{
    // Tablero lógico (modelo)
    const Tablero& tablero = juego.obtenerTablero();

    // Layout del tablero gráfico
    QGridLayout* gridTablero = ui->tablero;
    if (!gridTablero) return;

    for (int fila = 0; fila < 8; ++fila) {
        for (int col = 0; col < 8; ++col) {

            // 1) Casilla lógica
            Casilla* casilla = tablero.getCasilla(fila, col);
            Pieza* pieza = casilla ? casilla->getPieza() : nullptr;

            // 2) Botón en el grid
            QLayoutItem* item = gridTablero->itemAtPosition(fila, col);
            QPushButton* boton = item ? qobject_cast<QPushButton*>(item->widget()) : nullptr;
            if (!boton) continue;

            // 3) Decidir qué icono poner
            if (!pieza) {
                boton->setIcon(QIcon());
                boton->setIconSize(QSize()); // opcional
                continue;
            }

            // 4) Elegir la ruta de la imagen según tipo/color
            QString rutaIcono;

            switch (pieza->getTipo()) {
                case TipoPieza::PEON:
                    rutaIcono = (pieza->getColor() == Color::BLANCO)
                        ? ":/imagenes/Piezas/PeonBlanco.png"
                        : ":/imagenes/Piezas/PeonNegro.png";
                    break;

                case TipoPieza::TORRE:
                    rutaIcono = (pieza->getColor() == Color::BLANCO)
                        ? ":/imagenes/Piezas/TorreBlanco.png"
                        : ":/imagenes/Piezas/TorreNegro.png";
                    break;

                // Completa tú:
                case TipoPieza::CABALLO:
                rutaIcono = (pieza->getColor() == Color::BLANCO)
                        ? ":/imagenes/Piezas/CaballoBlanco.png"
                        : ":/imagenes/Piezas/CaballoNegro.png";
                break;
                case TipoPieza::ALFIL:
                rutaIcono = (pieza->getColor() == Color::BLANCO)
                        ? ":/imagenes/Piezas/AlfilBlanco.png"
                        : ":/imagenes/Piezas/AlfilNegro.png";
                break;
                case TipoPieza::REINA:
                rutaIcono = (pieza->getColor() == Color::BLANCO)
                        ? ":/imagenes/Piezas/ReinaBlanco.png"
                        : ":/imagenes/Piezas/ReinaNegro.png";
                break;
                case TipoPieza::REY:
                rutaIcono = (pieza->getColor() == Color::BLANCO)
                        ? ":/imagenes/Piezas/ReyBlanco.png"
                        : ":/imagenes/Piezas/ReyNegro.png";
                break;
                    // ...
                    break;
            }

            // 5) Aplicar icono al botón
            boton->setIcon(QIcon(rutaIcono));
            boton->setIconSize(boton->size());
        }
    }
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