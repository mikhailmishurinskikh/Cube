#pragma once

#include <QOpenGLTexture>
#include <QImage>
#include <QMap>

enum class colors {
    RED, GREEN, YELLOW, BLUE, ORANGE, WHITE, PLASTIC
};

class Textures {
    QMap<colors, QOpenGLTexture*> textures;

public:

    Textures();
    ~Textures();
    void bind(colors color);
    void release(colors color);
    void addTexture(colors color, const QString& filePath);
    void loadAll();
};
