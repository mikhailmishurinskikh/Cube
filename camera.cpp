#include "camera.hpp"

#include <QMatrix3x3>

#define CAMERA_Z 5.0f

constexpr float ROTATE_STEP = 180.f / 300;
constexpr float MAX_POLAR_ANGLE = 180 / 3;

Camera::Camera() :
    azimuthalAxe(QVector3D(CAMERA_Z, 0.0f, -CAMERA_Z * std::tan(M_PI / 6))),
    polarAngle(30), aspect(1.5), polarSign(0), azimuthalSign(0), vpMatrix()
{
    vpMatrix.perspective(
        45.0f,  // fovY (в градусах)
        aspect,  // aspect
        0.1f,   // zNear
        100.0f  // zFar
    );

    const float angle = M_PI / 6;  // 30 градусов в радианах
    vpMatrix.lookAt(
        QVector3D(
            CAMERA_Z * std::tan(angle),
            (CAMERA_Z * std::tan(angle)) / std::cos(angle),
            CAMERA_Z
            ),  // eye
        QVector3D(0.0f, 0.0f, 0.0f),  // center
        QVector3D(0.0f, 1.0f, 0.0f)   // up
    );
}

void Camera::polarRotate() {
    if ((polarAngle < MAX_POLAR_ANGLE || polarSign == -1) &&
        (polarAngle > -MAX_POLAR_ANGLE || polarSign == 1))
    {
        vpMatrix.rotate(polarSign * ROTATE_STEP, azimuthalAxe);
        polarAngle += polarSign * ROTATE_STEP;
    }
}

void Camera::azimuthalRotate()
{
    QMatrix4x4 rotMatrix;
    rotMatrix.rotate(azimuthalSign * ROTATE_STEP, QVector3D(0.0f, 1.0f, 0.0f));
    vpMatrix = vpMatrix * rotMatrix;
    azimuthalAxe = rotMatrix.transposed().mapVector(azimuthalAxe);
}

void Camera::updateSize(int w, int h) {
    if (h==0) h=1;
    float newAspect = (float)w / h;
    QMatrix4x4 aspectMatrix;
    aspectMatrix.scale(aspect / newAspect, 1.0f, 1.0f);
    vpMatrix = aspectMatrix * vpMatrix;
    aspect = newAspect;
}
