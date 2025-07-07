#include "mainwindow.hpp"
#include "openglrender.hpp"
#include "ui_mainwindow.h"

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionRight, &QAction::triggered,
            ui->Render, &OpenGLRender::rotateRight);
    connect(ui->actionBottom, &QAction::triggered,
            ui->Render, &OpenGLRender::rotateBottom);
    connect(ui->actionFront, &QAction::triggered,
            ui->Render, &OpenGLRender::rotateFront);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
    }
    else if (event->key() == Qt::Key_Right) {
        ui->Render->camera.azimuthalSign = 1;
    }
    else if (event->key() == Qt::Key_Left) {
        ui->Render->camera.azimuthalSign = -1;
    }
    else if (event->key() == Qt::Key_Up) {
        ui->Render->camera.polarSign = 1;
    }
    else if (event->key() == Qt::Key_Down) {
        ui->Render->camera.polarSign = -1;
    }

    QWidget::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Right) {
        ui->Render->camera.azimuthalSign = 0;
    }
    else if (event->key() == Qt::Key_Left) {
        ui->Render->camera.azimuthalSign = 0;
    }
    else if (event->key() == Qt::Key_Up) {
        ui->Render->camera.polarSign = 0;
    }
    else if (event->key() == Qt::Key_Down) {
        ui->Render->camera.polarSign = 0;
    }

    QWidget::keyReleaseEvent(event);
}

