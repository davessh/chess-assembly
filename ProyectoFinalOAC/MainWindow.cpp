// MainWindow.cpp
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPushButton>
#include <QPixmap>
#include <QGridLayout>
#include <QDebug>
#include <QStyle>
#include <QAction>
#include <QProcess>
#include <QApplication>
#include <QDialog>
#include "Reina.h"   
#include "Caballo.h"   
#include "Alfil.h"   
#include "Torre.h"   
#include "MenuWindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    ui->setupUi(this);

    connect(ui->actionNew_Game, &QAction::triggered, this, &MainWindow::reiniciar);
    connect(ui->actionMenu_2, &QAction::triggered, this, &MainWindow::volverAlMenu);


    this->setFixedSize(780, 700);

    this->setStyleSheet(
        "QMainWindow { background-color: #A67C52; }"
    );


    ui->contenedor->setStyleSheet(
        "QWidget#contenedor { "
        "   border-image: url(:/imagenes/fondo.jpg) 0 0 0 0 stretch stretch; "
        "}"
    );
    ui->labelBlack->setStyleSheet(
        "QLabel#labelBlack { "
        "color: black; "
        "background: transparent; "
        "border: 1px solid beige; "
        "}"
    );

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

void MainWindow::volverAlMenu()
{
    MenuWindow* menuVentana = new MenuWindow();
    menuVentana->show();

    this->close();
}

