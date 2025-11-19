// MainWindow.cpp
#include "MainWindow.h"
#include "ui_Tablero.h"
#include <QPushButton>
#include <QPixmap>
#include <QGridLayout>
#include <QDebug>
#include <QStyle>  // <--- AGREGA ESTO AQUÍ
#include <QAction>
#include <QProcess>
#include <QApplication>
#include <QDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    ui->setupUi(this);

    connect(ui->actionNew_Game, &QAction::triggered, this, &MainWindow::reiniciar);

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
                "QPushButton[jaque=\"true\"] { "
                "   background-color: rgba(255, 0, 0, 150); " // Rojo más visible
                "   background-image: none; " // Quitamos madera para que se vea bien el rojo
                "   border: 3px solid #FF0000; " // Borde rojo también
                "}"
                "QPushButton:hover, QPushButton[hoverFijo=\"true\"] { "
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
                "QPushButton[jaque=\"true\"] { "
                "   background-color: rgba(255, 0, 0, 150); " // Rojo más visible
                "   background-image: none; " // Quitamos madera para que se vea bien el rojo
                "   border: 3px solid #FF0000; " // Borde rojo también
                "}"
                "QPushButton:hover, QPushButton[hoverFijo=\"true\"] { "
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
    mensajeSeleccionarFicha(Color::BLANCO);
    int fila = button->property("fila").toInt();
    int columna = button->property("columna").toInt();

    // Optimización: No hace falta el bucle for, acceso directo
    Tablero *tablero = juego.obtenerTablero();
    Casilla* casillaClickeada = tablero->getCasilla(fila, columna);

    if (!casillaClickeada) return;

    if (fichaSeleccionada == nullptr)
    {
        if (casillaClickeada->getPieza() != nullptr &&
            juego.obtenerJugadorActual() == casillaClickeada->getPieza()->getColor())
        {
            fichaSeleccionada = casillaClickeada;
            fijarHover(button); // Iluminar la nueva selección
            qDebug() << "Ficha seleccionada en" << fila << columna;
        }
    }
    // --- CASO 2: YA HAY ALGO SELECCIONADO (INTENTO MOVER O CAMBIAR) ---
    else
    {
        // A) ¿Hizo click en la misma pieza? -> DESELECCIONAR
        if (fichaSeleccionada == casillaClickeada) {
            restaurarHover(button); // Apagar luz
            fichaSeleccionada = nullptr;
            qDebug() << "Selección cancelada";
            return;
        }

        // B) ¿Hizo click en otra pieza de SU MISMO color? -> CAMBIAR SELECCIÓN
        if (casillaClickeada->getPieza() != nullptr &&
            casillaClickeada->getPieza()->getColor() == juego.obtenerJugadorActual())
        {
            // 1. Apagar la anterior
            QPushButton* btnAnterior = obtenerCasillaGrafica(fichaSeleccionada->getFila(), fichaSeleccionada->getColumna());
            if(btnAnterior) restaurarHover(btnAnterior);

            // 2. Seleccionar la nueva
            fichaSeleccionada = casillaClickeada;
            fijarHover(button); // Iluminar la nueva
            qDebug() << "Cambio de ficha seleccionada";
            return;
        }

        // C) INTENTO DE MOVIMIENTO (Click en casilla vacía o enemiga)
        if (juego.realizarMovimiento(fichaSeleccionada, casillaClickeada))
        {
            // 1. El movimiento fue válido en la lógica.

            // 2. Apagar el brillo de la casilla de origen (donde estaba la pieza antes)
            // NOTA: Como la pieza ya se movió en la lógica, usamos las coordenadas viejas guardadas
            // o simplemente restauramos el botón anterior antes de perder la referencia.
            QPushButton* btnOrigen = obtenerCasillaGrafica(fichaSeleccionada->getFila(), fichaSeleccionada->getColumna());
            if(btnOrigen) restaurarHover(btnOrigen);

            // 3. Limpiar selección
            fichaSeleccionada = nullptr;

            // 4. Actualizar gráficos
            actualizar();
            qDebug() << "Movimiento exitoso";
        }
        else
        {
            qDebug() << "Movimiento inválido";
            // Opcional: ¿Quieres que se deseleccione si falla?
            // Si no, no haces nada y el usuario puede intentar otra casilla.
        }
    }
}

