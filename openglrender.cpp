#include "openglrender.hpp"
#include "ui_openglrender.h"

OpenGLRender::OpenGLRender(QWidget* parent) :
    QOpenGLWidget(parent),
    ui(new Ui::OpenGLRender),
    timer()
{
    ui->setupUi(this);
    connect(&timer, &QTimer::timeout, this, [this]() {
        if (rubick.rot != rotation::NONE || camera.azimuthalSign != 0 || camera.polarSign != 0) {
            update();  // Запускает paintGL()
        }
    });
    timer.start(16);  // 60 FPS
}

OpenGLRender::~OpenGLRender()
{
    delete ui;
}

void OpenGLRender::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST); // отслеживание оси z (глубины)
    initializeShaders();
    rubick.CreateBuffers(shaderProgram);
    textures.loadAll();
}

void OpenGLRender::paintGL()
{
    if (rubick.rot != rotation::NONE) rubick.Rotate();
    if (camera.azimuthalSign != 0) camera.azimuthalRotate();
    if (camera.polarSign != 0) camera.polarRotate();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    rubick.VAO.bind();
    shaderProgram.bind();

    for (int i{}; i < CUBES_NUM; i++) {
        QMatrix4x4 matrix = camera.vpMatrix * rubick.cubes[i].modelMatrix;
        shaderProgram.setUniformValue("gWVP", matrix);
        for (int n_texture{}; n_texture < 3; n_texture++) {

            textures.bind(rubick.cubes[i].m_colors[n_texture]);
            glDrawArrays(GL_TRIANGLES, 6 * n_texture, 6);
            textures.release(rubick.cubes[i].m_colors[n_texture]);
        }

        textures.bind(colors::PLASTIC);
        glDrawArrays(GL_TRIANGLES, 18, 18);
        textures.release(colors::PLASTIC);
    }

    shaderProgram.release();
    rubick.VAO.release();
}

void OpenGLRender::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    camera.updateSize(w, h);
}

void OpenGLRender::initializeShaders()
{
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/FS.frag")) {
        throw std::runtime_error("Fragment shader loading failed");
    };
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/VS.vert")) {
        throw std::runtime_error("Vertex shader loading failed");
    };
    if (!shaderProgram.link()) {
        throw std::runtime_error("Shaders linking failed");
    };
}

void OpenGLRender::rotateRight()
{
    rubick.setRotation(rotation::RIGHT_PLUS);
}

void OpenGLRender::rotateBottom()
{
    rubick.setRotation(rotation::BOTTOM_PLUS);
}

void OpenGLRender::rotateFront()
{
    rubick.setRotation(rotation::FRONT_PLUS);
}