void MainWindow::inicializar()
{
    juego.iniciar();
    fichaSeleccionada = nullptr;
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

    int sizeCasilla = 80;

    gridTablero->setSpacing(0);

    for (int fila = 0; fila < 8; fila++) {
        for (int columna = 0; columna < 8; columna++) {

            QPushButton* casilla = new QPushButton();

            casilla->setFixedSize(sizeCasilla, sizeCasilla);
            casilla->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            connect(casilla, &QPushButton::clicked, this,
                [this, casilla]() { buttonAction(casilla); });

            if ((fila + columna) % 2 == 0) {
                casilla->setStyleSheet(
                    "QPushButton { "
                    "   background-image: url(:/imagenes/texturaMaderaClara.jpg); "
                    "   background-position: center; "
                    "   background-repeat: no-repeat; "
                    "   border: 3px solid transparent; "
                    "   padding: 0px; "
                    "   margin: 0px; "
                    "}"
                    "QPushButton[jaque=\"true\"] { "
                    "   background-color: rgba(255, 0, 0, 150); "
                    "   background-image: none; "
                    "   border: 3px solid #FF0000; "
                    "}"
                    "QPushButton:hover, QPushButton[hoverFijo=\"true\"] { "
                    "   border: 3px solid #FFD700; "
                    "   background-color: rgba(255, 255, 100, 50); "
                    "}"
                );
            }
            else {
                casilla->setStyleSheet(
                    "QPushButton { "
                    "   background-image: url(:/imagenes/texturaMaderaOscura.jpg); "
                    "   background-position: center; "
                    "   background-repeat: no-repeat; "
                    "   border: 3px solid transparent; "
                    "   padding: 0px; "
                    "   margin: 0px; "
                    "}"
                    "QPushButton[jaque=\"true\"] { "
                    "   background-color: rgba(255, 0, 0, 150); "
                    "   background-image: none; "
                    "   border: 3px solid #FF0000; "
                    "}"
                    "QPushButton:hover, QPushButton[hoverFijo=\"true\"] { "
                    "   border: 3px solid #FFD700; "
                    "   background-color: rgba(255, 255, 100, 50); "
                    "}"
                );
            }

            casilla->setProperty("fila", fila);
            casilla->setProperty("columna", columna);

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

    Tablero* tablero = juego.obtenerTablero();
    Casilla* casillaClickeada = tablero->getCasilla(fila, columna);

    if (!casillaClickeada) return;

    if (fichaSeleccionada == nullptr)
    {
        if (casillaClickeada->getPieza() != nullptr &&
            juego.obtenerJugadorActual() == casillaClickeada->getPieza()->getColor())
        {
            fichaSeleccionada = casillaClickeada;
            fijarHover(button);
            qDebug() << "Ficha seleccionada en" << fila << columna;
        }
    }
    else
    {
        if (fichaSeleccionada == casillaClickeada) {
            restaurarHover(button);
            fichaSeleccionada = nullptr;
            qDebug() << "Selección cancelada";
            return;
        }

        if (casillaClickeada->getPieza() != nullptr &&
            casillaClickeada->getPieza()->getColor() == juego.obtenerJugadorActual())
        {
            QPushButton* btnAnterior = obtenerCasillaGrafica(fichaSeleccionada->getFila(), fichaSeleccionada->getColumna());
            if (btnAnterior) restaurarHover(btnAnterior);

            fichaSeleccionada = casillaClickeada;
            fijarHover(button);
            qDebug() << "Cambio de ficha seleccionada";
            return;
        }

        if (juego.realizarMovimiento(fichaSeleccionada, casillaClickeada))
        {
            QPushButton* btnOrigen = obtenerCasillaGrafica(fichaSeleccionada->getFila(), fichaSeleccionada->getColumna());
            if (btnOrigen) restaurarHover(btnOrigen);

            Casilla* seleccionadaTemp = casillaClickeada;
            fichaSeleccionada = nullptr;

            if (juego.hayPromocionPendiente(seleccionadaTemp)) {
                TipoPieza tipoSeleccionado = mensajeSeleccionarFicha(seleccionadaTemp->getPieza()->getColor());
                Color color = seleccionadaTemp->getPieza()->getColor();

                delete seleccionadaTemp->getPieza();

                Pieza* nuevaPieza = nullptr;

                if (tipoSeleccionado == TipoPieza::REINA) {
                    nuevaPieza = new Reina(color, seleccionadaTemp->getFila(), seleccionadaTemp->getColumna());
                    seleccionadaTemp->setPieza(nuevaPieza);
                }
                else if (tipoSeleccionado == TipoPieza::ALFIL) {
                    nuevaPieza = new Alfil(color, seleccionadaTemp->getFila(), seleccionadaTemp->getColumna());
                    seleccionadaTemp->setPieza(nuevaPieza);
                }
                else if (tipoSeleccionado == TipoPieza::CABALLO) {
                    nuevaPieza = new Caballo(color, seleccionadaTemp->getFila(), seleccionadaTemp->getColumna());
                    seleccionadaTemp->setPieza(nuevaPieza);
                }
                else if (tipoSeleccionado == TipoPieza::TORRE) {
                    nuevaPieza = new Torre(color, seleccionadaTemp->getFila(), seleccionadaTemp->getColumna());
                    seleccionadaTemp->setPieza(nuevaPieza);
                }

                if (nuevaPieza) {
                    Color jugadorActual = juego.obtenerJugadorActual();

                    if (juego.verificarJacke()) {
                        if (juego.esJaqueMate(jugadorActual)) {
                            juego.setEstado(EstadoJuego::JAQUE_MATE);
                        }
                        else {
                            juego.setEstado(EstadoJuego::JAQUE);
                        }
                    }
                }
            }

            actualizar();

            if (juego.obtenerEstadoJuego() == EstadoJuego::JAQUE_MATE)
            {
                Color ganador;
                if (juego.obtenerJugadorActual() == Color::BLANCO)
                {
                    ganador = Color::NEGRO;
                }
                else
                {
                    ganador = Color::BLANCO;
                }
                mensajeVictoria(ganador);
            }
            else if (juego.obtenerEstadoJuego() == EstadoJuego::TABLAS) {
                mensajeEmpate();
            }

            qDebug() << "Movimiento exitoso";
        }
        else
        {

            qDebug() << "Movimiento inválido";

        }
    }
}

QPushButton* MainWindow::obtenerCasillaGrafica(int fila, int columna)
{
    QGridLayout* gridTablero = ui->tablero;
    QLayoutItem* item = gridTablero->itemAtPosition(fila, columna);


    QPushButton* button = item ? qobject_cast<QPushButton*>(item->widget()) : nullptr;

    return button;
}

void MainWindow::restaurarHover(QPushButton* button) {
    button->setProperty("hoverFijo", false);
    button->style()->unpolish(button);
    button->style()->polish(button);
}


void MainWindow::fijarHover(QPushButton* button)
{
    button->setProperty("hoverFijo", true);

    button->style()->unpolish(button);
    button->style()->polish(button);
}

void MainWindow::marcarJacke(QPushButton* button) {
    if (!button) return;
    button->setProperty("jaque", true);
    button->style()->unpolish(button);
    button->style()->polish(button);
}

void MainWindow::desmarcarJacke(QPushButton* button) {
    if (!button) return;
    button->setProperty("jaque", false);
    button->style()->unpolish(button);
    button->style()->polish(button);
}



void MainWindow::actualizar()
{
    Casilla* casillaRey = nullptr;

    mostrarTurnoActual(juego.obtenerJugadorActual());

    Tablero* tablero = juego.obtenerTablero();

    QGridLayout* gridTablero = ui->tablero;
    if (!gridTablero) { return; }



    for (int f = 0; f < 8; ++f) {
        for (int c = 0; c < 8; ++c) {
            QLayoutItem* item = gridTablero->itemAtPosition(f, c);
            QPushButton* btn = item ? qobject_cast<QPushButton*>(item->widget()) : nullptr;
            if (btn) {
                desmarcarJacke(btn);
            }
        }
    }

    if (juego.obtenerEstadoJuego() == EstadoJuego::JAQUE)
    {
        casillaRey = tablero->buscarRey(juego.obtenerJugadorActual());
    }

    for (int fila = 0; fila < 8; ++fila) {
        for (int col = 0; col < 8; ++col) {

            Casilla* casilla = tablero->getCasilla(fila, col);
            Pieza* pieza = casilla ? casilla->getPieza() : nullptr;

            QLayoutItem* item = gridTablero->itemAtPosition(fila, col);
            QPushButton* boton = item ? qobject_cast<QPushButton*>(item->widget()) : nullptr;
            if (!boton) continue;

            if (!pieza) {
                boton->setIcon(QIcon());
                boton->setIconSize(QSize());
                continue;
            }

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
                if (casillaRey != nullptr &&
                    casillaRey->getFila() == fila &&
                    casillaRey->getColumna() == col)
                {
                    marcarJacke(boton);
                }

                rutaIcono = (pieza->getColor() == Color::BLANCO)
                    ? ":/imagenes/Piezas/ReyBlanco.png"
                    : ":/imagenes/Piezas/ReyNegro.png";
                break;
            }

            boton->setIcon(QIcon(rutaIcono));
            boton->setIconSize(boton->size());
        }
    }

}

void MainWindow::reiniciar()
{
    MainWindow* nuevaVentana = new MainWindow();
    nuevaVentana->show();

    this->close();
}


TipoPieza MainWindow::mensajeSeleccionarFicha(Color colorPieza)
{
    QDialog dialog(this);
    dialog.setWindowTitle("Promoción de Peón");
    dialog.setModal(true);


    dialog.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);
    dialog.setStyleSheet("QDialog { background-color: #A67C52; }");

    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);

    QLabel* titulo = new QLabel("Selecciona la pieza para promoción:");
    titulo->setStyleSheet("color: white; font-size: 14pt; font-weight: bold;");
    titulo->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titulo);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addLayout(gridLayout);

    TipoPieza piezaSeleccionada = TipoPieza::REINA;

    struct PiezaInfo {
        TipoPieza tipo;
        QString nombre;
        QString rutaImagen;
    };

    QString colorStr = (colorPieza == Color::BLANCO) ? "Blanco" : "Negro";

    QVector<PiezaInfo> piezas = {
        {TipoPieza::REINA, "Reina", ":/imagenes/Piezas/Reina" + colorStr + ".png"},
        {TipoPieza::TORRE, "Torre", ":/imagenes/Piezas/Torre" + colorStr + ".png"},
        {TipoPieza::ALFIL, "Alfil", ":/imagenes/Piezas/Alfil" + colorStr + ".png"},
        {TipoPieza::CABALLO, "Caballo", ":/imagenes/Piezas/Caballo" + colorStr + ".png"}
    };

    for (int i = 0; i < piezas.size(); ++i) {
        int fila = i / 2;
        int col = i % 2;

        QWidget* cellWidget = new QWidget();
        cellWidget->setStyleSheet(
            "QWidget { "
            "   background-color: #8B6F47; "
            "   border: 2px solid #654321; "
            "   border-radius: 8px; "
            "}"
        );

        QVBoxLayout* cellLayout = new QVBoxLayout(cellWidget);
        cellLayout->setContentsMargins(10, 10, 10, 10);
        cellLayout->setSpacing(8);

        QLabel* imageLabel = new QLabel();
        imageLabel->setFixedSize(80, 80);
        imageLabel->setScaledContents(true);
        imageLabel->setAlignment(Qt::AlignCenter);

        QPixmap pixmap(piezas[i].rutaImagen);
        if (!pixmap.isNull()) {
            imageLabel->setPixmap(pixmap);
        }
        else {
            imageLabel->setText(piezas[i].nombre);
            imageLabel->setStyleSheet("color: white;");
        }

        QPushButton* button = new QPushButton(piezas[i].nombre);
        button->setStyleSheet(
            "QPushButton { "
            "   background-color: #654321; "
            "   color: white; "
            "   border: 2px solid #A67C52; "
            "   border-radius: 5px; "
            "   padding: 8px; "
            "   font-weight: bold; "
            "}"
            "QPushButton:hover { "
            "   background-color: #7A5230; "
            "   border: 2px solid #FFD700; "
            "}"
        );

        connect(button, &QPushButton::clicked, [&dialog, &piezaSeleccionada, tipo = piezas[i].tipo]() {
            piezaSeleccionada = tipo;
            dialog.accept();
            });

        cellLayout->addWidget(imageLabel);
        cellLayout->addWidget(button);

        gridLayout->addWidget(cellWidget, fila, col);
    }

    dialog.setFixedSize(450, 280);

    dialog.exec();

    return piezaSeleccionada;
}



