#include "cube.hpp"

constexpr float cubeVertices[] = {
    // Нижняя
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    // Правая
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    // Передняя
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    // Задняя
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    // Верхняя
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

    // Левая
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
};

Cube::Cube(int rotValue, QVector3D rotDir, colors col_1, colors col_2, colors col_3) :
    m_colors { col_1, col_2, col_3 }
{
    QMatrix4x4 matrix;
    matrix.rotate(rotValue, rotDir);
    rotPosition = matrix;
    modelMatrix = matrix;
    modelMatrix.translate(0.51f, -0.51f, 0.51f);
}

void Cube::Rotate(QVector3D rotDirection, int rotSign)
{
    QMatrix4x4 matrix;
    matrix.rotate(rotSign * 180.0f / (2 * ROT_STEP), rotDirection);
    rotPosition = matrix * rotPosition;
    modelMatrix = rotPosition;
    modelMatrix.translate(0.51f, -0.51f, 0.51f);
}

Rubick::Rubick() :
    rotSign(0), step(0), rot(rotation::NONE), cubes {
        Cube(0, QVector3D(1.0f, 0.0f, 0.0f), colors::WHITE, colors::GREEN, colors::RED),
        Cube(-90, QVector3D(0.0f, 0.0f, 1.0f), colors::BLUE, colors::WHITE, colors::RED),
        Cube(180, QVector3D(0.0f, 0.0f, 1.0f), colors::YELLOW, colors::BLUE, colors::RED),
        Cube(90, QVector3D(0.0f, 0.0f, 1.0f), colors::GREEN, colors::YELLOW, colors::RED),
        Cube(90, QVector3D(1.0f, 0.0f, 0.0f), colors::ORANGE, colors::GREEN, colors::WHITE),
        Cube(180, QVector3D(0.0f, 1.0f, 0.0f), colors::WHITE, colors::BLUE, colors::ORANGE),
        Cube(180, QVector3D(0.0f, 1.0f, 1.0f), colors::ORANGE, colors::BLUE, colors::YELLOW),
        Cube(180, QVector3D(1.0f, 0.0f, 0.0f), colors::YELLOW, colors::GREEN, colors::ORANGE)
    }
{
    for (int i{}; i < CUBES_NUM; i++) {
        positions[i] = i;
    }
}

void Rubick::CreateBuffers(QOpenGLShaderProgram& program)
{
    VAO.create();
    VAO.bind();
    vertexBuffer.create();
    vertexBuffer.bind();

    vertexBuffer.allocate(cubeVertices, sizeof(cubeVertices));

    program.enableAttributeArray(0);
    program.setAttributeBuffer(0, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));

    program.enableAttributeArray(1);
    program.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

    VAO.release();
}

void Rubick::Rotate() {
    for (int i{}; i < CUBES_NUM/2; i++) {
        cubes[positions[rotPositions[i]]].Rotate(rotDirection, rotSign);
    }

    step++;
    if (step == ROT_STEP) {
        rotSign = 0;
        step = 0;
        swapPositions();
        rot = rotation::NONE;
    }
}

void Rubick::setRotation(rotation tmp_rot) {
    rot = tmp_rot;
    switch (tmp_rot) {
    case rotation::NONE: break;
    case rotation::FRONT_PLUS:
        rotDirection = QVector3D(0.0f, 0.0f, 1.0f);
        rotSign = 1;
        rotPositions[0] = 0;
        rotPositions[1] = 1;
        rotPositions[2] = 2;
        rotPositions[3] = 3;
        break;

    case rotation::BOTTOM_PLUS:
        rotDirection = QVector3D(0.0f, 1.0f, 0.0f);
        rotSign = 1;
        rotPositions[0] = 0;
        rotPositions[1] = 1;
        rotPositions[2] = 5;
        rotPositions[3] = 4;
        break;

    case rotation::RIGHT_PLUS:
        rotDirection = QVector3D(1.0f, 0.0f, 0.0f);
        rotSign = 1;
        rotPositions[0] = 0;
        rotPositions[1] = 3;
        rotPositions[2] = 7;
        rotPositions[3] = 4;
        break;
    }
}

void Rubick::swapPositions() {
    int tmp = positions[rotPositions[0]];
    positions[rotPositions[0]] = positions[rotPositions[1]];
    positions[rotPositions[1]] = positions[rotPositions[2]];
    positions[rotPositions[2]] = positions[rotPositions[3]];
    positions[rotPositions[3]] = tmp;
}
