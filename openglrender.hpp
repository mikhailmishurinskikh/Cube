#pragma once

#include "cube.hpp"
#include "camera.hpp"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class OpenGLRender : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit OpenGLRender(QWidget *parent = nullptr);

    Camera camera;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void initializeShaders();

private:
    QOpenGLShaderProgram shaderProgram;
    Rubick rubick;
    Textures textures;
    QTimer timer;

public slots:
    void rotate(rotation rot);
    void solve();
};