void MainWindow::mensajeVictoria(Color ganador)
{
    QDialog dialog(this);
    dialog.setWindowTitle("Jaque Mate!");
    dialog.setModal(true);
    dialog.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);

    QString colorFondo = (ganador == Color::BLANCO) ? "#F5F5DC" : "#2C2C2C";
    QString colorTexto = (ganador == Color::BLANCO) ? "#000000" : "#FFFFFF";
    QString colorBoton = (ganador == Color::BLANCO) ? "#FFD700" : "#C0C0C0";

    dialog.setStyleSheet(QString("QDialog { background-color: %1; }").arg(colorFondo));

    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    QLabel* titulo = new QLabel("JAQUE MATE!");
    titulo->setStyleSheet(QString(
        "color: %1; "
        "font-size: 28pt; "
        "font-weight: bold; "
        "font-family: 'Arial Black';"
    ).arg(colorTexto));
    titulo->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titulo);

    QLabel* imagenRey = new QLabel();
    imagenRey->setFixedSize(120, 120);
    imagenRey->setScaledContents(true);
    imagenRey->setAlignment(Qt::AlignCenter);

    QString rutaRey = (ganador == Color::BLANCO)
        ? ":/imagenes/Piezas/ReyBlanco.png"
        : ":/imagenes/Piezas/ReyNegro.png";

    QPixmap pixmapRey(rutaRey);
    if (!pixmapRey.isNull()) {
        imagenRey->setPixmap(pixmapRey);
    }
    mainLayout->addWidget(imagenRey, 0, Qt::AlignCenter);

    QString textoGanador = (ganador == Color::BLANCO) ? "BLANCAS" : "NEGRAS";
    QLabel* mensaje = new QLabel(QString("Las %1 han ganado!").arg(textoGanador));
    mensaje->setStyleSheet(QString(
        "color: %1; "
        "font-size: 18pt; "
        "font-weight: bold;"
    ).arg(colorTexto));
    mensaje->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(mensaje);

    QHBoxLayout* botonesLayout = new QHBoxLayout();
    botonesLayout->setSpacing(15);

    QPushButton* btnNuevaPartida = new QPushButton("Nueva Partida");
    QPushButton* btnSalir = new QPushButton("Salir");

    QString estiloBoton = QString(
        "QPushButton { "
        "   background-color: %1; "
        "   color: %2; "
        "   border: 3px solid %2; "
        "   border-radius: 8px; "
        "   padding: 12px 24px; "
        "   font-size: 14pt; "
        "   font-weight: bold; "
        "}"
        "QPushButton:hover { "
        "   background-color: %2; "
        "   color: %1; "
        "   border: 3px solid %1; "
        "}"
    ).arg(colorBoton).arg(colorTexto);

    btnNuevaPartida->setStyleSheet(estiloBoton);
    btnSalir->setStyleSheet(estiloBoton);

    connect(btnNuevaPartida, &QPushButton::clicked, [this, &dialog]() {
        dialog.accept();
        reiniciar();
        });

    connect(btnSalir, &QPushButton::clicked, [&dialog]() {
        dialog.accept();
        QApplication::quit();
        });

    botonesLayout->addWidget(btnNuevaPartida);
    botonesLayout->addWidget(btnSalir);
    mainLayout->addLayout(botonesLayout);

    dialog.setFixedSize(600, 400);
    dialog.exec();
}

