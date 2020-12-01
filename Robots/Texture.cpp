#include "Texture.h"

Texture::Texture(int size, const std::string &color, const std::string &texture) {
    this->size = size;
    this->color = color;
    this->texture = texture;
}

std::string Texture::getPixel(int r, int c) {
    try {
        std::string pixel = color + texture[r * size + c];
        return pixel;
    }
    catch (std::exception&) {
        return color + " ";
    }
}

int Texture::getSize() {
    return size;
}