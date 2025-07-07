#pragma once

#include <QMatrix4x4>

class Camera {
    QVector3D azimuthalAxe;
    float polarAngle;
    float aspect;

public:

    int polarSign;
    int azimuthalSign;
    QMatrix4x4 vpMatrix;

    Camera();
    void polarRotate();
    void azimuthalRotate();
    void updateSize(int w, int h);
};
