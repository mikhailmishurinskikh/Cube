#pragma once

#include "constants.hpp"
#include "textures.hpp"
#include "processor.hpp"

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QQueue>

class Cube {
    QMatrix4x4 rotPosition;

public:

    colors m_colors[3];
    QMatrix4x4 modelMatrix;

    Cube(int rotValue, QVector3D rotDir, colors col_1, colors col_2, colors col_3);
    void Rotate(QVector3D rotDirection, int rotSign);
};

class Rubick {
    QVector3D rotDirection;
    int rotSign;
    int step;
    int positions[CUBES_NUM];
    int rotPositions[CUBES_NUM/2];

public:
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject VAO;
    rotation rot;
    QQueue<rotation> rotationsQueue;
    Cube cubes[CUBES_NUM];
    processor::RubickState state;

    Rubick();
    void CreateBuffers(QOpenGLShaderProgram& program);
    void Rotate();
    void addRotation(rotation tmp_rot);
    void setRotation();
    void swapPositions();
    void solve();
};
