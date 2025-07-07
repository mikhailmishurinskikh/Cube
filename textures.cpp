#include "textures.hpp"

Textures::Textures()
{}

Textures::~Textures()
{
    for (auto texture : textures) {
        delete texture;
    }
}

void Textures::bind(colors color)
{
    textures[color]->bind();
}

void Textures::release(colors color)
{
    textures[color]->release();
}

void Textures::addTexture(colors color, const QString& filePath)
{
    QImage image(filePath);
    if(image.isNull()) {
        throw std::runtime_error("Texture loading failed");
    }

    auto texture = new QOpenGLTexture(image);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
    textures.insert(color, texture);
}

void Textures::loadAll()
{
    addTexture(colors::RED, ":/textures/red.png");
    addTexture(colors::GREEN, ":/textures/green.png");
    addTexture(colors::YELLOW, ":/textures/yellow.png");
    addTexture(colors::BLUE, ":/textures/blue.png");
    addTexture(colors::ORANGE, ":/textures/orange.png");
    addTexture(colors::WHITE, ":/textures/white.png");
    addTexture(colors::PLASTIC, ":/textures/plastic.png");
}
