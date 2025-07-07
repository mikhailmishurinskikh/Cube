#pragma once

#include "cube.hpp"
#include "camera.hpp"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

namespace Ui {
class OpenGLRender;
}

class OpenGLRender : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit OpenGLRender(QWidget *parent = nullptr);
    ~OpenGLRender();

    Camera camera;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void initializeShaders();

private:
    Ui::OpenGLRender *ui;

    QOpenGLShaderProgram shaderProgram;
    Rubick rubick;
    Textures textures;
    QTimer timer;

public slots:
    void rotateRight();
    void rotateBottom();
    void rotateFront();
};