void MainWindow::mostrarTurnoActual(Color turno)
{
    QString fuente = "Garamond";
    QString size = "30px";

    QString cafeOscuro = "#5A3E2B";
    QString cafeClaro = "#D7B892";

    QString bordeColor = (turno == Color::BLANCO) ? cafeOscuro : cafeClaro;

    QString estiloBlancoActivo = QString(
        "QLabel { "
        "  background-color: %3; "
        "  color: black; "
        "  border: 4px solid %4; "
        "  font-family: '%1'; "
        "  font-size: %2; "
        "  font-weight: bold; "
        "  qproperty-alignment: AlignCenter; "
        "}"
    ).arg(fuente).arg(size).arg(cafeClaro).arg(bordeColor);

    QString estiloNegroActivo = QString(
        "QLabel { "
        "  background-color: %3; "
        "  color: white; "
        "  border: 4px solid %4; "
        "  font-family: '%1'; "
        "  font-size: %2; "
        "  font-weight: bold; "
        "  qproperty-alignment: AlignCenter; "
        "}"
    ).arg(fuente).arg(size).arg(cafeOscuro).arg(bordeColor);

    QString estiloInactivo = QString(
        "QLabel { "
        "  background-color: transparent; "
        "  border: 4px solid %1; "
        "}"
    ).arg(bordeColor);

    QString textoVerticalBlanco = "B\nL\nA\nN\nC\nO";
    QString textoVerticalNegro = "N\nE\nG\nR\nO";

    if (turno == Color::BLANCO)
    {
        ui->labelWhite->setText(textoVerticalBlanco);
        ui->labelWhite->setStyleSheet(estiloBlancoActivo);

        ui->labelBlack->setText("");
        ui->labelBlack->setStyleSheet(estiloInactivo);
    }
    else
    {
        ui->labelBlack->setText(textoVerticalNegro);
        ui->labelBlack->setStyleSheet(estiloNegroActivo);

        ui->labelWhite->setText("");
        ui->labelWhite->setStyleSheet(estiloInactivo);
    }
}

