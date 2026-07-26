#include "mainwindow.hpp"
#include "openglrender.hpp"
#include "ui/ui_mainwindow.h"
#include "constants.hpp"

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionRight, &QAction::triggered, this,
        [this]() {
            ui->Render->rotate(rotation::Right);
        });
    connect(ui->actionBottom, &QAction::triggered, this,
        [this]() {
            ui->Render->rotate(rotation::Bottom);
        });
    connect(ui->actionFront, &QAction::triggered, this,
        [this]() {
            ui->Render->rotate(rotation::Front);
        });

    connect(ui->actionSolve, &QAction::triggered, this,
        [this]() {
            ui->Render->solve();
        });
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

