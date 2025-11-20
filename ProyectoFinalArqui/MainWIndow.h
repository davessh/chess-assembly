#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProyectoFinalArqui.h"

class ProyectoFinalArqui : public QMainWindow
{
    Q_OBJECT

public:
    ProyectoFinalArqui(QWidget *parent = nullptr);
    ~ProyectoFinalArqui();

private:
    Ui::ProyectoFinalArquiClass ui;
};