void MainWindow::mensajeEmpate()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Empate!");
    dialog.setModal(true);
    dialog.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);

    QString colorFondo = "#8B7355";
    QString colorTexto = "#FFFFFF";
    QString colorBoton = "#D4AF37";

    dialog.setStyleSheet(QString("QDialog { background-color: %1; }").arg(colorFondo));

    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    QLabel* titulo = new QLabel("EMPATE!");
    titulo->setStyleSheet(QString(
        "color: %1; "
        "font-size: 28pt; "
        "font-weight: bold; "
        "font-family: 'Arial Black';"
    ).arg(colorTexto));
    titulo->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titulo);

    QLabel* mensaje = new QLabel("La partida ha terminado en tablas");
    mensaje->setStyleSheet(QString(
        "color: %1; "
        "font-size: 18pt; "
        "font-weight: bold;"
    ).arg(colorTexto));
    mensaje->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(mensaje);

    mainLayout->addSpacing(120);

    QHBoxLayout* botonesLayout = new QHBoxLayout();
    botonesLayout->setSpacing(15);

    QPushButton* btnNuevaPartida = new QPushButton("Nueva Partida");
    QPushButton* btnSalir = new QPushButton("Salir");

    QString estiloBoton = QString(
        "QPushButton { "
        "   background-color: %1; "
        "   color: %2; "
        "   border: 3px solid %2; "
        "   border-radius: 8px; "
        "   padding: 12px 24px; "
        "   font-size: 14pt; "
        "   font-weight: bold; "
        "}"
        "QPushButton:hover { "
        "   background-color: %2; "
        "   color: %1; "
        "   border: 3px solid %1; "
        "}"
    ).arg(colorBoton).arg(colorTexto);

    btnNuevaPartida->setStyleSheet(estiloBoton);
    btnSalir->setStyleSheet(estiloBoton);

    connect(btnNuevaPartida, &QPushButton::clicked, [this, &dialog]() {
        dialog.accept();
        reiniciar();
        });

    connect(btnSalir, &QPushButton::clicked, [&dialog]() {
        dialog.accept();
        QApplication::quit();
        });

    botonesLayout->addWidget(btnNuevaPartida);
    botonesLayout->addWidget(btnSalir);
    mainLayout->addLayout(botonesLayout);

    dialog.setFixedSize(600, 400);
    dialog.exec();
}

void MainWindow::graciasOmar()
{

}