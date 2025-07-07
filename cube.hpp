#pragma once

#include "textures.hpp"

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>

#define ROT_STEP 80
#define CUBES_NUM 8

enum class rotation {
    NONE,
    BOTTOM_PLUS,
    RIGHT_PLUS,
    FRONT_PLUS
};

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
    Cube cubes[CUBES_NUM];

    Rubick();
    void CreateBuffers(QOpenGLShaderProgram& program);
    void Rotate();
    void setRotation(rotation tmp_rot);
    void swapPositions();
};