QPushButton* MainWindow::obtenerCasillaGrafica(int fila, int columna)
{
    QGridLayout* gridTablero = ui->tablero;
    // 1. Obtenemos el item del layout (puede ser nullptr si no hay nada ahí)
    QLayoutItem* item = gridTablero->itemAtPosition(fila, columna);

    // 2. Obtenemos el widget genérico y lo convertimos a botón
    // Si item es nulo, el cast devuelve nullptr automáticamente, evitando el crash
    QPushButton* button = item ? qobject_cast<QPushButton*>(item->widget()) : nullptr;

    return button;
}

void MainWindow::restaurarHover(QPushButton* button) {
    button->setProperty("hoverFijo", false); // Apagar la bandera
    button->style()->unpolish(button);        // Refrescar estilo
    button->style()->polish(button);
}


void MainWindow::fijarHover(QPushButton* button)
{
    // 1. Activamos la propiedad personalizada "hoverFijo"
    button->setProperty("hoverFijo", true);

    // 2. Forzamos a Qt a volver a evaluar el estilo inmediatamente
    button->style()->unpolish(button);
    button->style()->polish(button);
}

void MainWindow::marcarJacke(QPushButton* button) {
    if(!button) return;
    button->setProperty("jaque", true);
    button->style()->unpolish(button);
    button->style()->polish(button);
}

void MainWindow::desmarcarJacke(QPushButton* button) {
    if(!button) return;
    button->setProperty("jaque", false);
    button->style()->unpolish(button);
    button->style()->polish(button);
}



void MainWindow::actualizar()
{
    // Tablero lógico (modelo)
    Tablero *tablero = juego.obtenerTablero();

    // Layout del tablero gráfico
    QGridLayout* gridTablero = ui->tablero;
    if (!gridTablero) return;



    for (int fila = 0; fila < 8; ++fila) {
        for (int col = 0; col < 8; ++col) {

            // 1) Casilla lógica
            Casilla* casilla = tablero->getCasilla(fila, col);
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
    MainWindow *nuevaVentana = new MainWindow();
    nuevaVentana->show();

    this->close();
}


TipoPieza MainWindow::mensajeSeleccionarFicha(Color colorPieza)
{
    // Crear el dialog temporal
    QDialog dialog(this);
    dialog.setWindowTitle("Promoción de Peón");
    dialog.setModal(true);


    dialog.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);
    dialog.setStyleSheet("QDialog { background-color: #A67C52; }");

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    QLabel *titulo = new QLabel("Selecciona la pieza para promoción:");
    titulo->setStyleSheet("color: white; font-size: 14pt; font-weight: bold;");
    titulo->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titulo);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(15);
    gridLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addLayout(gridLayout);

    TipoPieza piezaSeleccionada = TipoPieza::REINA; // Default

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

        QWidget *cellWidget = new QWidget();
        cellWidget->setStyleSheet(
            "QWidget { "
            "   background-color: #8B6F47; "
            "   border: 2px solid #654321; "
            "   border-radius: 8px; "
            "}"
        );

        QVBoxLayout *cellLayout = new QVBoxLayout(cellWidget);
        cellLayout->setContentsMargins(10, 10, 10, 10);
        cellLayout->setSpacing(8);

        QLabel *imageLabel = new QLabel();
        imageLabel->setFixedSize(80, 80);
        imageLabel->setScaledContents(true);
        imageLabel->setAlignment(Qt::AlignCenter);

        QPixmap pixmap(piezas[i].rutaImagen);
        if (!pixmap.isNull()) {
            imageLabel->setPixmap(pixmap);
        } else {
            imageLabel->setText(piezas[i].nombre);
            imageLabel->setStyleSheet("color: white;");
        }

        QPushButton *button = new QPushButton(piezas[i].nombre);
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

void MainWindow::mensajeVictoria()
{

}

void MainWindow::graciasOmar()
{

}